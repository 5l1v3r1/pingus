//  $Id: smoke_particle.cxx,v 1.4 2002/10/04 11:38:29 torangan Exp $
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

#include "../globals.hxx"
#include "../pingus_resource.hxx"
#include "smoke_particle.hxx"

CL_Surface SmokeParticle::surf1;
CL_Surface SmokeParticle::surf2;

SmokeParticle::SmokeParticle()
{
}

// FIXME: Why the heck do I get an unresolved reference in
// WoodThing.cc when I try to use SmokeParticle there?!
SmokeParticle::SmokeParticle (int x, int y, float x_a, float y_a)
  : Particle (x, y, x_a, y_a)
{
  // FIXME: Probably slow??
  if (rand() % 2)
    {
      if (!surf1)
	surf1 = PingusResource::load_surface("Particles/smoke", "pingus");
      surface = surf1;
    }
  else
    {
      if (!surf2)
	surf2 = PingusResource::load_surface("Particles/smoke2", "pingus");
      surface = surf2;
    }

  livetime = 25 + (rand() % 10);
  time = livetime;
}

void
SmokeParticle::update (float delta)
{
  pos.x += velocity.x;
  pos.y += velocity.y;
  //  y_add += 0.1;

  if (livetime > 0)
    --livetime;
    
  UNUSED_ARG(delta);
}

void
SmokeParticle::draw_offset(int ofx, int ofy, float s)
{
  if (fast_mode)
    return;

  if (s == 1.0) {
    // FIXME: This segfaults from time to time, don't know why
    surface.put_screen(static_cast<int>(pos.x + ofx - 16),
                       static_cast<int>(pos.y + ofy - 16),
		       3 - (livetime * 4 / time));
  } else {
    int width  = static_cast<int>(surface.get_width() * s);
    int height = static_cast<int>(surface.get_height() * s);
    surface.put_screen(static_cast<int>((pos.x + ofx) * s) - width  / 2,
		       static_cast<int>((pos.y + ofy) * s) - height / 2,
		       width, height, 3 - (livetime * 4 / time));
  }
}

/* EOF */
