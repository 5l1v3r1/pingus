//  $Id: PLF.cc,v 1.31 2002/06/08 23:11:07 torangan Exp $
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

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "PLF.hh"
#include "algo.hh"
#include "globals.hh"
#include "PingusError.hh"
#include "System.hh"

using namespace std;
using namespace boost;

PLF::PLF()
{
  start_x_pos = start_y_pos = 0;
  width = 1600; height = 800;
  number_of_pingus = 100;
  max_time = 9000;
  number_to_save = 0;
  number_of_pingus = 100;
  difficulty = 5;  
  playable = false;
  music = ResDescriptor("file", "pingus-4.it");
  //maptype = SPOT;
  foreground.type = ResDescriptor::RD_FILE;
}

// Destroy all data
PLF::~PLF()
{
}
/*
vector<shared_ptr<BackgroundData> >
PLF::get_backgrounds()
{
  return backgrounds;
}*/

ResDescriptor
PLF::get_foreground()
{
  if (!psm_filename.empty()) {
    return ResDescriptor("file", psm_filename);
  } else {
    ResDescriptor ret_val = foreground;
    
    switch(foreground.type) {
    case  ResDescriptor::RD_FILE:
      ret_val.res_name = "levels/" + foreground.res_name;
      break;
    case  ResDescriptor::RD_RESOURCE:
      if (verbose > 1) std::cout << "Not supported" << endl;
      break;
    default:
      assert(false);
      break;
    }
    return ret_val;
  }
}
/*
MapType
PLF::map_type()
{
  return maptype;
}
*/
ResDescriptor
PLF::get_mapfile()
{
  switch(col.type) {
  case  ResDescriptor::RD_FILE:
    col.res_name = "levels/" + col.res_name;
    break;
  case  ResDescriptor::RD_RESOURCE:
    break;
  default:
    break;
  }
  return col;
}

int
PLF::get_startx()
{
  return start_x_pos;
}

int
PLF::get_starty()
{
  return start_y_pos;
}

int
PLF::get_width(void)
{
  return width;
}

int
PLF::get_height(void)
{
  return height;
}

int
PLF::get_pingus()
{
  return number_of_pingus;
}

vector<ActionData>
PLF::get_actions()
{
  // FIXME: we should merge duplicated actions
  return actions;
}

ResDescriptor
PLF::get_music()
{
  return music;
}

map<std::string, std::string>
PLF::get_description()
{
  return description;
}

std::string
PLF::get_filename()
{
  return filename;
}

map<std::string, std::string>
PLF::get_levelname()
{
  return levelname;
}

int
PLF::get_time(void)
{
  return max_time;
}

int
PLF::get_number_to_save()
{
  return number_to_save;
}

int  
PLF::get_difficulty()
{
  return difficulty;
}

bool  
PLF::get_playable()
{
  return playable;
}

std::string
PLF::get_comment ()
{
  return comment;
}

string
PLF::get_author()
{
  return author;
}

void
PLF::set_psm_filename(string name)
{
  psm_filename = name;
}

std::vector<GroundpieceData> 
PLF::get_groundpieces(void)
{
  return groundpieces;
}

std::vector<WeatherData>   
PLF::get_weather(void)
{
  return weathers;
}

///
std::vector<shared_ptr<WorldObjData> > 
PLF::get_worldobjs_data ()
{
  //std::cout << "World: " << worldobjs_data.size () << std::endl;
  return worldobjs_data;
}

/* EOF */
