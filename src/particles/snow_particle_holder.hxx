//  $Id: snow_particle_holder.hxx,v 1.2 2002/12/31 14:34:19 torangan Exp $
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

#ifndef HEADER_PINGUS_PARTICLES_SNOW_PARTICLE_HOLDER_HXX
#define HEADER_PINGUS_PARTICLES_SNOW_PARTICLE_HOLDER_HXX

#include <vector>
#include <ClanLib/Display/Display/surface.h>
#include "../vector.hxx"
#include "../worldobj.hxx"

class GraphicContext;

class SnowParticleHolder : public WorldObj
{
private:
  enum ParticleType { Snow1, Snow2, Snow3, Snow4, Snow5 };

  struct SnowParticle {
    bool         alive;
    bool         colliding;
    ParticleType type;
    Vector       pos;
    Vector       velocity;

    SnowParticle(int x, int y, bool colliding_);
  };

friend struct SnowParticle;

private:
  CL_Surface snow1;
  CL_Surface snow2;
  CL_Surface snow3;
  CL_Surface snow4;
  CL_Surface snow5;
  CL_Surface ground;

  std::vector<SnowParticle> particles;
  
public:
  SnowParticleHolder ();

  void add_particle (int x, int y, bool colliding = false);

  float get_z_pos () const { return 1000.0f; }

  /// Let the particle move
  void update ();

  /// Draw the particle with the correct zoom resize
  void draw (GraphicContext& gc);

private:
  SnowParticleHolder (const SnowParticleHolder&);
  SnowParticleHolder& operator= (const SnowParticleHolder&);
};

#endif

/* EOF */
