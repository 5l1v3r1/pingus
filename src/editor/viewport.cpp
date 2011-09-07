//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Jason Green <jave27@gmail.com>,
//                     Ingo Ruhnke <grumbel@gmx.de>
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

#include "editor/viewport.hpp"

#include <boost/format.hpp>

#include "editor/editor_level.hpp"
#include "editor/level_objs.hpp"
#include "engine/display/display.hpp"
#include "util/log.hpp"
#include "util/utf8.hpp"

namespace Editor {

static const int keyboard_movement_distance = 32;

// Constructor
Viewport::Viewport(EditorScreen* e, const Rect& rect_)  :
  RectComponent(rect_),
  state(rect.get_width(), rect.get_height()),
  drawing_context(new DrawingContext(rect)),
  editor(e),
  autoscroll(false),
  mouse_world_pos(),
  mouse_screen_pos(),
  drag_world_pos(),
  drag_screen_pos(),
  selection(),
  highlighted_area(0,0,0,0),
  context_menu(),
  snap_to(false),
  current_action(NOTHING),
  selection_changed()
{
}

// Destructor
Viewport::~Viewport ()
{
  delete drawing_context;
}

void
Viewport::on_secondary_button_press(int x_, int y_)
{
  mouse_world_pos = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);

  if (current_action == NOTHING)
  {
    drag_screen_pos = mouse_screen_pos;  
    current_action = SCROLLING;
  }
}

void
Viewport::on_secondary_button_release(int x_, int y_)
{
  mouse_world_pos = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);

  if (current_action == SCROLLING)
    current_action = NOTHING;
}

// When someone right-clicks inside the viewport
void
Viewport::on_secondary_button_click(int x_, int y_)
{
  mouse_world_pos = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);
}

// Select 1 or more LevelObjs, or drag them.
void 
Viewport::on_primary_button_press(int x_, int y_)
{
  mouse_world_pos  = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);
  
  if (current_action == NOTHING)
  {
    LevelObj* obj = editor->get_level()->object_at(mouse_world_pos.x, mouse_world_pos.y);

    if (obj)
    {
      // If the currently selected object isn't selected, select it and deselect the rest
      if (!obj->is_selected())
      {
        clear_selection();
        obj->select();
        selection.insert(obj);

        selection_changed(selection);
      }

      for (auto it = selection.begin(); it != selection.end(); ++it) 
      {
        (*it)->set_orig_pos((*it)->get_pos());
      }

      // Allow dragging of the currently selected objects
      current_action = DRAGGING;
      drag_world_pos = mouse_world_pos;
    }
    else
    {
      current_action = HIGHLIGHTING;
      highlighted_area.left = highlighted_area.right  = mouse_world_pos.x;
      highlighted_area.top  = highlighted_area.bottom = mouse_world_pos.y;

      clear_selection();

      selection_changed(selection);
    }
  }
}

void 
Viewport::on_primary_button_release(int x_, int y_)
{
  mouse_world_pos = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);

  if (current_action == HIGHLIGHTING)
  {
    highlighted_area.normalize();
    for (unsigned i = 0; i < get_objects()->size(); i++)
    {
      if (highlighted_area.contains(Vector2i(int((*get_objects())[i]->get_pos().x),
                                             int((*get_objects())[i]->get_pos().y))))
      {
        selection.insert((*get_objects())[i]);
        (*get_objects())[i]->select();
      }
      else
      {
        (*get_objects())[i]->unselect();
      }
    }

    selection_changed(selection);
  }
  else if (current_action == DRAGGING)
  {
    // Set the objects' positions for good
    for (unsigned i = 0; i < (*get_objects()).size(); i++)
      (*get_objects())[i]->set_orig_pos((*get_objects())[i]->get_pos());
  }
  current_action = NOTHING;
}

void
Viewport::on_pointer_move(int x_, int y_)
{
  mouse_world_pos = screen2world(x_, y_);
  mouse_screen_pos = Vector2i(x_, y_);
  
  switch(current_action)
  {
    case HIGHLIGHTING:
      highlighted_area.right  = mouse_world_pos.x;
      highlighted_area.bottom = mouse_world_pos.y;
      break;
        
    case DRAGGING:
      {
        float new_x, new_y;

        for (auto it = selection.begin(); it != selection.end(); ++it)
        {
          Vector3f orig_pos((*it)->get_orig_pos());
          float x_offset = static_cast<float>(mouse_world_pos.x - drag_world_pos.x);
          float y_offset = static_cast<float>(mouse_world_pos.y - drag_world_pos.y);

          if (snap_to)
          {
            // FIXME: May need to adjust the snap-to offset here.
            new_x = static_cast<float>(static_cast<int>((x_offset + orig_pos.x) / 10) * 10);
            new_y = static_cast<float>(static_cast<int>((y_offset + orig_pos.y) / 10) * 10);
          }
          else
          {
            new_x = x_offset + orig_pos.x;
            new_y = y_offset + orig_pos.y;
          }
          (*it)->set_pos(Vector3f(new_x, new_y, orig_pos.z));
        }
      }
      break;

    case SCROLLING:
      break;
        
    case NOTHING:
      break;
  }
}

