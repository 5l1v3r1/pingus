//  $Id: stat.hxx,v 1.1 2002/06/12 19:03:33 grumbel Exp $
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

#ifndef PINGUSWORLDMAPSTAT_HH
#define PINGUSWORLDMAPSTAT_HH

#include <map>
#include "graph.hxx"

class _xmlDoc;  typedef _xmlDoc*  xmlDocPtr;
class _xmlNode; typedef _xmlNode* xmlNodePtr;


/** This class holds the information on a level's completeness, etc.
    It's only here for internal use by PingusWorldMapStat. */
class PingusWorldMapNodeStat
{
public:
  PingusWorldMapNodeStat ();

  int id;
  std::string levelfile;
  std::string checksum;
  bool finished;
  bool accessible;
  int  percentage;
};

/** Loads a status file and gives you access to the information, which
    levels where finished and how far they are finished. */
class PingusWorldMapStat
{
private:
  bool is_empty;
  std::map<int, PingusWorldMapNodeStat> stats;
  std::string filename;
  xmlDocPtr doc;

  /** Load the given file */
  void parse_file (std::string filename);
  
  /** Parse a given node */
  void parse_node (xmlNodePtr);

public:
  PingusWorldMapStat (std::string worldmap_name);
  ~PingusWorldMapStat ();  

  /** Save the given nodes status to the file from which they are
      loaded */
  void save (std::list<boost::shared_ptr<Pingus::WorldMap::Node> >& nodes);

  /// @return true if the node is finished
  bool finished (int id);
  
  /// @return true if the node with the given id is accessible, false otherwise
  bool accessible (int id);

  ///
  bool empty () { return is_empty; } 
};

#endif

/* EOF */
