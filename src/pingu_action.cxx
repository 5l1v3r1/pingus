//  $Id: pingu_action.cxx,v 1.8 2002/09/16 20:31:09 grumbel Exp $
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

#include <assert.h>
#include "col_map.hxx"
#include "world.hxx"
#include "pingu.hxx"
#include "pingu_action.hxx"
#include "worldobj.hxx"

// Initialise class static.
const int PinguAction::pingu_height = 26;

PinguAction::PinguAction () : pingu (0)
{
}

PinguAction::~PinguAction ()
{
}

void
PinguAction::set_pingu (Pingu* pingu_data)
{
  pingu = pingu_data;
  assert(pingu);
  init();
}

// Checks if the pingu action needs to catch another pingu (needed for 
// example by the blocker)
bool 
PinguAction::need_catch () 
{ 
  return false; 
}

// Wrapper around the colmap, to get the pixels infront of the pingu,
// from is current position
int
PinguAction::rel_getpixel (int x, int y)
{
  return WorldObj::get_world()->get_colmap()->getpixel(static_cast<int>(pingu->get_x() + (x * pingu->direction)),
                                                       static_cast<int>(pingu->get_y() - y));
}

ActionType
PinguAction::get_activation_mode () const
{
  return INSTANT;
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

  if (pixel != Groundtype::GP_NOTHING && !(pixel & Groundtype::GP_BRIDGE))
    return true;

  return false;
}

/* EOF */
