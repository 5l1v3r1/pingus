//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Jason Green <jave27@gmail.com>,
//                     Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_EDITOR_LEVEL_IMPL_HPP
#define HEADER_PINGUS_EDITOR_LEVEL_IMPL_HPP

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "editor/editor_screen.hpp"
#include "editor/level_obj.hpp"
#include "editor/editor_level.hpp"

namespace Editor {

class LevelImpl
{
public:
  // Set defaults in constructor
  LevelImpl() :
    resname(),
    levelname(),
    description(),
    ambient_light(255, 255, 255),
    size(),
    number_of_pingus(),
    number_to_save(),
    actions(),
    time(),
    author(),
    music(),
    objects()
  {
    // Do nothing
  }

  /** Destructor */
  ~LevelImpl()
  {
  }
                   
  std::string resname;

  std::string levelname;
  std::string description;

  Color    ambient_light;
  Size     size;

  int number_of_pingus;
  int number_to_save;

  std::map<std::string, int> actions;

  int time;
  
  std::string author;
  std::string music;

  EditorLevel::Objects objects;

private:
  LevelImpl (const LevelImpl&);
  LevelImpl& operator= (const LevelImpl&);
};

} // namespace Editor

#endif

/* EOF */

