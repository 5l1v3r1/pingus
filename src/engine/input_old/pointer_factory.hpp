//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_ENGINE_INPUT_OLD_POINTER_FACTORY_HPP
#define HEADER_PINGUS_ENGINE_INPUT_OLD_POINTER_FACTORY_HPP

#include "file_reader.hpp"

namespace Input {

class Pointer;

class PointerFactory
{
private:
  static Pointer* axis_pointer(const FileReader& reader);
  static Pointer* mouse_pointer();
  static Pointer* multiple_pointer(const FileReader& reader);

public:
  static Pointer* create(const FileReader& reader);

private:
  PointerFactory();
  PointerFactory(const PointerFactory&);
  PointerFactory& operator= (const PointerFactory&);
};

} // namespace Input

#endif

/* EOF */
