//  $Id: story_screen.cxx,v 1.15 2003/04/10 15:40:18 grumbel Exp $
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

#include <algorithm>
#include <vector>
#include <ClanLib/Display/Display/surface.h>
#include "my_gettext.hxx"
#include "pingus_resource.hxx"
#include "gui/gui_manager.hxx"
#include "gui/surface_button.hxx"
#include "gui/screen_manager.hxx"
#include "gui/component.hxx"
#include "math.hxx"
#include "pingus_menu_manager.hxx"
#include "fonts.hxx"
#include "story_screen.hxx"
#include "res_descriptor.hxx"
#include "worldmap/manager.hxx"
#include "stat_manager.hxx"
#include "story.hxx"
#include "credits.hxx"
#include "sound/sound.hxx"

class StoryScreenComponent : public GUI::Component
{
private:
  bool show_credits;

  CL_Surface background;
  std::string display_text;
  float time_passed;

  bool page_displayed_completly;

  Story story;
  CL_Surface page_surface;
  StoryPage  current_page;
public:
  StoryScreenComponent (const Story&);
  virtual ~StoryScreenComponent () {}

  void draw (GraphicContext& gc);
  void update(float delta);

  /** starts to display the next text page */
  void next_text();
};

class StoryScreenContinueButton : public GUI::SurfaceButton
{
private:
  StoryScreenComponent* story_comp;
public:
  StoryScreenContinueButton(StoryScreenComponent* arg_story_comp)
    : GUI::SurfaceButton(620, 460, 
                         ResDescriptor("misc/next", "core", ResDescriptor::RD_RESOURCE),
                         ResDescriptor("misc/next", "core", ResDescriptor::RD_RESOURCE),
                         ResDescriptor("misc/next_hover", "core", ResDescriptor::RD_RESOURCE)),
      story_comp(arg_story_comp)
  {
  }

  void on_pointer_enter()
  {
    SurfaceButton::on_pointer_enter();
    PingusSound::play_sound ("tick", .3);
  }

  void on_click() 
  {
    story_comp->next_text();
    //ScreenManager::instance()->replace_screen (PingusMenuManager::instance (), false);
  }
};


StoryScreen::StoryScreen(const Story& arg_pages)
{
  story_comp = new StoryScreenComponent(arg_pages);
  gui_manager->add (story_comp);
  gui_manager->add (new StoryScreenContinueButton(story_comp));
}

StoryScreen::~StoryScreen()
{
}

StoryScreenComponent::StoryScreenComponent (const Story& arg_story)
  : story(arg_story)
{
  if (&arg_story == &Story::credits)
    show_credits = true;
  else
    show_credits = false;

  page_displayed_completly = false;
  time_passed  = 0;

  current_page = story.pages.back();
  page_surface = PingusResource::load_surface(current_page.image);
  background   = PingusResource::load_surface("menu/startscreenbg", "core");
}

void
StoryScreenComponent::draw (GraphicContext& gc)
{
  gc.draw(background, 0, 0);
  gc.print_center(Fonts::chalk_large, CL_Display::get_width()/2, 100, story.title);
  gc.draw(page_surface,  gc.get_width()/2 - page_surface.get_width()/2,
          160);
  gc.print_left(Fonts::chalk_normal, 120, 335, display_text);
}

void
StoryScreenComponent::update(float delta)
{
  time_passed += delta;

  if (!page_displayed_completly)
    {
      int i = Math::min(current_page.text.length(), (unsigned int)(15.0f * time_passed));
      display_text = current_page.text.substr(0, i);

      if (current_page.text.length() < (unsigned int)(15.0f * time_passed))
        {
          page_displayed_completly = true;
        }
    }
}

void
StoryScreen::on_fast_forward_press ()
{
  story_comp->next_text();
}

void
StoryScreen::on_escape_press ()
{
  if (1 /* story_seen */)
    ScreenManager::instance()->replace_screen(WorldMapNS::WorldMapManager::instance ());
}

void 
StoryScreen::on_startup()
{
  //PingusSound::play_sound ("letsgo");
  PingusSound::play_music("pingus-4.it", .7f);
}

void
StoryScreenComponent::next_text()
{
  if (!page_displayed_completly)
    {
      page_displayed_completly = true;
      display_text = current_page.text;  
    }
  else
    {
      story.pages.pop_back();
      if (!story.pages.empty())
        {
          current_page = story.pages.back();
          page_surface = PingusResource::load_surface(current_page.image);
          display_text = "";
          time_passed = 0;
          page_displayed_completly = false;
        }
      else
        {
          //std::cout << "StoryScreenComponent: Out of story pages" << std::endl;
          StatManager::instance()->set_bool("story-seen", true);
          //ScreenManager::instance()->replace_screen (PingusMenuManager::instance (), false);
          if (show_credits)
            ScreenManager::instance()->replace_screen(Credits::instance(), false);
          else
            ScreenManager::instance()->replace_screen(WorldMapNS::WorldMapManager::instance ());
        }
    }
}

// Local Variables: ***
// coding:iso-latin-1
// End: ***

/* EOF */
