//  Pingus - A free Lemmings clone
//  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <string>
#include "pingus_worldmap.hpp"

class PingusWorldmapImpl
{
public:
  std::string name;
  std::string short_name;
  std::string description;
  std::string music;
  std::string author;
  std::string email;
  int width;
  int height;

  std::string default_node;
  std::string final_node;

};

PingusWorldmap::PingusWorldmap()
{
}

PingusWorldmap::PingusWorldmap(const Pathname& pathname)
{
}


std::string
PingusWorldmap::get_name() const 
{
  return impl->name; 
}

std::string
PingusWorldmap::get_short_name() const
{
  return impl->short_name;
}

std::string
PingusWorldmap::get_description() const
{
  return impl->description;
}

std::string
PingusWorldmap::get_music() const
{
  return impl->music;
}

std::string
PingusWorldmap::get_author() const
{
  return impl->author;
}

std::string
PingusWorldmap::get_email() const
{
  return impl->email;
}

int
PingusWorldmap::get_width() const
{
  return impl->width;
}

int
PingusWorldmap::get_height() const
{
  return impl->height;
}

std::string
PingusWorldmap::get_default_node() const
{
  return impl->default_node;
}

std::string
PingusWorldmap::get_final_node() const
{
  return impl->final_node;
}

/* EOF */
