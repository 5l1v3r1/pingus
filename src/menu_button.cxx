//  $Id: menu_button.cxx,v 1.16 2003/12/14 00:30:04 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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
#include <ClanLib/Display/font.h>
#include "globals.hxx"
#include "debug.hxx"
#include "sound/sound.hxx"
#include "resource.hxx"
#include "pingus_menu_manager.hxx"
#include "credits.hxx"
#include "editor/editor.hxx"
#include "theme_selector.hxx"
#include "menu_button.hxx"
#include "gui/screen_manager.hxx"
#include "worldmap/manager.hxx"
#include "story_screen.hxx"
#include "gettext.h"
#include "stat_manager.hxx"
#include "story.hxx"

namespace Pingus {

using EditorNS::Editor;

SurfaceButton::SurfaceButton ()
{
  font       = Fonts::pingus_small;
  font_large = Fonts::pingus_large;

  mouse_over = false;
  pressed = false;

  //std::cout << "Generating font cache: " << std::flush;
  // We print all available letters, so that they are in the cache
  //font->print_left (0,0, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  //font_large->print_left (0,0, "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
  //std::cout << "done" << std::endl;
}

SurfaceButton::~SurfaceButton ()
{
}

void
SurfaceButton::draw (GraphicContext& gc)
{
  if (mouse_over && !pressed)
    {
      gc.print_center(font, CL_Display::get_width() / 2,
                      CL_Display::get_height() - font.get_height(),
                      desc.c_str());

      gc.draw(surface_p, Vector(x_pos - surface_p.get_width()/2,
                                y_pos - surface_p.get_height()/2));

      if (line2.empty())
	{
	  gc.print_center(font_large, x_pos + 32,
                          y_pos - 32 - font_large.get_height()/2,
                          line1.c_str());
	}
      else
	{
	  gc.print_center(font_large, x_pos + 32, y_pos - 32 - (font_large.get_height() - 5),
                          line1.c_str());
	  gc.print_center(font_large, x_pos + 32, y_pos - 32,
                          line2.c_str());
	}
    }
  else if (mouse_over && pressed)
    {
      float shrink = 0.9f;

      gc.print_center(font, CL_Display::get_width() / 2,
                      CL_Display::get_height() - 20,
                      desc.c_str());

      gc.draw(surface_p,
              Vector(x_pos - surface_p.get_width()/2 * shrink,
                     y_pos - surface_p.get_height()/2 * shrink));
#ifdef CLANLIB_0_6
              shrink, shrink, 0);
#endif

      if (line2.empty())
	{
	  gc.print_center(font_large,
                          x_pos + 32,
                          y_pos - 32 - font_large.get_height()/2,
                          line1.c_str());
	}
      else
	{
	  gc.print_center(font_large,
                          x_pos + 32, y_pos - 32 - font_large.get_height(),
                          line1.c_str());
	  gc.print_center(font_large, x_pos + 32, y_pos - 32,
                          line2.c_str());
	}
    }
  else
    {
      gc.draw(surface_p,
              Vector(x_pos - surface_p.get_width()/2,
                     y_pos - surface_p.get_height()/2));
    }
  UNUSED_ARG(gc);
}

void
SurfaceButton::update (float delta)
{
  UNUSED_ARG(delta);
}

void
SurfaceButton::on_pointer_enter ()
{
  mouse_over = true;
  Sound::PingusSound::play_sound ("tick");
  //std::cout << "X: " << this << "enter" << std::endl;
}

void
SurfaceButton::on_pointer_leave ()
{
  //std::cout << "X: " << this << "leave" << std::endl;
  mouse_over = false;
}

void
SurfaceButton::on_pointer_press ()
{
  pressed = true;
}

void
SurfaceButton::on_pointer_release ()
{
  pressed = false;
}

bool
SurfaceButton::is_at(int x, int y)
{
  return (x > x_pos - int(surface_p.get_width()) / 2
	  && x < x_pos + int(surface_p.get_width()) / 2
	  && y > y_pos - int(surface_p.get_height()) / 2
	  && y < y_pos + int(surface_p.get_height()) / 2);
}

///////////////////////////////////////////////

CreditButton::CreditButton (PingusMenu* menu_)
  : menu(menu_)
{
  // x_pos = CL_Display::get_width() * 500 / 640;
  // y_pos = CL_Display::get_height() * 420 / 480;

  x_pos = CL_Display::get_width() * 126 / 640;
  y_pos = CL_Display::get_height() * 369 / 480;

  //  desc["en"] = "..:: Starts the level you played at last ::..";
  desc = _("..:: The people who brought this game to you ::..");
  //desc["de"] = "..:: Wer hat den dieses Spiel verbrochen...? ::..";

  line1 = _("Credits");
  //line1["de"] = "Credits";

  surface_p = Resource::load_sprite("menu/credits_on", "core");
  //  surface   = Resource::load_sprite("NewButtons/credits_off", "menu");

  //surface   = Resource::load_sprite("Buttons/play", "menu");
  //surface_p = Resource::load_sprite("Buttons/play_p", "menu");
}

CreditButton::~CreditButton ()
{
}

void
CreditButton::on_click ()
{
  std::cout << "Pushing credits screen" << std::endl;
  ScreenManager::instance()->push_screen (Credits::instance(), false);
}

///////////////////////////////////////////////