void
Viewport::on_key_pressed(const Input::KeyboardEvent& ev)
{
  switch(ev.keysym.sym)
  {
    case SDLK_a:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        clear_selection();
        selection_changed(selection);
      }
      else
      {
        if (selection.size() == get_objects()->size())
        {
          clear_selection();
        }
        else 
        {
          clear_selection();
          selection.insert(get_objects()->begin(), get_objects()->end());
          for (auto it = selection.begin(); it != selection.end(); ++it)
          {
            (*it)->select();
          }
        }
        selection_changed(selection);
      }
      break;

    case SDLK_PAGEUP:
    case SDLK_RIGHTBRACKET:
    case SDLK_w:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        raise_objects_to_top();
      }
      else
      {
        raise_objects();
      }
      break;

    case SDLK_PAGEDOWN:
    case SDLK_LEFTBRACKET:
    case SDLK_s:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        lower_objects_to_bottom();
      }
      else
      {
        lower_objects();
      }
      break;

    case SDLK_r:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        rotate_270_selected_objects();
      }
      else
      {
        rotate_90_selected_objects();
      }
      break;
            
    case SDLK_DELETE:
    case SDLK_BACKSPACE:
      delete_selected_objects();
      break;
             
    case SDLK_d:
      duplicate_selected_objects();
      break;

    case SDLK_f:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        vflip_selected_objects();       
      }
      else
      {
        hflip_selected_objects();
      }
      break;

    case SDLK_v:
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        hflip_selected_objects();
      }
      else
      {
        vflip_selected_objects();
      }
      break;
            
    case SDLK_c: // dvorak-up
    case SDLK_i: // up
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        move_objects(Vector2i(0,-keyboard_movement_distance));
      }
      else
      {
        move_objects(Vector2i(0,-1));
      }
      break;

    case SDLK_t: // dvorak-down
    case SDLK_k: // down
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        move_objects(Vector2i(0, keyboard_movement_distance));       
      }
      else
      {
        move_objects(Vector2i(0,1));
      }
      break;

    case SDLK_h: // dvorak-left
    case SDLK_j: // left
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        move_objects(Vector2i(-keyboard_movement_distance, 0));
      }
      else
      {
        move_objects(Vector2i(-1,0));
      }
      break;

    case SDLK_n: // dvorak-right
    case SDLK_l: // right
      if (ev.keysym.mod & KMOD_SHIFT)
      {
        move_objects(Vector2i(keyboard_movement_distance, 0));
      }
      else
      {
        move_objects(Vector2i(1,0));
      }
      break;
      
    default:
      log_debug("Viewport::on_key_pressed: " << ev.keysym.sym 
                << " U+" << (boost::format("%04x") % ev.keysym.unicode)
                << " " << UTF8::encode_utf8(ev.keysym.unicode));
      break;
  }
}

// Draws all of the objects in the viewport and the background (if any)
void
Viewport::draw(DrawingContext &gc)
{
  drawing_context->clear();
  drawing_context->fill_screen(Color(155,0,155));
  state.push(*drawing_context);
  
  // Level border
  drawing_context->draw_rect(Rect(Vector2i(0,0), editor->get_level()->get_size()), Color(255,255,255), 5000.0f);
  drawing_context->draw_rect(Rect(Vector2i(0,0), editor->get_level()->get_size()).grow(1), Color(0,0,0), 5000.0f);

  // Safe area
  drawing_context->draw_rect(Rect(Vector2i(0,0), editor->get_level()->get_size()).grow(-100), Color(155,155,155), 5000.0f);
        
  // Draw the level objects
  for (unsigned i = 0; i < (*get_objects()).size(); i++)
    (*get_objects())[i]->draw(*drawing_context);

  if (current_action == HIGHLIGHTING)
  {
    drawing_context->draw_fillrect(highlighted_area, Color(155,200,255, 100), 1000.0f);
    drawing_context->draw_rect(highlighted_area, Color(155,200,255), 1000.0f);
  }
  
  state.pop(*drawing_context);
  gc.draw(*drawing_context, -150);
}

