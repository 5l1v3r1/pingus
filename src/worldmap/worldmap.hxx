//  $Id: worldmap.hxx,v 1.21 2003/02/19 09:50:36 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDMAP_WORLDMAP_HXX
#define HEADER_PINGUS_WORLDMAP_WORLDMAP_HXX

#include <vector>
#include "../libxmlfwd.hxx"
#include "stat.hxx"
#include "../gui/display_graphic_context.hxx"

class GraphicContext;
class CL_Key;
class CL_Font;
class CL_InputDevice;

namespace WorldMapNS {

typedef int EdgeId;
typedef int NodeId;

class PathGraph;
class Drawable;
class Pingus;

/** A class for loading, displaying and managing the worldmap. The
    worldmap is basically a multi-layered image and a path
    (bidirectional graph) where a pingu can walk on. Parts of the
    worldmap are hidable and will only get displayed at specific
    events (successfull level completions, etc.). */
class WorldMap
{
private:
  // FIXME: We should use a ScrollGC or something like that here
  DisplayGraphicContext display_gc;

  /** name of the file to parse */
  std::string filename;

  typedef std::vector<Drawable*>   ObjectLst;
  typedef std::vector<Drawable*> DrawableLst;

  int width;
  int height;

  Pingus* pingus;

  /** The graph that represents the path on the map */
  PathGraph* path_graph;
  
  /** A collection of drawable things, allocation and deallocation
      takes place elsewhere these are only references to other
      objects */
  DrawableLst drawables;

  /** A collection of drawables loaded from the xml file, this list
      gets deleted at the end */
  ObjectLst objects;

  int mouse_x;
  int mouse_y;
public:
  /** Load the given*/
  WorldMap(const std::string& filename);
  ~WorldMap();

  void draw (GraphicContext& gc);
  void update ();
  
  /** The the pingu to the given Node */
  void set_pingus(NodeId id);
  
  /** FIXME: Memory leak?! */
  void add_drawable(Drawable* drawable);
  void remove_drawable(Drawable* drawable);

  /** @return the shortest path between node1 and node2  */
  std::vector<EdgeId> find_path (NodeId node1, NodeId node2);

  /** x,y are in WorldMap CO, not ScreenCO */
  void on_primary_button_press(int x, int y);
  void on_secondary_button_press(int x, int y);
  void on_pointer_move(int x, int y);
private:
#if 0
  /** @return the node at the given position. x and y are in
      world-COs, not screen. */
  NodeId get_node (int x, int y);
#endif

  /** Parses a WorldMap XML file */
  void parse_file(xmlDocPtr doc, xmlNodePtr cur);
  
  /** Parse the object section of the Worldmap XML file, it contains 
      Sprites, Backgrounds and other things */
  void parse_objects(xmlDocPtr doc, xmlNodePtr cur);

  /** Parse the graph section of the WorldMap XML file, it contains
      the path where the Pingu can walk on. */
  void parse_graph(xmlDocPtr doc, xmlNodePtr cur);
  
  /** Parse the propertie section of a WorldMap XML file, it contains
      meta data such as the author or the name of the Worldmap */
  void parse_properties(xmlDocPtr doc, xmlNodePtr cur);
};

} // namespace WorldMapNS

#endif

/* EOF */
