//  $Id: smallmap.cpp 3608 2008-07-01 01:43:36Z grumbel $
//
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

#include "../game_session.hpp"
#include "../pingu_holder.hpp"
#include "../display/display.hpp"
#include "../display/drawing_context.hpp"
#include "../world.hpp"
#include "../resource.hpp"
#include "../col_map.hpp"
#include "../server.hpp"
#include "../smallmap_image.hpp"
#include "../pingu.hpp"
#include "../math.hpp"
#include "../math/vector3f.hpp"
#include "../globals.hpp"
#include "playfield.hpp"
#include "smallmap.hpp"

SmallMap::SmallMap(Server* server_, Playfield* playfield_)
  : server(server_),
    playfield(playfield_),
    gc_ptr(0)
{
  int max_width = 175;
  int max_height = 100;

  int min_height = 70;
  int min_width = 100;

  World* world = server->get_world();

  // Scaling values used in order to keep the aspect ratio
  int x_scaling = world->get_width()  / max_width;
  int y_scaling = world->get_height() / max_height;

  // If at best one horizontal pixel in the smallmap represents more colmap
  // pixels than one vertical pixel
  if (x_scaling > y_scaling)
    {
      width  = max_width;
      height = Math::max(min_height, world->get_height() / x_scaling);
    }
  else
    {
      width  = Math::max(min_width, world->get_width() / y_scaling);
      height = max_height;
    }
  
  x_pos   = 5;
  y_pos   = Display::get_height() - height - 5;

  image = new SmallMapImage(server, width, height);

  scroll_mode = false;
}

SmallMap::~SmallMap()
{
  delete image;
}

void
SmallMap::draw (DrawingContext& gc)
{
  // FIXME: This is potentially dangerous, since we don't know how
  // long 'gc' will be alive. Should use a DrawingContext for caching.
  gc_ptr = &gc;

  World* const& world  = server->get_world();
  
  Vector2i of = playfield->get_pos();
  Rect rect;

  if (world->get_width() > gc.get_width())
    {
      int rwidth = int(gc.get_width()  * width  / world->get_width());
      rect.left  = x_pos + (of.x * width  / world->get_width()) - rwidth/2;
      rect.right = rect.left + rwidth;
    }
  else
    {
      rect.left  = x_pos;
      rect.right = x_pos + width;
    }

  if (world->get_height() > gc.get_height())
    {
      int rheight = int(gc.get_height() * height / world->get_height());
      rect.top    = y_pos + (of.y * height / world->get_height()) - rheight/2;
      rect.bottom = rect.top + rheight;
    }
  else
    {
      rect.top    = y_pos;
      rect.bottom = y_pos + height;
    }
  
  gc.draw(image->get_surface(), Vector2i(x_pos, y_pos));
  gc.draw_rect(rect.left, rect.top, rect.right, rect.bottom,
               Color(0, 255, 0));

  server->get_world()->draw_smallmap(this);

  // Draw Pingus
  PinguHolder* pingus = world->get_pingus();
  for(PinguIter i = pingus->begin(); i != pingus->end(); ++i)
    {
      int x = static_cast<int>(x_pos + ((*i)->get_x() * width  / world->get_width()));
      int y = static_cast<int>(y_pos + ((*i)->get_y() * height / world->get_height()));

      gc.draw_line(x, y, x, y-2, Color(255, 255, 0));
    }

  gc_ptr = 0;
}

void
SmallMap::update (float delta)
{
  image->update(delta);
}

void
SmallMap::draw_sprite(Sprite sprite, Vector3f pos)
{
  World* world = server->get_world();
  float x = x_pos + (pos.x * width  / world->get_width());
  float y = y_pos + (pos.y * height / world->get_height());

  gc_ptr->draw(sprite, Vector3f(x, y));
}

bool
SmallMap::is_at (int x, int y)
{
  return (x > x_pos && x < x_pos + (int)width
	  && y > y_pos && y < y_pos + (int)height);
}

void
SmallMap::on_pointer_move (int x, int y)
{
  int cx, cy;
  World* world = server->get_world();

  if (scroll_mode)
    {
      cx = (x - x_pos) * static_cast<int>(world->get_width()  / width);
      cy = (y - y_pos) * static_cast<int>(world->get_height() / height);

      playfield->set_viewpoint(cx, cy);
    }
}

void
SmallMap::on_primary_button_press (int x, int y)
{
  scroll_mode = true;

  // set view to the given COs
  int cx, cy;
  World* world = server->get_world();
  cx = (x - x_pos) * int(world->get_width()) / width;
  cy = (y - y_pos) * int(world->get_height()) / height ;
  playfield->set_viewpoint(cx, cy);
}

void
SmallMap::on_primary_button_release(int x, int y)
{
  scroll_mode = false;
  UNUSED_ARG(x);
  UNUSED_ARG(y);
}

void
SmallMap::on_pointer_enter ()
{
  has_focus = true;
}

void
SmallMap::on_pointer_leave ()
{
  has_focus = false;
}

/* EOF */
