//  $Id: Splashed.cc,v 1.1 2000/03/22 14:32:42 grumbel Exp $
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

#include "Splashed.hh"

Splashed::Splashed(void)
{
}

PinguAction*
Splashed::allocate(void)
{
  return new Splashed();
}

void
Splashed::init(void)
{
  environment = (PinguEnvironment)(land | sky);
  action_name = "splashed";

  surface = CL_Surface::load("Pingus/splash", local_res());
  counter.set_size(surface->get_num_frames());
  counter.set_type(Counter::once);
  counter.set_count(0);
  counter.set_speed(10);
  pingu->set_status(not_catchable);

  is_multi_direct = false;
  sound_played = false;
  particle_thrown = false;
}

void
Splashed::let_move(void)
{
  if (pingu->get_status() == dead)
    return;

  if (!particle_thrown)
    {
      //pingu->particle->add_pingu_explo(pingu->x_pos, pingu->y_pos - 2);
      particle_thrown = true;
    }

  if (counter == 11)
    {
      pingu->set_status(dead);
    }
}

/* EOF */
