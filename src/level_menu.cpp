//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#include <boost/format.hpp>
#include "gettext.h"
#include "resource.hpp"
#include "screen/screen_manager.hpp"
#include "fonts.hpp"
#include "display/drawing_context.hpp"
#include "option_menu.hpp"
#include "system.hpp"
#include "display/display.hpp"
#include "level_menu.hpp"
#include "gui/rect_component.hpp"
#include "gui/gui_manager.hpp"
#include "game_session.hpp"
#include "start_screen.hpp"

class LevelsetSelector : public GUI::RectComponent
{
private:
  LevelMenu* level_menu;
  typedef std::vector<Levelset*> Levelsets;
  Levelsets levelsets;
  Levelset* current_levelset;
  Sprite marker;

public:
  LevelsetSelector(LevelMenu* level_menu_, const Rect& rect_) 
    : RectComponent(rect_),
      level_menu(level_menu_)
  {
    marker        = Resource::load_sprite("core/menu/marker");

    std::string path = Pathname("levelsets", Pathname::DATA_PATH).get_sys_path();
    System::Directory directory = System::opendir(path, "*.levelset");
    for(System::Directory::iterator i = directory.begin(); i != directory.end(); ++i)
      {
        levelsets.push_back(new Levelset(Pathname(path + "/" + i->name, Pathname::SYSTEM_PATH)));
      }
  }

  ~LevelsetSelector() 
  {
    for(Levelsets::iterator i = levelsets.begin(); i != levelsets.end(); ++i)
      {
        delete *i;
      }
  }
  
  void draw(DrawingContext& gc)
  {
    gc.print_center(Fonts::chalk_large, 800/2, 90, _("Levelset Menu"));

    gc.push_modelview();
    gc.translate(static_cast<float>(rect.left), static_cast<float>(rect.top));

    //gc.draw_fillrect(Rect(Vector2i(0,0), Size(rect.get_width(), rect.get_height())),
    //                 Color(255, 255, 0, 100));

    int y = 0;
    for(Levelsets::iterator i = levelsets.begin(); i != levelsets.end(); ++i)
      {
        if (*i == current_levelset)
          gc.draw(marker, Vector2i(0, y - 5));

        gc.draw((*i)->get_image(), Vector2i(30, y));

        gc.print_left(Fonts::chalk_normal, 85+30, 15 + y, (*i)->get_title());
        gc.print_left(Fonts::chalk_small,  85+50, 40 + y, (*i)->get_description());

        gc.print_right(Fonts::chalk_normal, rect.get_width() - 30, 15 + y, (boost::format("Completion: %1%%%") % (*i)->get_completion()).str());
        gc.print_right(Fonts::chalk_small,  rect.get_width() - 30, 60 + y, (boost::format("%1% levels") % (*i)->get_level_count()).str());

        //gc.draw(ok_button, 620, y);

        y += 75;
      }
    gc.pop_modelview();
  }

  void on_pointer_move(int x, int y)
  {
    x -= rect.left;
    y -= rect.top;

    if (!levelsets.empty())
      {
        int i = y / 75;

        if (i >= 0 && i < 4)
          current_levelset = levelsets[i];
        else
          i = 0;
      }
  }

  void on_primary_button_press (int x, int y)
  {
    if (current_levelset)
      {
        level_menu->set_levelset(current_levelset);
      }
  }

  void update_layout() {}
};

class LevelSelector : public GUI::RectComponent
{
private:
  LevelMenu* level_menu;
  Sprite marker;
  Sprite marker_locked;
  Levelset* levelset;
  int current_level;
  
public:
  LevelSelector(LevelMenu* level_menu_, const Rect& rect_) 
    : RectComponent(rect_),
      level_menu(level_menu_),
      levelset(0),
      current_level(-1)
  {
    marker        = Resource::load_sprite("core/menu/marker2");
    marker_locked = Resource::load_sprite("core/menu/marker_locked");
  }

  void draw(DrawingContext& gc) 
  {
    gc.print_center(Fonts::chalk_large, 800/2, 90, _(levelset->get_title()));

    gc.push_modelview();
    gc.translate(static_cast<float>(rect.left), static_cast<float>(rect.top));

    if (levelset)
      {
        levelset->refresh(); // should be better placed in on_startup() or so
        
        //gc.draw_fillrect(Rect(Vector2i(0,0), Size(rect.get_width(), rect.get_height())),
        //                 Color(255, 255, 0, 100));

        gc.print_left(Fonts::chalk_normal,  30, -32, "Levelname");
        gc.print_right(Fonts::chalk_normal, rect.get_width() - 30, - 32, "Status");

        int y = 0;
        for(int i = 0; i < levelset->get_level_count(); ++i)
          {
            if (!levelset->get_level(i)->accessible)
              gc.draw(marker_locked, Vector2i(0, y));
            else if (i == current_level)
              gc.draw(marker, Vector2i(0, y));
                        
            std::string level = levelset->get_level(i)->plf.get_levelname();
            gc.print_left(Fonts::chalk_small, 30, y+4, level);

            if (levelset->get_level(i)->finished)
              gc.print_right(Fonts::chalk_small, rect.get_width() -30, y+4, "solved");
            else
              gc.print_right(Fonts::chalk_small, rect.get_width() -30, y+4, "unsolved");

            y += 32;
          }
      }
    
    gc.pop_modelview();
  }

  void set_levelset(Levelset* levelset_)
  {
    levelset = levelset_;
  }

  void on_pointer_move(int x, int y)
  {
    x -= rect.left;
    y -= rect.top;

    current_level = y / 32;
    
    if (current_level < 0 || current_level > levelset->get_level_count())
      current_level = -1;
  }

  void on_primary_button_press (int x, int y)
  {
    if (current_level != -1)
      {
        if (levelset->get_level(current_level)->accessible)
          {
            ScreenManager::instance()->push_screen(new StartScreen(levelset->get_level(current_level)->plf), true);
          }
      }
  }

  void update_layout() {}
};

LevelMenu::LevelMenu()
  : x_pos((Display::get_width()  - 800)/2),
    y_pos((Display::get_height() - 600)/2)
{
  background = Resource::load_sprite("core/menu/filedialog");
  ok_button  = Resource::load_sprite("core/start/ok");

  levelset_selector = new LevelsetSelector(this, Rect(Vector2i(x_pos + 100, y_pos + 140), Size(600, 300)));
  level_selector    = new LevelSelector(this, Rect(Vector2i(x_pos + 100, y_pos + 160), Size(600, 300)));

  gui_manager->add(levelset_selector, true);
  gui_manager->add(level_selector,    true);

  level_selector->hide();
}

LevelMenu::~LevelMenu()
{
}

void
LevelMenu::draw_background(DrawingContext& gc)
{
  gc.push_modelview();
  gc.translate(static_cast<float>(x_pos), static_cast<float>(y_pos));

  // gc.draw_fillrect(Rect(100, 100, 400, 400), Color(255, 0, 0));
  gc.draw(background, Vector2i(400 - background.get_width()/2, 300 - background.get_height()/2));

  gc.pop_modelview();
}

void
LevelMenu::on_escape_press()
{
  std::cout << "OptionMenu: poping screen" << std::endl;
  ScreenManager::instance()->pop_screen();
}

void
LevelMenu::set_levelset(Levelset* levelset)
{
  if (levelset)
    {
      level_selector->set_levelset(levelset);
      levelset_selector->hide();
      level_selector->show();
    }
  else
    {
      levelset_selector->show();
      level_selector->hide();      
    }
}

/* EOF */
