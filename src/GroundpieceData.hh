//  $Id: GroundpieceData.hh,v 1.6 2001/05/18 19:17:08 grumbel Exp $
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

#ifndef GROUNDPIECEDATA_HH
#define GROUNDPIECEDATA_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "ResDescriptor.hh"

///
class GroundpieceData 
{
public:
  ///
  CL_Surface surface;
  ///
  CL_Resource* resource;
  ///
  ResDescriptor desc;
  ///
  CL_Vector pos;
  ///
  enum Type { SOLID, TRANSPARENT, GROUND, BRIDGE, WATER, LAVA, REMOVE, NOTHING } type; 

  static Type string_to_type(const std::string& arg_type) 
  {
    if (arg_type == "solid")
      return GroundpieceData::SOLID;
    else if (arg_type == "transparent")    
      return GroundpieceData::TRANSPARENT;
    else if (arg_type == "ground")
      return GroundpieceData::GROUND;
    else if (arg_type == "bridge")
      return GroundpieceData::BRIDGE;
    else if (arg_type == "water")
      return GroundpieceData::WATER;
    else if (arg_type == "lava") 
      return GroundpieceData::LAVA;
    else if (arg_type == "remove") 
      return GroundpieceData::REMOVE;
    else
      {
	std::cout << "GroundpieceData: Unhandled type: " << arg_type << std::endl;
	return GroundpieceData::GROUND;
      }
  }

  static std::string type_to_string(Type arg_type) 
  {
    switch (arg_type)
      { 
      case GroundpieceData::SOLID:
	return "solid";
      case GroundpieceData::TRANSPARENT:
	return "transparent";
      case GroundpieceData::GROUND:
	return "ground";
      case GroundpieceData::BRIDGE:
	return "bridge";
      case GroundpieceData::WATER:
	return "water";
      case GroundpieceData::LAVA:
	return "lava";
      case GroundpieceData::REMOVE:
	return "remove";
      default:
	std::cout << "GroundpieceData: Unhandled type: " << arg_type << std::endl;
	return "ground";
      }
  }
};

/* EOF */

#endif

/* EOF */
