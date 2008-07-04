//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include "../gettext.h"
#include "../fonts.hpp"
#include "../display/display.hpp"
#include "../screen/screen_manager.hpp"
#include "../gui/surface_button.hpp"
#include "../path_manager.hpp"
#include "../res_descriptor.hpp"
#include "../sound/sound.hpp"
#include "../stat_manager.hpp"
#include "../display/scene_context.hpp"
#include "../math.hpp"
#include "worldmap.hpp"
#include "worldmap_component.hpp"
#include "resource.hpp"
#include "worldmap_story.hpp"
#include "pingus.hpp"
#include "../story_screen.hpp"
#include "worldmap_screen.hpp"

class WorldmapScreenCloseButton
  : public GUI::SurfaceButton
{
private: 
  WorldmapScreen* worldmap_screen;
public:
  WorldmapScreenCloseButton(WorldMapScreen* worldmap_screen);
  void on_click();
  void draw (DrawingContext& gc);
  void on_pointer_enter();
};

class WorldmapScreenStoryButton
  : public GUI::SurfaceButton
{
private:
  WorldmapScreen* worldmap_screen;
public:
  WorldmapScreenStoryButton(WorldMapScreen* worldmap_screen);
  void on_click();
  void draw (DrawingContext& gc);
  void on_pointer_enter();
};

class WorldmapScreenCreditsButton
  : public GUI::SurfaceButton
{
private:
  WorldmapScreen* worldmap_screen;
public:
  WorldmapScreenCreditsButton(WorldMapScreen* worldmap_screen);
  void on_click();
  void draw (DrawingContext& gc);
  void on_pointer_enter();
};

class WorldmapScreenEnterButton
  : public GUI::SurfaceButton
{
private:
  WorldmapScreen* worldmap_screen;
public:
  WorldmapScreenEnterButton(WorldMapScreen* worldmap_screen);
  void on_click();
  void draw (DrawingContext& gc);
  void on_pointer_enter();
};

WorldmapScreenCreditsButton::WorldMapScreenCreditsButton(WorldMapScreen* worldmap_screen)
  : GUI::SurfaceButton(Display::get_width() - 150, 0,
                       ResDescriptor("core/worldmap/credits_button_normal"),
                       ResDescriptor("core/worldmap/credits_button_pressed"),
                       ResDescriptor("core/worldmap/credits_button_hover")),
    worldmap_screen(worldmap_screen)
{
}

void
WorldmapScreenCreditsButton::on_pointer_enter()
{
  SurfaceButton::on_pointer_enter();
  Sound::PingusSound::play_sound ("tick");
}

void
WorldmapScreenCreditsButton::draw (DrawingContext& gc)
{
  SurfaceButton::draw(gc);
  gc.print_center(Fonts::chalk_small, Display::get_width() - 59 - 24, 2, _("Show Ending?"));
}

void
WorldmapScreenCreditsButton::on_click()
{
  ScreenManager::instance()->replace_screen
    (new StoryScreen(worldmap_screen->get_worldmap()->get_end_story()), true);
}

WorldmapScreenStoryButton::WorldMapScreenStoryButton(WorldMapScreen* worldmap_screen)
  : GUI::SurfaceButton(0, 0,
                       ResDescriptor("core/worldmap/story_button_normal"),
                       ResDescriptor("core/worldmap/story_button_pressed"),
                       ResDescriptor("core/worldmap/story_button_hover")),
    worldmap_screen(worldmap_screen)
{
}

void
WorldmapScreenStoryButton::on_pointer_enter()
{
  SurfaceButton::on_pointer_enter();
  Sound::PingusSound::play_sound ("tick");
}

void
WorldmapScreenStoryButton::draw (DrawingContext& gc)
{
  SurfaceButton::draw(gc);
  gc.print_center(Fonts::chalk_small, 59, 2, _("Show Story?"));
}

void
WorldmapScreenStoryButton::on_click()
{
  ScreenManager::instance()->replace_screen
    (new StoryScreen(worldmap_screen->get_worldmap()->get_intro_story()), true);
}

WorldmapScreenCloseButton::WorldMapScreenCloseButton(WorldMapScreen* worldmap_screen)
  : GUI::SurfaceButton(0, Display::get_height() - 37,
                       ResDescriptor("core/worldmap/leave_button_normal"),
                       ResDescriptor("core/worldmap/leave_button_pressed"),
                       ResDescriptor("core/worldmap/leave_button_hover")),
    worldmap_screen(worldmap_screen)
{
}

void
WorldmapScreenCloseButton::on_pointer_enter()
{
  SurfaceButton::on_pointer_enter();
  Sound::PingusSound::play_sound ("tick");
}

