//  $Id: start_pos.cxx,v 1.9 2003/10/18 23:17:27 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include "../xml_helper.hxx"
#include "start_pos.hxx"

namespace Pingus {
namespace EditorNS {

StartPos::StartPos (int arg_x_pos, int arg_y_pos)
  : SpriteEditorObj("editor/start_pos", "core")
{
  pos.x = arg_x_pos;
  pos.y = arg_y_pos;
  pos.z = 1000;

  pos_ref = &pos;
}

void
StartPos::write_xml (std::ostream& xml)
{
  xml << "  <start-position>\n";
  XMLhelper::write_vector_xml(xml, pos);
  xml << "  </start-position>\n" << std::endl;
}

EditorObj*
StartPos::duplicate ()
{
  std::cout << "StartPos: The start position can't be duplicated" << std::endl;
  return 0;
}

} // namespace EditorNS
} // namespace Pingus

/* EOF */
