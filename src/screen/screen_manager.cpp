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

#include "SDL.h"
#include <iostream>
#include "../delta_manager.hpp"
#include "../globals.hpp"
#include "math/size.hpp"
#include "pathname.hpp"
#include "display/display.hpp"
#include "screen_manager.hpp"
#include "../path_manager.hpp"
#include "screen.hpp"
#include "fps_counter.hpp"
#include "../display/drawing_context.hpp"
#include "../input/controller.hpp"
#include "../input/manager.hpp"

ScreenManager* ScreenManager::instance_ = 0;

ScreenManager::ScreenManager()
  : display_gc(new DrawingContext())
{  
  assert(instance_ == 0);
  instance_ = this;
  cached_action = CA_NONE;
  
  input_manager = std::auto_ptr<Input::Manager>(new Input::Manager());

  if (controller_file.empty())
    input_controller = std::auto_ptr<Input::Controller>(input_manager->create_controller(Pathname("controller/default.scm", 
                                                                                                  Pathname::DATA_PATH)));
  else
    input_controller = std::auto_ptr<Input::Controller>(input_manager->create_controller(Pathname(controller_file,
                                                                                                  Pathname::SYSTEM_PATH)));

  cursor = Sprite("core/cursors/animcross");
  fps_counter = std::auto_ptr<FPSCounter>(new FPSCounter());
}

ScreenManager::~ScreenManager ()
{
  instance_ = 0;
}

void
ScreenManager::display()
{
  show_swcursor(swcursor_enabled);
  DeltaManager delta_manager;
  DeltaManager frame_timer;

  // Main loop for the menu
  // and incidentally this is also the main loop for the whole game
  while (!screens.empty())
    {
      // how long the previous frame (iteration) took (if any)
      float time_delta = delta_manager.getset();
      // start the frame timer
      frame_timer.set();

      // previous frame took more than one second
      if (time_delta > 1.0)
	{
          if (maintainer_mode)
            std::cout << "ScreenManager: detected large delta (" << time_delta
                      << "), ignoring and doing frameskip" << std::endl;
	  continue; // skip this frame
	}

      last_screen = get_current_screen();
            
      // update the input
      input_manager->update(time_delta);
      std::vector<Input::Event> events = input_controller->poll_events();
      for(std::vector<Input::Event>::iterator i = events.begin(); 
          i != events.end() && last_screen == get_current_screen(); 
          ++i)
        {
          get_current_screen()->update(*i);
        }
      get_current_screen()->update(time_delta);

      if (swcursor_enabled)
        cursor.update(time_delta);

      // Last screen has popped, so we are going to end here
      if (screens.empty())
	continue;

      while (cached_action != CA_NONE)
        {
          switch (cached_action)
            {
            case CA_POP:
              real_pop_screen();
              break;
            case CA_POP_ALL:
              real_pop_all_screens();
              break;
            case CA_REPLACE:
              real_replace_screen(replace_screen_arg);
              break;
            case CA_CLEAR:
              real_clear();
              break;
            default:
              break;
            }
        }

      // FIXME: is there a more gentel way to do that instead of spreading the checks all around here?
      // Last screen has poped, so we are going to end here
      if (screens.empty())
	continue;

      // skip draw if the screen changed to avoid glitches
      if (last_screen == get_current_screen())
      	{
	  if (get_current_screen()->draw(*display_gc))
            {
              display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                                 Display::get_height())));

              if (swcursor_enabled)
                {
                  Vector2f mouse_pos = Input::Controller::current()->get_pointer(Input::STANDARD_POINTER)->get_pos();
                  cursor.draw(mouse_pos.x, mouse_pos.y, Display::get_screen());
                }

              if (print_fps)
                fps_counter->draw();

              Display::flip_display();
              display_gc->clear();
            }
        }
      else
	{
	  //std::cout << "ScreenManager: fading screens" << std::endl;
	  //FIXME: this shouldn't be done in one iteration of this loop (one frame)
	  fade_over(last_screen, get_current_screen());
	}

      // save this value because it might change drastically within the if statement
      float current_frame_time = frame_timer.get();
      // cap the framerate at the desired value
      if (current_frame_time < 1 / desired_fps) {
	// idle delay to make the frame take as long as we want it to
	SDL_Delay(static_cast<Uint32>(1000 *((1 / desired_fps) - current_frame_time)));
      }
    }
}