// Returns true if the viewport is at the x,y coordinate
bool
Viewport::is_at(int x, int y)
{
  return drawing_context->get_rect().contains(Vector2i(x,y));
}

void
Viewport::update(float delta)
{
  if (current_action == SCROLLING)
  {
    state.set_pos(Vector2i(state.get_pos().x + static_cast<int>(static_cast<float>(mouse_screen_pos.x - drag_screen_pos.x) * 5.0f * delta),
                           state.get_pos().y + static_cast<int>(static_cast<float>(mouse_screen_pos.y - drag_screen_pos.y) * 5.0f * delta)));
  }
  
  // Autoscroll if necessary
  if (autoscroll)
  {
    const int autoscroll_border = 10;
    if (autoscroll)
    {
      if (mouse_screen_pos.x < autoscroll_border)
        state.set_pos(state.get_pos() - Vector2i(5, 0));
      else if (Display::get_width() - mouse_screen_pos.x < autoscroll_border)
        state.set_pos(state.get_pos() + Vector2i(5, 0));
      else if (mouse_screen_pos.y < autoscroll_border)
        state.set_pos(state.get_pos() - Vector2i(0, 5));
      else if (Display::get_height() - mouse_screen_pos.y < autoscroll_border)
        state.set_pos(state.get_pos() + Vector2i(0, 5));
    }
  }
}

void
Viewport::refresh()
{
  state.set_limit(Rect(Vector2i(0,0), editor->get_level()->get_size()).grow(256));
}

void
Viewport::duplicate_selected_objects()
{
  Selection new_selection;
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    LevelObj* clone = (*i)->duplicate(Vector2i(32, 32));
    if (clone)
    {
      new_selection.insert(clone);
      get_objects()->push_back(clone);
      clone->select();
    }
  }
  
  clear_selection();
  selection = new_selection;
  selection_changed(selection);  
}

void
Viewport::delete_selected_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
    (*i)->remove();
  
  (*get_objects()).erase(std::remove_if((*get_objects()).begin(), (*get_objects()).end(), boost::mem_fn(&LevelObj::is_removed)),
                         (*get_objects()).end());

  for(auto i = selection.begin(); i != selection.end(); ++i)
    delete (*i);

  selection.clear();
  selection_changed(selection);
}

void
Viewport::hflip_selected_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    (*i)->set_modifier(ResourceModifier::horizontal_flip((*i)->get_modifier()));
  }  
}

void
Viewport::vflip_selected_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    (*i)->set_modifier(ResourceModifier::vertical_flip((*i)->get_modifier()));
  }
}

void
Viewport::rotate_90_selected_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    (*i)->set_modifier(ResourceModifier::rotate_90((*i)->get_modifier()));
  }
}

void
Viewport::rotate_270_selected_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    (*i)->set_modifier(ResourceModifier::rotate_270((*i)->get_modifier()));
  }
}

Vector2i
Viewport::screen2world(int x, int y) const
{
  return state.screen2world(drawing_context->screen_to_world(Vector2i(x, y)));
}

void
Viewport::raise_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    editor->get_level()->raise_object(*i);
  }
}

void
Viewport::lower_objects()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
  {
    editor->get_level()->lower_object(*i);
  }
}

void
Viewport::raise_objects_to_top()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
    editor->get_level()->raise_object_to_top(*i);
}

void
Viewport::lower_objects_to_bottom()
{
  for(auto i = selection.begin(); i != selection.end(); ++i)
    editor->get_level()->lower_object_to_bottom(*i); 
}

void
Viewport::update_layout()
{
  state.set_size(rect.get_width(), rect.get_height());
  drawing_context->set_rect(rect);
}

void
Viewport::clear_selection()
{
  for (auto it = selection.begin(); it != selection.end(); ++it)
  {
    (*it)->unselect();
  }                
  selection.clear(); 
}

void
Viewport::move_objects(const Vector2i& offset)
{
  for (auto it = selection.begin(); it != selection.end(); ++it)
  {
    Vector3f p = (*it)->get_pos(); 
    (*it)->set_pos(Vector3f(p.x + static_cast<float>(offset.x),
                                       p.y + static_cast<float>(offset.y),
                                       p.z));
  }
}

Vector2i
Viewport::get_scroll_pos() const
{
  return state.get_pos();
}

void
Viewport::set_scroll_pos(const Vector2i& pos)
{
  state.set_pos(pos);
}

std::vector<LevelObj*>*
Viewport::get_objects()
{
  return editor->get_level()->get_objects();
}

} // namespace Editor

/* EOF */
