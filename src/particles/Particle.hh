//  $Id: Particle.hh,v 1.4 2000/06/18 17:01:50 grumbel Exp $
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

#ifndef PARTICLE_HH
#define PARTICLE_HH

#include <ClanLib/core.h>

#include "../PinguMap.hh"
#include "../ColMap.hh"

///
class Particle
{
protected:
  ///
  static PinguMap* map;
  ///
  static ColMap*   colmap;

  ///
  CL_Surface* surface;
  ///
  float x_pos;
  ///
  float y_pos;

  ///
  float x_add;
  ///
  float y_add;
  ///
  int livetime;
public:
  ///
  Particle();
  ///
  Particle(int x, int y, float x_a, float y_a);

  ///
  virtual ~Particle();

  ///
  static void set_map(PinguMap* m);

  /// Reinit a allready created particle with now coordinates
  virtual void init(int x, int y, float x_a, float y_a);

  // If false is returned the particle gets deleted by the
  /// ParticleHolder 
  virtual bool is_alive(void);

  /// Let the particle move
  virtual void let_move(void);

  /// Draw the particle with the correct zoom resize
  virtual void draw_offset(int, int, float) const;
}///
;

#endif

/* EOF */
