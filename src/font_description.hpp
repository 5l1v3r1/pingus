//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_FONT_DESCRIPTION_HPP
#define HEADER_FONT_DESCRIPTION_HPP

#include <string>
#include "math/vector2i.hpp"
#include "math/rect.hpp"
#include "pathname.hpp"

class FileReader;

class GlyphDescription
{
public:
  uint32_t unicode; 
  Vector2i offset;
  int      advance; 
  Rect     rect;

  GlyphDescription();
  GlyphDescription(FileReader& reader);
};

/** */
class FontDescription
{
public:
  Pathname    pathname;

  /** Space between two characters */
  float char_spacing;
  
  /** Spacing between lines, given in multiples of \a size */
  float vertical_spacing;

  /** Vertical height of the font */
  int size;

  /** Image file from which the basic surface is loaded */
  Pathname image;

  /** Characters in the font image */
  std::vector<GlyphDescription> glyphs;

  FontDescription(const Pathname& filename);
};

#endif

/* EOF */
