//  $Id: menu_background.cxx,v 1.7 2003/03/28 12:06:32 grumbel Exp $
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

#include "gui/graphic_context.hxx"
#include "menu_background.hxx"
#include "pingus_resource.hxx"

MenuBackground::MenuBackground ()
{
  layer_manager.add_layer (PingusResource::load_surface ("menu/layer1", "core"),  0, 0, 12, 0);
  layer_manager.add_layer (PingusResource::load_surface ("menu/layer2", "core"),  0, 150, 25, 0);
  layer_manager.add_layer (PingusResource::load_surface ("menu/layer3", "core"), 0, 200, 50, 0);
  layer_manager.add_layer (PingusResource::load_surface ("menu/layer4", "core"), 0, 600 - 171, 100, 0);
  layer_manager.add_layer (PingusResource::load_surface ("menu/layer5", "core"), 0, 500, 200, 0);
}

MenuBackground::~MenuBackground ()
{
}

void 
MenuBackground::draw (GraphicContext& gc)
{
  layer_manager.draw (gc);
}

void 
MenuBackground::update (float delta)
{
#ifndef WIN32
  // FIXME: WIN32 shouldn't be an issue here
  layer_manager.update (delta);
#endif
}

/* EOF */
