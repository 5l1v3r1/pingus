//  $Id: exit_menu.cxx,v 1.3 2002/07/30 01:58:16 grumbel Exp $
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

#include <ClanLib/Display/Display/display.h>
#include <ClanLib/Display/Input/input.h>
#include "pingus_menu_manager.hxx"
#include "pingus_resource.hxx"

ExitMenu::ExitMenu (PingusMenuManager* manager)
  : PingusSubMenu (manager)
{
}

ExitMenu::~ExitMenu ()
{
}

void 
ExitMenu::draw ()
{
  CL_Display::fill_rect (0, 0, CL_Display::get_width (), CL_Display::get_height (),
			 0, 0, 0, 0.5);
  sur.put_screen (CL_Display::get_width ()/2 - sur.get_width ()/2, 
		  CL_Display::get_height ()/2 - sur.get_height ()/2);
}

void 
ExitMenu::update (float /*delta*/)
{
}

void 
ExitMenu::preload ()
{
  sur = PingusResource::load_surface ("misc/exitmenu", "core");
}

/* EOF */
