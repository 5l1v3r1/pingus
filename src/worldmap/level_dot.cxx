//  $Id: level_dot.cxx,v 1.26 2003/10/21 11:01:52 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include <math.h>
#include <ClanLib/Display/font.h>
#include "../input/controller.hxx"
#include "../input/pointer.hxx"
#include "../gettext.h"
#include "../globals.hxx"
#include "../system.hxx"
#include "../fonts.hxx"
#include "../display/drawing_context.hxx"
#include "../gui/screen_manager.hxx"
#include "../resource.hxx"
#include "../path_manager.hxx"
#include "../start_screen.hxx"
#include "../plf_res_mgr.hxx"
#include "../savegame_manager.hxx"
#include "../file_reader.hxx"
#include "level_dot.hxx"

namespace Pingus {
namespace WorldMapNS {

LevelDot::LevelDot(FileReader reader)
  : Dot(reader.read_section("dot")),
    green_dot_sur(Resource::load_sprite("core/worldmap/dot_green")),
    red_dot_sur(Resource::load_sprite("core/worldmap/dot_red")),
    unaccessible_dot_sur(Resource::load_sprite("core/worldmap/dot_invalid")),
    highlight_green_dot_sur(Resource::load_sprite("core/worldmap/dot_green_hl")),
    highlight_red_dot_sur(Resource::load_sprite("core/worldmap/dot_red_hl"))
{
  reader.read_string("levelname", levelname);
}

void
LevelDot::draw(DrawingContext& gc)
{
  Vector mpos = gc.screen_to_world(Vector(Input::Controller::get_current()->get_pointer()->get_x_pos(),
                                          Input::Controller::get_current()->get_pointer()->get_y_pos()));

  float x = mpos.x - pos.x;
  float y = mpos.y - pos.y;

  bool highlight = false;

  if (sqrt(x*x + y*y) < 30.0f)
    highlight = true;

  Savegame* savegame = SavegameManager::instance()->get(levelname);
  if (savegame
      && (savegame->status == Savegame::FINISHED
          || savegame->status == Savegame::ACCESSIBLE))
    {
      if (savegame->status == Savegame::FINISHED)
        if (highlight)
          gc.draw (highlight_green_dot_sur, pos);
        else
          gc.draw (green_dot_sur, pos);
      else
        if (highlight)
          gc.draw (highlight_red_dot_sur, pos);
        else
          gc.draw (red_dot_sur, pos);
    }
  else
    {
      gc.draw (unaccessible_dot_sur, pos);
    }
}

void
LevelDot::update(float delta)
{
  UNUSED_ARG(delta);
}

void
LevelDot::on_click()
{
  std::cout << "Starting level: " << levelname << std::endl;
  ScreenManager::instance()->push_screen(new StartScreen(plf),
                                         true);
}

bool
LevelDot::finished()
{
  Savegame* savegame = SavegameManager::instance()->get(levelname);
  if (savegame && savegame->status == Savegame::FINISHED)
    return true;
  else
    return false;
}

bool
LevelDot::accessible()
{
  Savegame* savegame = SavegameManager::instance()->get(levelname);
  if (savegame && savegame->status != Savegame::NONE)
    return true;
  else
    return false;
}


void
LevelDot::draw_hover(DrawingContext& gc)
{
  int pos_correction = 0;

  if (accessible())
    {
      int length = Fonts::pingus_small.bounding_rect(0, 0, System::translate(get_plf().get_levelname())).get_width() / 2;
      int realpos = static_cast<int>(gc.world_to_screen(Vector(pos.x, pos.y, 0)).x);
      if (realpos - length < 0)
        pos_correction = realpos - length;
      else if (realpos + length > gc.get_width())
        pos_correction = realpos + length - static_cast<int>(gc.get_width());
      
      gc.print_center(Fonts::pingus_small,
                      static_cast<int>(pos.x) - pos_correction,
                      static_cast<int>(pos.y - 40),
                      System::translate(get_plf().get_levelname()));
    }
  else
    {
      int length  = Fonts::pingus_small.bounding_rect(0, 0, _("locked")).get_width() / 2;
      int realpos = static_cast<int>(gc.world_to_screen(Vector(pos.x, pos.y, 0)).x);
      if (realpos - length < 0)
        pos_correction = realpos - length;
      else if (realpos + length > gc.get_width())
        pos_correction = realpos + length - static_cast<int>(gc.get_width());
        
      gc.print_center(Fonts::pingus_small,
                      static_cast<int>(pos.x) - pos_correction,
                      static_cast<int>(pos.y - 30),
                      _("locked"));
    }

  if (maintainer_mode)
    {
      gc.print_center(Fonts::pingus_small,
                      int(pos.x), int(pos.y - 56),
                      get_plf().get_resname());
    }
}

void
LevelDot::unlock()
{
  Savegame* savegame = SavegameManager::instance()->get(levelname);
  if (savegame == 0 || savegame->status == Savegame::NONE)
    {
      Savegame savegame;
      savegame.status = Savegame::ACCESSIBLE;
      savegame.levelname = levelname;
      SavegameManager::instance()->store(savegame);
    }
  else
    {
    }
}

} // namespace WorldMapNS
} // namespace Pingus

/* EOF */
