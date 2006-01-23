//  $Id: file_dialog.cxx,v 1.00 2005/11/18 00:30:04 Jave27 Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <ClanLib/Display/display.h>
#include <ClanLib/Core/IOData/directory_scanner.h>
#include "gettext.h"
#include "pingus_menu_manager.hxx"
#include "resource.hxx"
#include "gui/surface_button.hxx"
#include "gui/gui_manager.hxx"
#include "gui/input_box.hxx"
#include "sound/sound.hxx"
#include "file_dialog.hxx"
#include "file_dialog_item.hxx"
#include "file_dialog_listener.hxx"

namespace Pingus {

	const int DIR_UP = 0;
	const int DIR_DOWN = 1;

	class FileDialogOkButton : public GUI::SurfaceButton
	{
	private:
		FileDialog* file_dialog;
		std::string label;
		bool is_hidden;

	public:
		FileDialogOkButton (FileDialog *f, std::string l)
			: GUI::SurfaceButton(CL_Display::get_width()/2 + 170,
			CL_Display::get_height()/2 + 160,
			ResDescriptor("core/menu/exit_button_normal"),
			ResDescriptor("core/menu/exit_button_pressed"),
			ResDescriptor("core/menu/exit_button_hover")),
			file_dialog(f),
			label (l),
			is_hidden(true)
		{
		}

		void draw (DrawingContext& gc) {
			if (!is_hidden)
			{
				SurfaceButton::draw(gc);
				gc.print_right(Fonts::chalk_large, (float)CL_Display::get_width()/2 + 200,
					(float)CL_Display::get_height()/2 + 160, label);
			}
		}

		void on_click()
		{
			if (!is_hidden)
			{
				Sound::PingusSound::play_sound ("yipee");
				file_dialog->ok_pressed();
			}
		}

		void on_pointer_enter()
		{
			if (!is_hidden)
			{
				SurfaceButton::on_pointer_enter();
				Sound::PingusSound::play_sound ("tick");
			}
		}

		void hide() { is_hidden = true; }
		void show() { is_hidden = false; }

	};

	class FileDialogCancelButton : public GUI::SurfaceButton
	{
	private:
		FileDialog* file_dialog;

	public:
		FileDialogCancelButton (FileDialog* f)
			: GUI::SurfaceButton(CL_Display::get_width()/2 - 280,
			CL_Display::get_height()/2 + 160,
			ResDescriptor("core/menu/exit_button_normal"),
			ResDescriptor("core/menu/exit_button_pressed"),
			ResDescriptor("core/menu/exit_button_hover")),
			file_dialog (f)
		{
		}

		void draw (DrawingContext& gc) {
			SurfaceButton::draw(gc);
			gc.print_right(Fonts::chalk_large, (float)CL_Display::get_width()/2 - 200,
				(float)CL_Display::get_height()/2 + 160, _("Cancel"));
		}

		void on_click()
		{
			Sound::PingusSound::play_sound ("yipee");
			file_dialog->cancel_pressed();
		}

		void on_pointer_enter()
		{
			SurfaceButton::on_pointer_enter();
			Sound::PingusSound::play_sound ("tick");
		}
	};

	class FileDialogScrollButton : public GUI::Component
	{
	private:
		/** FileDialog box to this which button is assigned */
		FileDialog* file_dialog;

		/** Where the image is located */
		Vector pos;

		/** Image used for the scroll button */
		CL_Sprite sprite;

		/** 0 for Up, 1 for Down */
		int direction;

		/** Show it or not */
		bool is_hidden;

		bool hover;

	public:
		FileDialogScrollButton (FileDialog* f, int d, int height_offset)
			: file_dialog(f),
				pos(Vector((float)CL_Display::get_width()/2 + 210,
					(float)CL_Display::get_height()/2 + height_offset)),
				direction(d),
				is_hidden(false),
				hover(false)
		{
			std::string str_direction = d==0 ? "up" : "down";
			sprite = Resource::load_sprite("core/menu/" + str_direction + "_arrow");
		}

