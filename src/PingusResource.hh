//  $Id: PingusResource.hh,v 1.5 2000/06/18 17:01:50 grumbel Exp $
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

#ifndef PINGUSRESOURCE_HH
#define PINGUSRESOURCE_HH

#include <string>
#include <vector>

#include <ClanLib/core.h>

///
class PingusResource
{
private:
  ///
  struct Res {
    ///
    CL_ResourceManager* res;
    ///
    std::string filename;
  }///
;

  ///
  static std::vector<Res> resource;

  ///
  static void open(std::string);
public:
  ///
  PingusResource();

  ///
  static CL_ResourceManager* get(std::string);
}///
;

#endif

/* EOF */
