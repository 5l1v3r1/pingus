//  $Id: graph.hxx,v 1.10 2002/09/11 12:45:58 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDMAP_GRAPH_HXX
#define HEADER_PINGUS_WORLDMAP_GRAPH_HXX

#include "../res_descriptor.hxx"
#include "../boost/smart_ptr.hpp"
#include "node.hxx"

namespace WorldMapNS {

#if 0
/** This class manages the path of the WorldMap where the pingu can
    walk on. */
class Graph
{
public:
  /** Load a graph from file */
  Graph (const std::string& filename);
  ~Graph ();
    
  /** Draw the graph to the given GC 
      @param gc The GraphicContext to draw on */
  void draw (GraphicContext& gc);
    
  /** @return a reference to the nodes of this graph */
  const std::vector<>& get_nodes ();

  /** @return a reference to the edges of this graph */
  const std::vector<>& get_edges ();
};
#endif 

/** The path on the WorldMap is a bidirectional graph, this class
    managed it FIXME: needs a complete rewrite, EmptyNodes need to
    be handled differently */
class Graph
{
private:
  //Graph<Node>* graph;
  ResDescriptor bg_desc;
  std::string music;
  xmlDocPtr doc;
  
public:
  std::list<boost::shared_ptr<Node> >   nodes;
  typedef std::list<boost::shared_ptr<Node> >::iterator iterator;

  Graph ();
  ~Graph ();
 
  /** FIXME: We shouldn't have a background, but instead multiple
      layers of images */
  ResDescriptor              get_background ();

  /** @return The name of the music file which should be used for
      @return this level, filename is relative to "data/music/"
      @return Example: pingus1.it */
  std::string get_music ();

  /** Draw the edges of the graph to the screen
      @param offset FIXME: should be handled by GraphicContext instead */
  void draw (const CL_Vector& offset);

  /** Some functions to parse the data out of an xml file.
      For syntax description see doc/worldmap.xml
      @{ */
  void parse_file (std::string filename);
private:
  void parse_node_list (xmlNodePtr);
  void parse_music (xmlNodePtr);
  void parse_background (xmlNodePtr);
  /** @} */
      
  Graph (const Graph&);
  Graph operator= (const Graph&);
};

} // namespace WorldMapNS

#endif

/* EOF */
