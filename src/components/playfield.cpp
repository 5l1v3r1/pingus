//  $Id: playfield.cxx,v 1.40 2003/10/22 11:11:22 grumbel Exp $
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

#include <stdio.h>
#include <iostream>
#include "../globals.hxx"
#include "../pingu_holder.hxx"
#include "../display/drawing_context.hxx"
#include "../display/scene_context.hxx"
#include "../world.hxx"
#include "../server.hxx"
#include "../true_server.hxx"
#include "../pingu.hxx"
#include "../gui/display.hxx"
#include "button_panel.hxx"
#include "playfield.hxx"


Playfield::Playfield (Client* client_, const Rect& rect_)
  : rect(rect_),
    client(client_),
    buttons(client->get_button_panel()),
    current_pingu(0),
    // We keep the SceneContext has member variable so that we don't
    // have to reallocate it every frame, which is quite a costly operation
    scene_context(new SceneContext()),
    state(rect.get_width(), rect.get_height()),
    cap(client->get_button_panel())
{
  world              = client->get_server()->get_world();
  mouse_scrolling    = false;

  state.set_limit(Rect(Vector2i(0, 0), Size(world->get_width(), world->get_height())));
}

Playfield::~Playfield()
{
  delete scene_context;
}

void
Playfield::draw (DrawingContext& gc)
{
  scene_context->clear();
  scene_context->light().fill_screen(Color(50, 50, 50));
 
  state.push(*scene_context);

  cap.set_pingu(current_pingu);
  cap.draw(*scene_context);
  
  // Blank out the entire window in case the screen resolution is larger
  // than the current level.
  gc.draw_fillrect(0, 0, (float)Display::get_width(), (float)Display::get_height(),
                   Color(0,0,0), -15000);
  world->draw(*scene_context);
 
  // Draw the scrolling band
  if (mouse_scrolling && !drag_drop_scrolling)
    {
      gc.draw_line((float)mouse_pos.x, (float)mouse_pos.y,
                   (float)scroll_center.x, (float)scroll_center.y-15,
                   Color(0, 255, 0));

      gc.draw_line((float)mouse_pos.x, (float)mouse_pos.y,
                   (float)scroll_center.x, (float)scroll_center.y,
                   Color(255, 0, 0));

      gc.draw_line((float)mouse_pos.x, (float)mouse_pos.y,
                   (float)scroll_center.x, (float)scroll_center.y+15,
                   Color(0, 0, 255));

      gc.draw_line((float)mouse_pos.x, (float)mouse_pos.y,
                   (float)scroll_center.x + 15, (float)scroll_center.y,
                   Color(0, 255, 255));

      gc.draw_line((float)mouse_pos.x, (float)mouse_pos.y,
                   (float)scroll_center.x - 15, (float)scroll_center.y,
                   Color(255, 255, 0));
    }

  state.pop(*scene_context);
  gc.draw(new SceneContextDrawingRequest(scene_context, Vector3f(0,0,-10000)));
}

Pingu*
Playfield::current_pingu_find (const Vector2f& pos)
{
  double min_dist = 500.0;
  double dist;
  Pingu* c_pingu = 0;

  for (PinguIter pingu = world->get_pingus()->begin();
       pingu != world->get_pingus()->end();
       ++pingu)
    {
      if ((*pingu)->is_over(static_cast<int>(pos.x), static_cast<int>(pos.y)))
	{
	  dist = (*pingu)->dist(static_cast<int>(pos.x), static_cast<int>(pos.y));

	  if (dist < min_dist)
	    {
	      min_dist = dist;
	      c_pingu = *pingu;
	    }
	}
    }
  return c_pingu;
}

void
Playfield::update(float delta)
{
  // FIXME: This should be delta dependant
  if (!mouse_scrolling)
    {
      current_pingu = current_pingu_find(state.screen2world(mouse_pos));
      cap.set_pingu(current_pingu);
    }
  else
    {
      if (drag_drop_scrolling)
        {
          state.set_pos(old_state_pos + (scroll_center - mouse_pos));
        }
      else
        { 
          state.set_pos(Vector2f(state.get_pos().x - float(scroll_center.x - mouse_pos.x) * 0.2f,
                                 state.get_pos().y - float(scroll_center.y - mouse_pos.y) * 0.2f));
        }
    }

  if (auto_scrolling)
    {
      // FIXME: May need to modify this function if it's not gradient enough.
      scroll_speed = static_cast<int>(800 * delta);
      //std::cout << "scroll_speed: " << scroll_speed << std::endl;
    
      if (mouse_pos.x < 10)
	{
	  state.set_pos(state.get_pos() - Vector2i(scroll_speed, 0));
	}
      else if (mouse_pos.x > Display::get_width() - 10)
	{
	  state.set_pos(state.get_pos() + Vector2i(scroll_speed, 0));
	}

      if (mouse_pos.y < 10)
	{
	  state.set_pos(state.get_pos() - Vector2i(0, scroll_speed));
	}
      else if (mouse_pos.y > Display::get_height() - 10)
	{
	  state.set_pos(state.get_pos() + Vector2i(0, scroll_speed));	 
	}
    }
}

void
Playfield::on_primary_button_press(int x, int y)
{
  UNUSED_ARG(x);
  UNUSED_ARG(y);

  if (current_pingu)
    {
      server->send_pingu_action_event(current_pingu, buttons->get_action_name());
    }
}

void
Playfield::on_secondary_button_press (int x, int y)
{
  std::cout << "on_secondary_button_press" << std::endl;
  mouse_scrolling = true;
  scroll_center.x = x;
  scroll_center.y = y;

  old_state_pos = state.get_pos();
}

void
Playfield::on_secondary_button_release (int x, int y)
{
  std::cout << "on_secondary_button_release" << std::endl;

  UNUSED_ARG(x);
  UNUSED_ARG(y);

  mouse_scrolling = false;
}

void
Playfield::on_pointer_move (int x, int y)
{
  // FIXME: useless stuff, but currently the controller doesn't have a state
  mouse_pos.x = x;
  mouse_pos.y = y;
}

void
Playfield::set_server(Server* s)
{
  server = s;
}

Vector2i
Playfield::get_pos() const
{
  return Vector2i(static_cast<int>(state.get_pos().x), 
                  static_cast<int>(state.get_pos().y));
}

void
Playfield::set_viewpoint(int x, int y)
{
  state.set_pos(Vector2f(x, y));
}

void
Playfield::generate_clipping_rects(int x1, int y1, int x2, int y2)
{
  clipping_rectangles.push_back(Rect(0, 0, Display::get_width() - 1, y1));
  clipping_rectangles.push_back(Rect(0, y1, x1, y2+1));
  clipping_rectangles.push_back(Rect(x2+1, y1, Display::get_width() - 1, y2+1));
  clipping_rectangles.push_back(Rect(0, y2+1, Display::get_width() - 1, Display::get_height() - 1));
}

void
Playfield::scroll (int x, int y)
{
  state.set_pos(state.get_pos() + Vector2f(x, y));
}


/* EOF */
