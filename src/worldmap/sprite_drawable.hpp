
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_SPRITE_DRAWABLE_HPP
#define HEADER_SPRITE_DRAWABLE_HPP

#include "../sprite.hpp"
#include "../math/vector3f.hpp"
#include "drawable.hpp"

namespace WorldMapNS {

/** */
class SpriteDrawable : public Drawable
{
private:
  Sprite sprite;
  Vector3f  pos;

public:
  SpriteDrawable(FileReader reader);
  ~SpriteDrawable();

  void draw(DrawingContext& gc);

  void update(float delta)
  {
    sprite.update(delta);
  }

private:
  SpriteDrawable (const SpriteDrawable&);
  SpriteDrawable operator= (const SpriteDrawable&);
};

} // namespace WorldMapNS

#endif

/* EOF */
