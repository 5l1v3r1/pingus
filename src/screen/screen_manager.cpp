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

ScreenManager::~ScreenManager()
{
  instance_ = 0;
}

void
ScreenManager::display()
{
  show_swcursor(swcursor_enabled);
  
  Uint32 last_ticks = SDL_GetTicks();

  while (!screens.empty())
    {
      Uint32 ticks = SDL_GetTicks();
      float delta  = float(ticks - last_ticks)/1000.0f;

      // previous frame took more than one second
      if (delta > 1.0)
        {
          if (maintainer_mode)
            std::cout << "ScreenManager: detected large delta (" << delta
                      << "), ignoring and doing frameskip" << std::endl;
        }
      else
        {
          if (swcursor_enabled)
            cursor.update(delta);
  
          update(delta);
      
          // cap the framerate at the desired value
          if (delta < 1.0f / desired_fps) {
            // idle delay to make the frame take as long as we want it to
            SDL_Delay(static_cast<Uint32>(1000 *((1.0f / desired_fps) - delta)));
          }
        }

      last_ticks   = ticks;
    }
}
 
void
ScreenManager::update(float delta)
{
  ScreenPtr last_screen = get_current_screen();
            
  // update the input, break away as soon as the current screen changed
  input_manager->update(delta);
  std::vector<Input::Event> events = input_controller->poll_events();
  for(std::vector<Input::Event>::iterator i = events.begin(); 
      i != events.end();
      ++i)
    {
      last_screen->update(*i);
      if (last_screen != get_current_screen())
        {
          fade_over(last_screen, get_current_screen());
          return;
        }
    }

  last_screen->update(delta);
  if (last_screen != get_current_screen())
    {
      fade_over(last_screen, get_current_screen());
      return;
    }

  // Draw screen
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

ScreenPtr
ScreenManager::get_current_screen()
{
  if (screens.empty())
    return ScreenPtr();
  else
    return screens.back();
}

ScreenManager*
ScreenManager::instance()
{
  return instance_;
}

void
ScreenManager::push_screen (Screen* screen)
{ 
  if (!screens.empty())
    screens.back()->on_shutdown();

  screens.push_back(ScreenPtr(screen));
  screen->on_startup();
}

void
ScreenManager::pop_screen()
{
  ScreenPtr back = screens.back();
  screens.pop_back();
  back->on_shutdown();

  if (!screens.empty())
    {
      if (screens.back()->get_size() != Display::get_size())
        screens.back()->resize(Display::get_size());
      screens.back()->on_startup();
    }
}

void
ScreenManager::pop_all_screens()
{
  ScreenPtr back = screens.back();
  screens.pop_back();
  back->on_shutdown();

  screens.clear();
}

void
ScreenManager::replace_screen (Screen* screen)
{
  screens.back()->on_shutdown();
  screens.back() = ScreenPtr(screen);

  if (screens.back()->get_size() != Display::get_size())
    screens.back()->resize(Display::get_size());
  screens.back()->on_startup();

}

void
ScreenManager::fade_over(ScreenPtr old_screen, ScreenPtr new_screen)
{
  if (!old_screen.get() || !new_screen.get())
    return;
  
  Uint32 last_ticks = SDL_GetTicks();
  float progress = 0.0f;
  while (progress <= 1.0f)
    {
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
      
      Display::pop_cliprect();
      Display::flip_display();
      display_gc->clear();
      
      progress = (SDL_GetTicks() - last_ticks)/1000.0f;
    }
}

void
ScreenManager::resize(const Size& size_)
{
  Size size(size_);

  // Limit Window size so some reasonable minimum
  if (size.width  < 640) size.width  = 640;
  if (size.height < 480) size.height = 480;

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
