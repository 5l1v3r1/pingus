//  $Id: fake_exit.cxx,v 1.6 2002/09/27 18:36:41 torangan Exp $
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

#include "../graphic_context.hxx"
#include "../pingu.hxx"
#include "../pingu_holder.hxx"
#include "../pingu_action.hxx"
#include "../world.hxx"
#include "../worldobjsdata/fake_exit_data.hxx"
#include "fake_exit.hxx"

namespace WorldObjs {

FakeExit::FakeExit (const WorldObjsData::FakeExitData& data_) 
  : data (new WorldObjsData::FakeExitData(data_)),
    smashing(false)
{
  data->counter.set_size(data->surface.get_num_frames());
  data->counter.set_type(GameCounter::once);
  data->counter.set_speed(2.5);
  data->counter = data->surface.get_num_frames() - 1;

  data->pos -= CL_Vector(data->surface.get_width ()/2, data->surface.get_height ());
}

FakeExit::~FakeExit()
{
  delete data;
}

float
FakeExit::get_z_pos () const
{
  return data->pos.z;
}

void 
FakeExit::draw (GraphicContext& gc)
{
  gc.draw (data->surface, data->pos, data->counter.value());
}


void
FakeExit::update (float delta)
{
  PinguHolder* holder = world->get_pingu_p ();
  for (PinguIter pingu = holder->begin (); pingu != holder->end (); ++pingu){
    catch_pingu(*pingu);
  }

  if (smashing)
    ++data->counter;
      
  UNUSED_ARG(delta);
}

void
FakeExit::catch_pingu (Pingu* pingu)
{
  if (data->counter.finished()) {
    smashing = false;
  }

  if (   pingu->get_x() > data->pos.x + 31 && pingu->get_x() < data->pos.x + 31 + 15
      && pingu->get_y() > data->pos.y + 56 && pingu->get_y() < data->pos.y + 56 + 56) 
    {
      if (pingu->get_action()->get_type() != Actions::Splashed)
	{
	  if (!smashing) {
	    data->counter = 0;
	    smashing = true; 
	  }

	  if (data->counter >= 3 && data->counter <= 5) {
	    pingu->set_action(Actions::Splashed);
	  }
	}
    }
}

} // namespace WorldObjs

/* EOF */
