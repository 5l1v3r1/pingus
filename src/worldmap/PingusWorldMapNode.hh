//  $Id: PingusWorldMapNode.hh,v 1.1 2002/06/04 21:23:42 grumbel Exp $
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

#ifndef PINGUSWORLDMAPNODE_HH
#define PINGUSWORLDMAPNODE_HH

#include "../Sprite.hh"
#include "../boost/smart_ptr.hpp"
#include "../PingusSound.hh"
#include "../globals.hh"
#include "../PLF.hh"
#include "PingusWorldMapNodeData.hh"

//#include "../generic/Graph.hh"


/** An object on the worldmap */
class PingusWorldMapNode 
{
public:
  /** should links or nodes be accessible? */
  bool accessible;
  
  PingusWorldMapNode () {}
  virtual ~PingusWorldMapNode () {}

  virtual void on_click () =0;
  virtual void mark (bool /*value*/) {}
  virtual void draw (CL_Vector /*offset*/) {}
  virtual std::string get_string () =0;

  virtual int  get_id () =0;
  virtual CL_Vector get_pos () =0;
  virtual std::list<int>& get_links () =0;
};

/** A wrap object which brings you to the next worldmap */
class PingusWorldMapTubeNode
  : public PingusWorldMapNode,
    public PingusWorldMapTubeNodeData
{
public:
  std::string worldmap_name;
  Sprite tube;
  int link_node;
public:  
  PingusWorldMapTubeNode (const PingusWorldMapTubeNodeData&);
  void on_click ();
  void draw (CL_Vector offset);
  std::string get_string ();

  /** FIXME: this looks unnecesarry, could probally replaced by
      FIXME: templates or something like that */
  int  get_id () { return PingusWorldMapNodeData::get_id (); }
  CL_Vector get_pos () { return PingusWorldMapNodeData::get_pos (); }
  std::list<int>& get_links () { return PingusWorldMapNodeData::get_links (); }
};

/** The entrance to a level */
class PingusWorldMapLevelNode
  :  public PingusWorldMapNode,
     public PingusWorldMapLevelNodeData
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
  bool finished;
  boost::shared_ptr<PLF> get_plf ();

  PingusWorldMapLevelNode (const PingusWorldMapLevelNodeData&);
  void on_click ();
  void mark (bool value);
  void draw (CL_Vector offset);
  std::string get_string ();


  /** FIXME: this looks unnecesarry, could probally replaced by
      FIXME: templates or something like that */
  int  get_id () { return PingusWorldMapNodeData::get_id (); }
  CL_Vector get_pos () { return PingusWorldMapNodeData::get_pos (); }
  std::list<int>& get_links () { return PingusWorldMapNodeData::get_links (); }
};

#endif

/* EOF */
