//  $Id: fonts.cxx,v 1.8 2003/12/13 23:41:11 grumbel Exp $
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

#include "resource.hpp"
#include "fonts.hpp"

namespace Fonts {

////std::string encoding("ISO-8859-1");
std::string encoding("iso-8859-1");

Font chalk_large;
Font chalk_normal;
Font chalk_small;

Font pingus_small;
Font pingus_small_fix_num;
Font pingus_large;

Font smallfont;
Font smallfont_h;

Font courier_small;
Font xterm;
Font lcd;

void
init ()
{
  chalk_large  = Resource::load_font("fonts/chalk_large" + std::string("-") + encoding); 
  chalk_normal = Resource::load_font("fonts/chalk_normal" + std::string("-") + encoding);
  chalk_small  = Resource::load_font("fonts/chalk_small" + std::string("-") + encoding);

  pingus_small = Resource::load_font("fonts/pingus_small" + std::string("-") + encoding);
  pingus_small_fix_num = Resource::load_font("fonts/pingus_small_fix_num" + std::string("-") + encoding);
  pingus_large = Resource::load_font("fonts/pingus" + std::string("-") + encoding);

  courier_small = Resource::load_font("fonts/courier_small" + std::string("-") + encoding);
  xterm        = Resource::load_font("fonts/courier_small" + std::string("-") + encoding);
  smallfont    = Resource::load_font("fonts/courier_small" + std::string("-") + encoding); //PingusResource::load_font("Fonts/smallfont","fonts");
  smallfont_h  = Resource::load_font("fonts/courier_small" + std::string("-") + encoding); // PingusResource::load_font("Fonts/smallfont_h","fonts");

  lcd          = Resource::load_font("fonts/courier_small" + std::string("-") + encoding); // PingusResource::load_font("Fonts/numbers", "fonts");
}

void deinit () 
{
  chalk_large  = Font();
  chalk_normal = Font();
  chalk_small  = Font();
  pingus_small = Font();
  pingus_small_fix_num = Font();
  pingus_large = Font();
  courier_small = Font();
  xterm = Font();
  smallfont = Font();
  smallfont_h = Font();
  lcd = Font();
}

} // namespace Fonts

/* EOF */