		void draw (DrawingContext& gc) {
			if (!is_hidden)
			{
				gc.draw(sprite, pos);
				if (hover)
					gc.draw_rect(pos.x, pos.y, pos.x + sprite.get_width(), 
						pos.y + sprite.get_height(), CL_Color(255,255,255,150));
			}
		}
		
		void on_primary_button_click(int x, int y)
		{
			file_dialog->scroll(direction);
		}

		void on_pointer_enter() { hover = true; }
		void on_pointer_leave() { hover = false; }

		bool is_at(int x, int y)
		{
			if (is_hidden)
				return false;
			return (x > (int)pos.x && x < (int)pos.x + sprite.get_width()
				&& y > (int)pos.y && y < (int)pos.y + sprite.get_height());
		}

		void show() { is_hidden = false; }
		void hide() { is_hidden = true; }
	};

	class FileDialogParentFolderButton : public GUI::Component
	{
	private:
		/** FileDialog box to this which button is assigned */
		FileDialog* file_dialog;

		/** Where the image is located */
		Vector pos;

		/** Image used for the parent folder button */
		CL_Sprite sprite;

		bool hover;

	public:
		FileDialogParentFolderButton (FileDialog* f)
			: file_dialog(f),
        pos(Vector((float)CL_Display::get_width()/2 + 230,
                   (float)CL_Display::get_height()/2 - 210)),
			  sprite(Resource::load_sprite("core/menu/parent_folder")),
				hover(false)
		{
		}

		void draw (DrawingContext& gc) {
			gc.draw(sprite, pos);
			if (hover)
				gc.draw_rect(pos.x, pos.y, pos.x + sprite.get_width(), 
					pos.y + sprite.get_height(), CL_Color(255,255,255,150));
		}
		
		void on_primary_button_click(int x, int y)
		{
			FileItem f;
			f.name = "..";
			f.is_directory = true;
			file_dialog->set_selected_file(f);
		}

		void on_pointer_enter() { hover = true; }
		void on_pointer_leave() { hover = false; }

		bool is_at(int x, int y)
		{
			return (x > (int)pos.x && x < (int)pos.x + sprite.get_width()
				&& y > (int)pos.y && y < (int)pos.y + sprite.get_height());
		}
	};

