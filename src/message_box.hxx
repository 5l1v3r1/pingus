//  $Id: message_box.hxx,v 1.2 2002/06/24 22:52:55 grumbel Exp $
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

#ifndef HEADER_PINGUS_MESSAGE_BOX_HXX
#define HEADER_PINGUS_MESSAGE_BOX_HXX

#include <string>

class CL_Font;

///
class PingusMessageBox
{
private:
  ///
  std::string str;
  ///
  CL_Font* font;
public:
  ///
  PingusMessageBox(std::string);

  ///
  void draw(void);
}///
;

#endif

/* EOF */
