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

#include "gui/gui_manager.hpp"

#include <algorithm>
#include "pingus/debug.hpp"
#include "pingus/globals.hpp"
#include "input/event.hpp"
#include "display/display.hpp"

using namespace Input;

namespace GUI { 

GUIManager::GUIManager ()
  : GroupComponent(Rect(0, 0, Display::get_width(), Display::get_height()), false),
    mouse_pos(400,300)
{
}

GUIManager::GUIManager(const Rect& rect_)
  : GroupComponent(rect_),
    mouse_pos(400,300)
{
}

GUIManager::~GUIManager ()
{
}


void
GUIManager::update(float delta)
{
  GroupComponent::update(delta);
}

void
GUIManager::update(const Input::Event& event)
{
  switch (event.type)
    {
      case Input::POINTER_EVENT_TYPE:
        mouse_pos.x = int(event.pointer.x);
        mouse_pos.y = int(event.pointer.y);
        on_pointer_move(mouse_pos.x, mouse_pos.y);
        break;

      case Input::BUTTON_EVENT_TYPE:
        if (event.button.name == PRIMARY_BUTTON)
          {
            if (event.button.state == Input::BUTTON_PRESSED)
              on_primary_button_press(mouse_pos.x, mouse_pos.y);
            else if (event.button.state == Input::BUTTON_RELEASED)
              on_primary_button_release(mouse_pos.x, mouse_pos.y);
          }
        else if (event.button.name == SECONDARY_BUTTON)
          {
            if (event.button.state == Input::BUTTON_PRESSED)
              on_secondary_button_press(mouse_pos.x, mouse_pos.y);
            else if (event.button.state == Input::BUTTON_RELEASED)
              on_secondary_button_release(mouse_pos.x, mouse_pos.y);
          }
        break;

      case Input::AXIS_EVENT_TYPE:
        // AxisEvents can be ignored in the GUI, they are handled elsewhere
        pout(PINGUS_DEBUG_GUI) << "GUIManager: AxisEvent: " << event.axis.dir << std::endl;
        break;
	
      case Input::KEYBOARD_EVENT_TYPE:
        on_key_pressed(event.keyboard.key);
        break;

      case Input::SCROLLER_EVENT_TYPE:
        on_scroller_move(event.scroll.x_delta, event.scroll.y_delta);
        break;

      default:
        pwarn (PINGUS_DEBUG_GUI) << "GUIManager: unhandled event type " << event.type << std::endl;
        break;
    }
}

} // namespace GUI

/* EOF */
