//  $Id: guillotine.cxx,v 1.1 2002/09/04 14:55:13 torangan Exp $
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

#include "guillotine.hxx"
#include "../pingus_resource.hxx"
#include "../pingu_holder.hxx"
#include "../world.hxx"
#include "../pingu.hxx"
#include "../worldobj.hxx"
#include "../worldobjsdata/guillotine_data.hxx"

namespace WorldObjs {

  Guillotine::Guillotine (WorldObjsData::GuillotineData* data_) 
                        : killing(false),
			  data (new WorldObjsData::GuillotineData(*data_))
  {
    data->counter.set_size(data->surface.get_num_frames()/2);
    data->counter.set_type(GameCounter::once);
    data->counter.set_speed(0.7);
    data->counter = 0;

    data->idle_counter.set_size(data->idle_surf.get_num_frames());
    data->idle_counter.set_type(GameCounter::loop);
    data->idle_counter.set_speed(0.3);
    data->idle_counter = 0;
  }

  Guillotine::~Guillotine ()
  {
    delete data;
  }

  void
  Guillotine::draw_offset (int x, int y, float s)
  {
    if (killing) {
      if (data->direction.is_left())
        data->surface.put_screen(static_cast<int>(data->pos.x + x), static_cast<int>(data->pos.y + y), data->counter);
      else
        data->surface.put_screen(static_cast<int>(data->pos.x + x), static_cast<int>(data->pos.y + y), data->counter + 12);
    } else {
      data->idle_surf.put_screen(static_cast<int>(data->pos.x + x), static_cast<int>(data->pos.y + y), data->idle_counter);
    }
    
    UNUSED_ARG(s);
  }
  
  
  float
  Guillotine::get_z_pos () const
  {
    return data->pos.z;
  }

  void
  Guillotine::update (float delta)
  {
    if (data->counter.finished()) {
      data->counter = 0;
      killing = false;
    }

    PinguHolder* holder = world->get_pingu_p ();
    for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu)
      catch_pingu(*pingu);

    if (killing) {
      ++data->counter;
    } else {
      ++data->idle_counter;
    }
    
    UNUSED_ARG(delta);
  }

  void
  Guillotine::catch_pingu (Pingu* pingu)
  {
    if (!killing) 
      {
        if (pingu->is_inside (static_cast<int>(data->pos.x + 38), static_cast<int>(data->pos.y + 90),
			      static_cast<int>(data->pos.x + 42), static_cast<int>(data->pos.y + 98)))
	  {
	    killing = true;
	    pingu->set_status(PS_DEAD);
	    data->direction = pingu->direction;
	  }
      }
  }

}

/* EOF */
