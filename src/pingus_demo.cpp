//  $Id$
// 
//  Pingus - A free Lemmings clone
//  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmx.de>
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

#include <stdexcept>
#include <fstream>
#include "pathname.hpp"
#include "file_reader.hpp"
#include "server_event.hpp"
#include "pingus_error.hpp"
#include "pingu_enums.hpp"
#include "pingus_demo.hpp"

PingusDemo::PingusDemo(const Pathname& pathname)
{
  std::vector<FileReader> lines = FileReader::parse_many(pathname);

  if (!lines.empty())
    {
      PingusError::raise("'" + pathname.str() + "', demo file is empty");
    }
  else
    {
      if (lines.front().get_name() == "level")
        {
          if (!lines.front().read_string("name", levelname))
            {
              PingusError::raise("(level (name ...)) entry missing in demo file '" + pathname.str() + "'");
            }
        }
            
      for(std::vector<FileReader>::iterator i = lines.begin()+1; i != lines.end(); ++i)
        {
          events.push_back(ServerEvent(*i));
        }
    }
}

/* EOF */
