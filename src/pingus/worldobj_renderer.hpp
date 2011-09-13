//  Pingus - A free Lemmings clone
//  Copyright (C) 1998-2011 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_PINGUS_WORLDOBJ_RENDERER_HPP
#define HEADER_PINGUS_PINGUS_WORLDOBJ_RENDERER_HPP

#include <vector>

#include "engine/display/surface.hpp"
#include "pingus/resource.hpp"
#include "util/file_reader.hpp"

class WorldObjRenderer
{
private:
  Surface m_surface;
 
public:
  WorldObjRenderer(Surface& output);

  void process(const std::vector<FileReader>& readers);
  void process(const FileReader& reader);

  void render_sprite(const ResDescriptor& desc,
                     const Vector3f& pos);
  void render_surface(const ResDescriptor& desc,
                      const Vector3f& pos,
                      int repeat = 1);

private:
  void process_object_with_surface(const FileReader& reader);
};

#endif

/* EOF */
