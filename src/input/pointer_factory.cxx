//  $Id: pointer_factory.cxx,v 1.11 2003/10/20 19:28:55 grumbel Exp $
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

#include "../xml_helper.hxx"
#include "../pingus_error.hxx"
#include "axis_factory.hxx"
#include "pointers/axis_pointer.hxx"
#include "pointers/mouse_pointer.hxx"
#include "pointers/multiple_pointer.hxx"
#include "pointer_factory.hxx"

namespace Pingus {
namespace Input {

using namespace Pointers;

Pointer* PointerFactory::create (xmlNodePtr cur)
{
  if (!cur)
    PingusError::raise("PointerFactory called without an element");

  if (XMLhelper::equal_str(cur->name, "axis-pointer"))
    return axis_pointer(cur);

  else if (XMLhelper::equal_str(cur->name, "mouse-pointer"))
    return mouse_pointer();

  else if (XMLhelper::equal_str(cur->name, "multiple-pointer"))
    return multiple_pointer(cur->children);

  else
    PingusError::raise(std::string("Unknown pointer type: ") + ((cur->name) ? reinterpret_cast<const char*>(cur->name) : ""));

  return 0; // never reached
}

Pointer* PointerFactory::axis_pointer (xmlNodePtr cur)
{
  float speed;
  if (!XMLhelper::get_prop(cur, "speed", speed))
    PingusError::raise("AxisPointer without speed parameter");

  std::vector<Axis*> axes;
  cur = cur->children;

  while (cur)
    {
      if (xmlIsBlankNode(cur))
	{
  	  cur = cur->next;
	  continue;
	}

      axes.push_back(AxisFactory::create(cur));
      cur = cur->next;
    }

  return new AxisPointer(speed, axes);
}

Pointer* PointerFactory::mouse_pointer ()
{
  return new MousePointer;
}

Pointer* PointerFactory::multiple_pointer (xmlNodePtr cur)
{
  std::vector<Pointer*> pointers;

  while (cur)
    {
      if (xmlIsBlankNode(cur))
	{
  	  cur = cur->next;
	  continue;
	}

      pointers.push_back(create(cur));
      cur = cur->next;
    }

  return new MultiplePointer(pointers);
}

} // namespace Input
} // namespace Pingus

/* EOF */
