//  $Id: PinguInfo.cc,v 1.13 2002/06/10 11:00:27 torangan Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#include <cstdio>

#include <ClanLib/Display/Display/display.h>
#include <ClanLib/Display/Font/font.h>
#include "algo.hh"
#include "PinguAction.hh"
#include "PingusResource.hh"
#include "PinguInfo.hh"

/* Headers needed for i18n / gettext */
#include <clocale>
#include <config.h>
#include "my_gettext.hh"


PinguInfo::PinguInfo()
  : pingu (0)
{
  font = PingusResource::load_font("Fonts/courier_small","fonts");
}

void
PinguInfo::draw()
{
  int x_pos = 100;
  int y_pos = 5;

  CL_Display::fill_rect(x_pos + CL_Display::get_width()  - 220,
			y_pos + CL_Display::get_height() - 55,
			x_pos + CL_Display::get_width()  - 5,
			y_pos + CL_Display::get_height() - 5,
			0.2f, 0.2f, 0.2f, 1.0f);
  if (pingu) {
    char str1[256];
    char str2[256];

    sprintf(str1, _("pingu_id %d"), pingu->get_id());
    font->print_left(x_pos + CL_Display::get_width() - 185, 
		     y_pos + CL_Display::get_height() - 50,
		     tolowerstr(str1));

    if (pingu->get_action()) {
      sprintf(str2, _("action %s"), pingu->get_action()->get_name().c_str());
    } else {
      sprintf(str2, _("action none"));
    }

    font->print_left(x_pos + CL_Display::get_width() - 185, 
		     y_pos + CL_Display::get_height() - 30,
		     tolowerstr(str2));
  } else {
    font->print_left(x_pos + CL_Display::get_width() - 200, 
		     y_pos + CL_Display::get_height() - 50,
		     "none selected");
  }
}

void
PinguInfo::set_pingu(Pingu* p)
{
  pingu = p;
}

/* EOF */
