// $Id: rect_editorobj.cxx,v 1.10 2003/10/18 23:17:27 grumbel Exp $
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <ClanLib/Core/Math/rect.h>
#include "editor_view.hxx"
#include "rect_editorobj.hxx"

namespace Pingus {
namespace EditorNS {

RectEditorObj::RectEditorObj()
{
}

RectEditorObj::RectEditorObj (const RectEditorObj& old) : EditorObj(old)
{
}

RectEditorObj&
RectEditorObj::operator= (const RectEditorObj& old)
{
  if (this != &old)
    EditorObj::operator=(old);

  return *this;
}

void
RectEditorObj::draw_mark (EditorNS::EditorView * view)
{
  Vector ul(get_upper_left_corner());

  view->draw_rect(static_cast<int>(ul.x),
		  static_cast<int>(ul.y),
		  static_cast<int>(ul.x + get_width()),
		  static_cast<int>(ul.y + get_height()),
		  1.0, 0.0, 1.0, 1.0);
}

bool
RectEditorObj::is_over(const Vector& pos)
{
  Vector ul(get_upper_left_corner());

  return  (   ul.x < pos.x && ul.x + get_width () > pos.x
	   && ul.y < pos.y && ul.y + get_height() > pos.y);
}

bool
RectEditorObj::is_in_rect (const CL_Rect& rect)
{
  Vector pos(get_upper_left_corner());

  // FIXME: Simple, stupid and wrong,... but works good =;-)
  return (   pos.x >= rect.left && pos.x < rect.right
	  && pos.y >= rect.top && pos.y < rect.bottom);
}

} // namespace EditorNS
} // namespace Pingus

/* EOF */
