//  $Id: PingusWorldMap.hh,v 1.2 2000/09/20 07:20:22 grumbel Exp $
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef PINGUSWORLDMAP_HH
#define PINGUSWORLDMAP_HH

#include <string>
#include <ClanLib/core.h>

class PingusWorldMap
{
private:
  CL_Surface* background;
  
public:
  /** Load a worldmap from a given worldmap description file */
  PingusWorldMap (std::string filename);
  /** Destruct the worldmap */
  virtual ~PingusWorldMap ();

  /** React on button press:
      - calculate which level was clicked
      - calculate the shortest path
      - let the pingu walk */
  void on_button_press ();

  /** React on button release */
  void on_button_release ();

  /** Draw the world worldmap */
  virtual void draw ();
  
  /** Let the woldmap do some stuff, like animating smoke, playing
      sounds or reacting on special events */
  virtual void let_move ();
};

#endif

/* EOF */
