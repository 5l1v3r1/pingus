//  $Id: PingusWorldMap.hh,v 1.5 2000/09/25 16:29:43 grumbel Exp $
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
#include "../generic/Graph.hh"
#include "../Position.hh"
#include "PingusWorldMapGraph.hh"
#include "PingusWorldMapPingus.hh"

class PingusWorldMap
{
private:
  CL_Surface* background;
  CL_Surface* green_dot;
  CL_Surface* red_dot;
  CL_Surface* dot_border;

  Graph<PingusWorldMapNode>* graph;
  PingusWorldMapGraph graph_data;

  PingusWorldMapPingus* pingus;
  
public:
  /** Load a worldmap from a given worldmap description file */
  PingusWorldMap (std::string filename);
  /** Destruct the worldmap */
  virtual ~PingusWorldMap ();

  /** React on button press:
      - calculate which level was clicked
      - calculate the shortest path
      - let the pingu walk */
  void on_button_press (CL_InputDevice *device, const CL_Key &key);
 
  /** React on button release */
  void on_button_release (CL_InputDevice *device, const CL_Key &key);

  /** Draw the world worldmap */
  virtual void draw ();
  
  /** Let the woldmap do some stuff, like animating smoke, playing
      sounds or reacting on special events */
  virtual void let_move ();

  /** Returns a pointer to the node under the given coordinates */
  PingusWorldMapNode* get_node (int x, int y);
};

#endif

/* EOF */
