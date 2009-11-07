//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_LEVELSET_HPP
#define HEADER_PINGUS_PINGUS_LEVELSET_HPP

#include "engine/display/sprite.hpp"
#include "pingus/pingus_level.hpp"
#include "util/pathname.hpp"

class Levelset
{
public:
  struct Level 
  {
    std::string resname;
    bool accessible;
    bool finished;
    PingusLevel plf;

    Level() :
      resname(),
      accessible(),
      finished(),
      plf()
    {}
  };

private:
  std::string title;
  std::string description;
  Sprite image;
  int  completion;
  std::vector<Level*> levels;

public:
  Levelset(const Pathname& pathname);
  ~Levelset();

  std::string get_title() const;
  std::string get_description() const;
  Sprite get_image() const;

  Level* get_level(int num) const;
  int get_level_count() const;

  /** Return the number of completed levels */
  int get_completion()  const;

  void refresh();
private:
  Levelset (const Levelset&);
  Levelset& operator= (const Levelset&);
};

#endif

/* EOF */
