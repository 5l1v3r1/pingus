//  $Id: PinguEnums.hh,v 1.8 2001/08/05 21:20:53 grumbel Exp $
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

#ifndef PINGUENUMS_HH
#define PINGUENUMS_HH

/** Haven't yet experimented much with pingu status, but maybe it is a
    good idea. Maybe that should be changed to a bitmask. */
enum PinguStatus { PS_ALIVE, PS_EXITED, PS_DEAD };

/// The environment in which a PinguAction get be activated.
enum PinguEnvironment {
  ENV_LAND   = 1<<0,
  ENV_WATER  = 1<<1,
  ENV_FIRE   = 1<<2,
  ENV_AIR    = 1<<3,
  ENV_ALWAYS = ~0
};

///
enum PingusGameMode { 
  INTERACTIVE_MODE,
  DEMO_MODE 
};

#endif

/* EOF */
