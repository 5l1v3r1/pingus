//  $Id: PinguAction.cc,v 1.24 2002/06/08 23:11:07 torangan Exp $
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

#include <cassert>
#include "ColMap.hh"
#include "PingusError.hh"
#include "World.hh"
#include "PingusResource.hh"
#include "Pingu.hh"

// Initialise class static.
const int PinguAction::pingu_height = 26;

PinguAction::PinguAction()
{
  is_finished = false;
}

PinguAction::~PinguAction()
{
}

void
PinguAction::set_pingu(Pingu* pingu_data)
{
  pingu = pingu_data;
  //assert(pingu);
  init();
}

// Checks if the pingu action needs to catch another pingu (needed for 
// example by the blocker)
bool 
PinguAction::need_catch() 
{ 
  return false; 
}

// Wrapper around the colmap, to get the pixels infront of the pingu,
// from is current position
int
PinguAction::rel_getpixel(int x, int y)
{
  return pingu->get_world()->get_colmap()->getpixel(pingu->get_x() + (x * pingu->direction), (pingu->get_y ()) - y);
}

ActionType
PinguAction::get_type(void)
{
  return (ActionType)ONCE;
}

char
PinguAction::get_persistent_char ()
{
  assert(!"This is not a persitent action!");
  return '-';
}

bool
PinguAction::head_collision_on_walk (int x, int y)
{
  int pixel = rel_getpixel(x, y + pingu_height);

  if (pixel != ColMap::NOTHING && !(pixel & ColMap::BRIDGE))
    return true;

  return false;
}

/* EOF */
