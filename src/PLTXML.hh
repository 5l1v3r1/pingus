//  $Id: PLTXML.hh,v 1.3 2000/09/18 12:22:15 grumbel Exp $
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

#ifndef PLTXML_HH
#define PLTXML_HH

#include <libxml/parser.h>
#include <vector>
#include <string>
#include <map>
#include "backgrounds/SurfaceBackgroundData.hh"

class PLTXML
{
private:
  xmlDocPtr doc;
  std::vector<std::string> level_list;
  map<std::string, std::string> world_name;
  map<std::string, std::string> description;
  SurfaceBackgroundData background;

  void parse_file();
  void parse_background(xmlNodePtr cur);
  void parse_description(xmlNodePtr cur);
  void parse_world_name(xmlNodePtr cur);
  void parse_level_list(xmlNodePtr cur);
  
public:
  ///
  PLTXML();
  ///
  ~PLTXML();

  ///
  void parse(std::string filename);

  ///
  map<std::string,std::string> get_name();
  ///
  map<std::string,std::string> get_description();
  ///
  SurfaceBackgroundData get_background();
  ///
  std::string get_surface() { return ""; }
  ///
  std::vector<std::string> get_levels();
};

#endif

/* EOF */