ScreenPtr
ScreenManager::get_current_screen()
{
  assert(!screens.empty());
  return screens.back ();
}

ScreenManager*
ScreenManager::instance ()
{
  return instance_;
}

void
ScreenManager::push_screen (Screen* screen)
{
  if (!screens.empty())
    {
      screens.back()->on_shutdown();
    }

  screens.push_back(ScreenPtr(screen));
  screen->on_startup();
}

void
ScreenManager::pop_screen ()
{
  assert(cached_action == CA_NONE);
  cached_action = CA_POP;
}

void
ScreenManager::pop_all_screens()
{
  assert(cached_action == CA_NONE);
  cached_action = CA_POP_ALL;
}

void
ScreenManager::replace_screen (Screen* screen)
{
  assert(cached_action == CA_NONE);
  cached_action = CA_REPLACE;
  replace_screen_arg = ScreenPtr(screen);
}

void
ScreenManager::real_replace_screen (ScreenPtr ptr)
{
  cached_action = CA_NONE;
  screens.back()->on_shutdown ();
  screens.back() = ptr;

  if (screens.back()->get_size() != Display::get_size())
    screens.back()->resize(Display::get_size());
  screens.back()->on_startup();
}

void
ScreenManager::real_pop_screen ()
{
  cached_action = CA_NONE;
  ScreenPtr back = screens.back ();
  screens.pop_back();
  back->on_shutdown();

  if (!screens.empty ())
    {
      if (screens.back()->get_size() != Display::get_size())
        screens.back()->resize(Display::get_size());
      screens.back()->on_startup();
    }
}

void
ScreenManager::real_pop_all_screens()
{
  cached_action = CA_NONE;
  ScreenPtr back = screens.back();
  screens.pop_back();
  back->on_shutdown();

  screens.clear();
}

void
ScreenManager::clear()
{
  cached_action = CA_CLEAR;
}

void
ScreenManager::real_clear()
{
  cached_action = CA_NONE;
  screens.clear();
}

void
ScreenManager::fade_over(ScreenPtr old_screen, ScreenPtr new_screen)
{
  DeltaManager delta_manager;
  float passed_time = 0;

  float progress = 0.0f;
  while (progress <= 1.0f)
    {
      float time_delta = delta_manager.getset ();
      passed_time += time_delta;

      int border_x = int((Display::get_width()/2)  * (1.0f - progress));
      int border_y = int((Display::get_height()/2) * (1.0f - progress));

      old_screen->draw(*display_gc);
      display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                         Display::get_height())));
      display_gc->clear();
      
      Display::push_cliprect(Rect(Vector2i(0 + border_x, 0 + border_y),
                                  Size(Display::get_width()  - 2*border_x, 
                                       Display::get_height() - 2*border_y)));

      new_screen->draw(*display_gc);
      display_gc->render(Display::get_screen(), Rect(Vector2i(0,0), Size(Display::get_width(),
                                                                         Display::get_height())));
      display_gc->clear();

      //GameDelta delta (time_delta, CL_System::get_time(), events);
      // FIXME: Animation looks nifty but doesn't work all that good
      //new_screen->update (delta);
      //old_screen->update (delta);
      
      Display::pop_cliprect();
      Display::flip_display ();
      display_gc->clear();
      
      progress = passed_time/1.0f;
    }
}

void
ScreenManager::resize(const Size& size)
{
  display_gc->set_rect(Rect(Vector2i(0, 0), size));

  // FIXME: Calling this causes horrible flicker, since the screen
  // goes black on a size change. Seems to be an SDL issue.
  Display::set_video_mode(size.width, size.height);

  // FIXME: We need to resize the other screens too
  get_current_screen()->resize(size);
}

void
ScreenManager::show_swcursor(bool visible)
{
  swcursor_enabled = visible;
  if (swcursor_enabled)
    {
      SDL_ShowCursor(SDL_DISABLE);
    }
  else
    {
      SDL_ShowCursor(SDL_ENABLE);
    }
}

/* EOF */
