//  $Id: level_dot.cxx,v 1.2 2002/10/13 13:34:40 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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
#include "../pingus_resource.hxx"
#include "../graphic_context.hxx"
#include "level_dot.hxx"

namespace WorldMapNS {

LevelDot::LevelDot(xmlDocPtr doc, xmlNodePtr cur)
  : Dot(doc, XMLhelper::skip_blank(cur->children)),
    green_dot_sur(PingusResource::load_surface("misc/dot_green", "core")),
    red_dot_sur(PingusResource::load_surface("misc/dot_red", "core"))
{
}

void
LevelDot::draw(GraphicContext& gc)
{
  std::cout << "Drawing level dat: " << pos << std::endl;
  gc.draw (green_dot_sur, pos);
}

void
LevelDot::update()
{
}

} // namespace WorldMapNS

/* EOF */
