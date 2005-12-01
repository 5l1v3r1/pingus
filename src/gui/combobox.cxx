//  $Id: combobox.cxx,v 1.16 2005/11/10 21:37:06 Jave27 Exp $
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

#include <ClanLib/Display/font.h>
#include <vector>
#include <string>
#include "combobox.hxx"
#include "../fonts.hxx"

namespace Pingus {
namespace GUI {

// Constructor
Combobox::Combobox (Vector p) :
	current_item(0),
	drop_down(false),
	pos(p)
{
	// Default to 20 characters wide.
	width = Fonts::smallfont.get_width('O') * 20.0f;
	height = (float)Fonts::smallfont.get_height();
}

// Destructor
Combobox::~Combobox ()
{
	for (std::vector<ComboItem*>::iterator i = item_list.begin();
		i != item_list.end(); i++)
	{
		if ((*i)->delete_it())
			delete (*i);
	}
}

// Add an item to the combobox
void
Combobox::add(ComboItem* item)
{
	item_list.push_back(item);
}

// Remove an item from the combobox.  Delete it if necessary
void
Combobox::remove(ComboItem* item)
{
	for (std::vector<ComboItem*>::iterator i = item_list.begin();
		i != item_list.end(); i++)
	{
		if ((*i) == item)
		{
			item_list.erase(i);
			if (item->delete_it())
				delete item;
		}
	}
}
			
// Returns whether or not the combobox is at this location
bool
Combobox::is_at(int x, int y)
{
	return ((float)x > pos.x && (float)x < pos.x + get_width() &&
		(float)y > pos.y && (float)y < pos.y + get_height());
}

// Returns the width of the box
float
Combobox::get_width()
{
	return width;
}

// Returns the height of the box
float
Combobox::get_height()
{
	if (drop_down)
		return height * ((float)item_list.size() + 1.0f);
	else
		return height;
}

// action taken when the primary mouse button is clicked
void
Combobox::on_primary_button_click(int x, int y)
{
	if (drop_down)
	{
		// Determine which item was selected, if any, and set the current item to it.
		if (y > pos.y + height)
			current_item = item_list[static_cast<int>((y - pos.y - height) / height)];
		drop_down = false;
	}
	else
	{
		drop_down = true;
	}
}

// Draws the Combobox on the screen at it's location
void
Combobox::draw(DrawingContext &gc)
{
	// First off, Draw the rectangle
	gc.draw_fillrect(pos.x, pos.y, pos.x + get_width(), pos.y + get_height(),
		CL_Color::white);
	// Next, draw the rectangle border
	gc.draw_rect(pos.x, pos.y, pos.x + get_width(), pos.y + get_height(),
		CL_Color::black);

	if (drop_down && item_list.size() > 0)
	{
		// FIXME: Implement - Draw the "highlighted" rectangle.
		// FIXME: Need to have the mouse pointer x,y coordinates for this function.
		
		// Draw all of the items
		for (unsigned i = 0; i < item_list.size(); i++)
		{
			gc.print_left(Fonts::smallfont, pos.x + 5.0f, pos.y + ((i + 1) * height), 
				item_list[i]->get_string(), 5000);
		}
	}

	if (current_item)
	{
		// Print the currently selected item
		gc.print_left(Fonts::smallfont, pos.x + 3.0f, pos.y, current_item->get_string());
	}
}

}	// GUI namespace
} // Pingus namespace

/* EOF */
