//  $Id: ResDescriptor.cc,v 1.6 2000/04/25 17:54:39 grumbel Exp $
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

#include "ResDescriptor.hh"
#include "PingusError.hh"

ResDescriptor::ResDescriptor()
{
  type = RESOURCE;
  res_name = "";
  filename = "global.dat";
}

ResDescriptor::ResDescriptor(std::string str) 
{
  std::string::size_type pos1;
  std::string::size_type pos2;

  //cout << "Resdes: " << str << std::endl;

  type = RESOURCE;
  
  pos1 = str.find_first_of(':');
  pos2 = str.find_first_of(')');
  
  if (pos1 != std::string::npos && pos2 != std::string::npos)
    {
      filename = str.substr(pos1 + 1, (pos2 - pos1 - 1));
      res_name = str.substr(pos2 + 1);
    }
  else
    {
      res_name = str;
      filename = "global.dat";
    }
}

ResDescriptor::ResDescriptor(std::string c_cast, std::string value) 
{
  std::string cast;

  if (c_cast.find_first_of(":") == std::string::npos) {
    cast = c_cast;
    filename = "global.dat";
  } else {
    cast     = c_cast.substr(0, c_cast.find_first_of(":"));
    filename = c_cast.substr(c_cast.find_first_of(":") + 1);
  }
  
  if (cast == "file") {
    type = FILE;
  } else if (cast == "resource") {
    type = RESOURCE;
  } else if (cast == "auto") {
    type = AUTO;
  } else {
    throw PingusError("ResDescriptor: Wrong cast '"+cast+"' for value '"+value+"'\n");
  }
  res_name = value;
}

/* EOF */