OptionsButton::OptionsButton (PingusMenu* menu_)
  : menu(menu_)
{
  // x_pos = CL_Display::get_width() * 150 / 640; //150;
  // y_pos = CL_Display::get_height() * 330 / 480; //330;

  x_pos = CL_Display::get_width() * 516 / 640; //150;
  y_pos = CL_Display::get_height() * 113 / 480; //330;

  desc = _("..:: Takes you to the options menu ::..");
  //  desc["de"] = "..:: Einstellungen und Mogeleien ::..";

  line1 = _("Options");
  //line1["de"] = "Einstellungen";

  //  surface   = Resource::load_sprite("NewButtons/options_off", "menu");
  surface_p = Resource::load_sprite("menu/options_on", "core");

  // surface   = Resource::load_sprite("Buttons/options", "menu");
  // surface_p = Resource::load_sprite("Buttons/options_p", "menu");
}

OptionsButton::~OptionsButton ()
{
}

void
OptionsButton::on_click()
{
  //option_menu.display();
  //menu->get_manager ()->set_menu (&menu->get_manager ()->optionmenu);
  perr (PINGUS_DEBUG_GUI) << "Option menu currently disabled" << std::endl;
}

///////////////////////////////////////////////

QuitButton::QuitButton(PingusMenu* m)
  : menu (m)
{
  // x_pos = CL_Display::get_width() * 500 / 640;
  // y_pos = CL_Display::get_height() * 320 / 480;

  x_pos = CL_Display::get_width() * 650 / 800;
  y_pos = CL_Display::get_height() * 370 / 600;

  desc = _("..:: Bye, bye ::..");
  //desc["de"] = "..:: Auf Wiedersehen ::..";

  line1 = _("Exit");
  //line1["de"] = "Ausgang";

  // surface   = Resource::load_sprite("Buttons/quit", "menu");
  // surface_p = Resource::load_sprite("Buttons/quit_p", "menu");

  //  surface   = Resource::load_sprite("NewButtons/exit_off", "menu");
  surface_p = Resource::load_sprite("menu/exit_on", "core");
}

QuitButton::~QuitButton()
{
}

void
QuitButton::on_click()
{
  menu->get_manager ()->show_exit_menu ();
}

///////////////////////////////////////////////

LoadButton::LoadButton()
{
  x_pos = CL_Display::get_width() * 400 / 800;
  y_pos = CL_Display::get_height() * 500 / 600;

  //surface   = Resource::load_sprite("menu/load", "core");
  surface_p = Resource::load_sprite("menu/load_p", "core");
}

LoadButton::~LoadButton()
{
}

void LoadButton::on_click()
{
  /*  std::string levelfile;
  levelfile = file.select(pXXXus_datadir, "*.pingus");
  if (!levelfile.empty()) {
    PingusGame game;
    game.start(levelfile);
    }*/
}

EditorButton::EditorButton (PingusMenu* menu_)
  : menu(menu_)
{
  x_pos = CL_Display::get_width()  * 150 / 800;
  y_pos = CL_Display::get_height() * 370 / 600;

  desc = _("..:: Launch the level editor ::..");
  //desc["de"] = "..:: Den Level Editor starten ::..";

  line1 = _("Create a");
  line2 = _("Level");

  //line1["de"] = "Level";
  //line2["de"] = "Editor";

  // surface   = Resource::load_sprite("Buttons/editor", "menu");
  // surface_p = Resource::load_sprite("Buttons/editor_p", "menu");

  surface_p = Resource::load_sprite("menu/create_on", "core");
}

EditorButton::~EditorButton ()
{

}

void
EditorButton::load_level (const std::string& str)
{
  Editor::instance ()->load_level (str);
}

void
EditorButton::on_click()
{
  ScreenManager::instance()->push_screen (Editor::instance(), false);
}

StoryButton::StoryButton (PingusMenu* menu_)
  : menu(menu_)
{
  x_pos = CL_Display::get_width()  * 400 / 800;
  y_pos = CL_Display::get_height() * 370 / 600;

  desc = _("..:: Start the game ::..");
  line1 = _("Start");
  surface_p = Resource::load_sprite("menu/play_on", "core");
}

StoryButton::~StoryButton () {}

void
StoryButton::on_click ()
{
  Sound::PingusSound::play_sound ("letsgo");

  bool story_seen = false;
  StatManager::instance()->get_bool("story-seen", story_seen);

  if (!story_seen)
    {
      ScreenManager::instance()->push_screen(new StoryScreen(Story::intro), true);
    }
  else
    {
      ScreenManager::instance()->push_screen(WorldMapNS::WorldMapManager::instance ());
    }
}

ThemeButton::ThemeButton (PingusMenu* menu_)
  : menu(menu_)
{
  x_pos = CL_Display::get_width() * 321 / 640;
  y_pos = CL_Display::get_height() * 100 / 480;

  desc = _("..:: Start a contrib level ::..");

  line1 = _("Contrib");
  surface_p = Resource::load_sprite("menu/play_on", "core");
}

void
ThemeButton::on_click ()
{
  Sound::PingusSound::play_sound ("letsgo");

#ifdef CLANLIB_0_6
  ThemeSelector theme_selector;
  theme_selector.display();
#endif
}

#if 0
MultiplayerButton::MultiplayerButton (PingusMenu* menu_)
  : menu(menu_)
{
  x_pos = CL_Display::get_width() * 320 / 640;
  y_pos = CL_Display::get_height() * 369 / 480;

  desc = _("..:: Multiplayer Modes... experimental stuff ::..");

  line1 = _("Multi");

  surface_p = Resource::load_sprite("menu/multi_on", "core");
}

MultiplayerButton::~MultiplayerButton ()
{
}

void
MultiplayerButton::on_click ()
{
  multiplayer_config.display ();
}
#endif

} // namespace Pingus

/* EOF */