	FileDialog::FileDialog (FileDialogListener* listener_, 
		const std::string filemask_, 
		const std::string searchpath_, 
		bool for_load)
		: PingusSubMenu (PingusMenuManager::instance()),
									listener(listener_),
                  for_loading(for_load),
                  file_mask(filemask_),
                  current_path(searchpath_)
	{
		// Initialize the buttons
		ok_button = new FileDialogOkButton(this,
			for_loading ? _("Load") : _("Save"));

		up_button = new FileDialogScrollButton(this, DIR_UP, -150);
		down_button = new FileDialogScrollButton(this, DIR_DOWN, 100);

		gui_manager->add(ok_button, true);
		gui_manager->add(up_button, true);
		gui_manager->add(down_button, true);
		gui_manager->add(new FileDialogCancelButton(this), true);
		gui_manager->add(new FileDialogParentFolderButton(this));

		// FIXME: Ugly - hardcoded values for items in file dialog.  Should be dynamic.
		// Create 8 FileDialogItems and add them to the gui_manager.
		float center_x = (float)CL_Display::get_width()/2;
		float center_y = (float)CL_Display::get_height()/2;

		inputbox = new GUI::InputBox(450, Vector(center_x - 225, center_y - 170));
		gui_manager->add((GUI::Component*)inputbox);

		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 280, center_y - 140)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 280, center_y - 70)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 280, center_y + 10)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 280, center_y + 80)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 10, center_y - 140)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 10, center_y - 70)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 10, center_y + 10)));
		file_dialog_items.push_back(new FileDialogItem(this, 
			Vector(center_x - 10, center_y + 80)));

		for (std::vector<FileDialogItem*>::const_iterator i = file_dialog_items.begin();
			i != file_dialog_items.end(); i++)
			gui_manager->add((GUI::Component*)(*i));

		refresh();
	}

	FileDialog::~FileDialog ()
	{
	}

	bool
		FileDialog::draw (DrawingContext& gc)
	{
		gc.draw(sprite, Vector(gc.get_width ()/2 - sprite.get_width ()/2,
			gc.get_height ()/2 - sprite.get_height ()/2));
		gc.draw_rect(gc.get_width() / 2 - 285, gc.get_height() / 2 - 160,
			gc.get_width() / 2 + 285, gc.get_height() / 2 + 160, CL_Color::black);
		gc.print_center(Fonts::chalk_large, gc.get_width()/2, gc.get_height()/2 - 220, 
			current_file.friendly_name == "" ? current_file.name : current_file.friendly_name);

		PingusSubMenu::draw(gc);
		return true;
	}

	void
		FileDialog::preload ()
	{
		sprite = Resource::load_sprite("core/menu/filedialog");
	}

	void
		FileDialog::refresh ()
	{
		// Clear the current list of files
		file_list.clear();
		current_offset=0;

		FileItem f;

		// Get the list of files and folders in the current folder
		CL_DirectoryScanner scanner;
		scanner.scan(current_path, "*");
		while (scanner.next())
		{
			if (scanner.get_name() != "." && scanner.get_name() != ".." 
				&& scanner.get_name() != ".svn" && scanner.is_directory())
			{
				f.name = scanner.get_name();
				f.is_directory = true;
				file_list.push_back(f);
			}
		}

		scanner.scan(current_path, "*" + file_mask);
		while (scanner.next())
		{
			f.name = scanner.get_name();
			f.is_directory = false;
			file_list.push_back(f);
		}

		std::sort(file_list.begin(), file_list.end(), &FileItemCompare);

		current_offset = 0;
		offset_changed();
	}

	// Whenever the list of showing files has changed.
	void
	FileDialog::offset_changed()
	{
		unsigned j = current_offset;

		for (std::vector<FileDialogItem*>::const_iterator i = file_dialog_items.begin();
			i != file_dialog_items.end(); i++, j++)
		{
			 if (j < (unsigned)file_list.size())
				 (*i)->set_file(file_list[j]);
			 else
				 (*i)->hide();
		}

		// Show or hide scroll buttons
		if (current_offset == 0)
			up_button->hide();
		else
			up_button->show();

		if (current_offset + (unsigned)file_dialog_items.size() < (unsigned)file_list.size())
			down_button->show();
		else
			down_button->hide();
	}

	// Scroll the list up or down.
	void
	FileDialog::scroll(int direction)
	{
		if (direction == DIR_UP)
		{
			if (current_offset != 0)
				current_offset -= (unsigned)file_dialog_items.size();
		}
		else
		{
			if (current_offset + (unsigned)file_dialog_items.size() < (unsigned)file_list.size())
				current_offset += (unsigned)file_dialog_items.size();
		}
		offset_changed();
	}

	// Set the file and show or hide the OK button.
	void
	FileDialog::set_selected_file(FileItem f)
	{ 
	 current_file = f;
	 if (current_file.name != "")
	 {
			ok_button->show();
			if (!current_file.is_directory)
				inputbox->set_string(current_file.name);
			else
				inputbox->set_string("");
	 }
	 else
		 ok_button->hide();

	 if (current_file.is_directory)
		 ok_pressed();
	}

	void
	FileDialog::ok_pressed()
	{
		// If it's a directory, change to it.
		if (current_file.is_directory)
		{
			current_path += current_file.name + "/";
			refresh();
			ok_button->hide();
		}
		else
		{
			// Load or save the selected file
			if (for_loading)
				listener->load(current_path + current_file.name, file_mask);
			else
				listener->save(current_path + current_file.name, file_mask);
		}
	}

	void
	FileDialog::cancel_pressed()
	{
		listener->cancel();
	}

} // namespace Pingus

/* EOF */