void
WorldmapScreenCloseButton::draw (DrawingContext& gc)
{
  SurfaceButton::draw(gc);
  gc.print_center(Fonts::chalk_small, 44, Display::get_height() - 25, _("Leave?"));
}

void
WorldmapScreenCloseButton::on_click()
{
  ScreenManager::instance ()->pop_screen ();
}

WorldmapScreenEnterButton::WorldMapScreenEnterButton(WorldMapScreen* worldmap_screen)
  : GUI::SurfaceButton(Display::get_width() - 119, Display::get_height() - 37,
                       ResDescriptor("core/worldmap/enter_button_normal"),
                       ResDescriptor("core/worldmap/enter_button_pressed"),
                       ResDescriptor("core/worldmap/enter_button_hover")),
    worldmap_screen(worldmap_screen)
{
}

void
WorldmapScreenEnterButton::on_pointer_enter()
{
  SurfaceButton::on_pointer_enter();
  if (!worldmap_screen->get_worldmap()->get_pingus()->is_walking())
    {
      Sound::PingusSound::play_sound ("tick");
    }
}

void
WorldmapScreenEnterButton::draw (DrawingContext& gc)
{
  if (worldmap_screen->get_worldmap()->get_pingus()->is_walking())
    {
      gc.draw(button_surface, Vector2i(x_pos, y_pos));
    }
  else
    {
      SurfaceButton::draw(gc);
      gc.print_center(Fonts::chalk_small,
                      Display::get_width() - 43 - 22,
                      Display::get_height() - 25,
                      _("Enter?"));
    }
}

void
WorldmapScreenEnterButton::on_click()
{
  worldmap_screen->get_worldmap()->enter_level();
}

WorldmapScreen::WorldMapScreen ()
  : levelname_bg(Sprite("core/worldmap/levelname_bg")),
    is_init(false),
    exit_worldmap(false),
    worldmap(0),
    new_worldmap(0)
{
  // FIXME: a bit ugly because of the proteced member, but should work
  // FIXME: well enough. GUIScreen could also use multi-inheritage,
  // FIXME: but that could lead to member function name conflicts
  gui_manager->add(new WorldmapComponent(this), true);
  gui_manager->add(new WorldmapScreenCloseButton(this), true);
  gui_manager->add(new WorldmapScreenEnterButton(this), true);
  gui_manager->add(new WorldmapScreenStoryButton(this), true);
}

void
WorldmapScreen::load (const std::string& filename)
{
  if (worldmap)
    delete worldmap;

  worldmap = new Worldmap(filename);
	
  bool credits_unlocked = false;
  StatManager::instance()->get_bool(worldmap->get_shortname() + "-endstory-seen", 
                                    credits_unlocked);
  if (credits_unlocked)
    {
      gui_manager->add(new WorldmapScreenCreditsButton(this), true);
    }
}

void
WorldmapScreen::on_startup ()
{
  exit_worldmap = false;
  Sound::PingusSound::stop_music();

  if (worldmap)
    worldmap->on_startup ();
}

WorldmapScreen::~WorldMapScreen ()
{
  delete worldmap;
  delete new_worldmap;
}

void
WorldmapScreen::on_escape_press ()
{
  //std::cout << "WorldmapScreen::on_escape_press ()..." << std::endl;
  exit_worldmap = true;
}

void
WorldmapScreen::update (float delta)
{
  GUIScreen::update(delta);

  // Exit the word
  if (exit_worldmap)
    ScreenManager::instance ()->pop_screen ();

  // Check if new worldmap is set and if so, change it
  if (new_worldmap)
    {
      delete worldmap;
      worldmap     = new_worldmap;
      new_worldmap = 0;
    }
}

void
WorldmapScreen::draw_foreground(DrawingContext& gc)
{
  // Draw the levelname
  gc.draw(levelname_bg,
          Vector2i(gc.get_width()/2 - levelname_bg.get_width()/2,
                   gc.get_height() - levelname_bg.get_height()));

  gc.print_center(Fonts::chalk_small, gc.get_width()/2, gc.get_height() - 25,
                  worldmap->get_levelname());
}

void
WorldmapScreen::change_map (const std::string& filename, NodeId node)
{
  // Create the new worldmap and make it the current one
  new_worldmap = new Worldmap (path_manager.complete("worldmaps/" + filename));
  new_worldmap->set_pingus (node);
}

Rect
WorldmapScreen::get_trans_rect() const
{
  return Rect(Vector2i(Math::max((Display::get_width()  - worldmap->get_width())/2,  0),
                       Math::max((Display::get_height() - worldmap->get_height())/2, 0)), 
              Size(Math::min(Display::get_width(),  worldmap->get_width()),
                   Math::min(Display::get_height(), worldmap->get_height())));
}

/* EOF */
