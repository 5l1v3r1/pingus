//  $Id: PingusWorldMapGraph.hh,v 1.18 2002/06/04 08:35:31 grumbel Exp $
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

#ifndef PINGUSWORLDMAPGRAPH_HH
#define PINGUSWORLDMAPGRAPH_HH

#include <string>

#include "../PLF.hh"
#include "../Sprite.hh"
#include "../ResDescriptor.hh"
#include "../Position.hh"
#include "../XMLhelper.hh"

//#include "../generic/Graph.hh"

/* Wannabe syntax of worldmaps:
   ----------------------------

    <level id="1" accessible="1">
      <node>
	<position>
	  <x-pos>50</x-pos>
	  <y-pos>377</y-pos>
	</position>
	<link id="2"/>
      </node>
      
      <level name="level1.xml"/>
    </level>

    <tube id="...">
       <node>
         ...
 */

/** An object on the worldmap */
class PingusWorldMapNode
{
public:
  int id;
  bool accessible;
  CL_Vector pos;
  std::list<int> links;
  
  PingusWorldMapNode () {}
  virtual ~PingusWorldMapNode () {}

  virtual void on_click () =0;
  virtual void mark (bool /*value*/) {}
  virtual void draw (CL_Vector /*offset*/) {}
  virtual std::string get_string () =0;
};

/** A wrap object which brings you to the next worldmap */
class PingusWorldMapTubeNode
  : public PingusWorldMapNode
{
public:
  std::string worldmap_name;
  Sprite tube;
  int link_node;
public:  
  PingusWorldMapTubeNode ();
  void on_click ();
  void draw (CL_Vector offset);
  std::string get_string ();
};

/** The entrance to a level */
class PingusWorldMapLevelNode
  : public PingusWorldMapNode
{
private:
  Sprite green_dot;
  Sprite red_dot;
  Sprite invalid_dot;
  Sprite dot_border;
  Sprite green_flag;

  boost::shared_ptr<PLF> plf;
  
  /** true if the level is invalid, which means that the levelfile
      could not be loaded or had errors. false is the default */
  bool invalid;

public:
  std::string levelname;
  bool finished;
  boost::shared_ptr<PLF> get_plf ();

  PingusWorldMapLevelNode ();
  void on_click ();
  void mark (bool value);
  void draw (CL_Vector offset);
  std::string get_string ();
};

class PingusWorldMapGraph
{
private:
  //Graph<PingusWorldMapNode>* graph;
  ResDescriptor bg_desc;
  std::string music;
  xmlDocPtr doc;
  
public:
  std::list<boost::shared_ptr<PingusWorldMapNode> >   nodes;
  typedef std::list<boost::shared_ptr<PingusWorldMapNode> >::iterator iterator;

  PingusWorldMapGraph ();
  ~PingusWorldMapGraph ();
 
  ResDescriptor              get_background ();
  //Graph<PingusWorldMapNode>* get_graph ();
  std::string get_music ();
  
  void draw (const CL_Vector&);

  /// Some functions to parse the data out of an xml file
  //@{ 
  void parse_file (std::string filename);
private:
  void parse_node_list (xmlNodePtr);
  void parse_level (xmlNodePtr);
  void parse_tube (xmlNodePtr);
  void parse_empty (xmlNodePtr);
  void parse_music (xmlNodePtr);
  void parse_background (xmlNodePtr);
  //@}
};

#endif

/* EOF */
