//  $Id: loading.hxx,v 1.8 2003/10/19 12:25:47 grumbel Exp $
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

#ifndef HEADER_PINGUS_LOADING_HXX
#define HEADER_PINGUS_LOADING_HXX

#include "pingus.hxx"
#include <ClanLib/Display/surface.h>

class CL_Font;

namespace Pingus {

class Loading
{
private:
  CL_Surface sur;
  CL_Font    font;
  bool is_init;

public:
  Loading ();
  ~Loading ();

  void init ();
  void draw ();
  void draw_progress (const std::string& str, float progress);

private:
  Loading (const Loading&);
  Loading& operator= (const Loading&);
};

extern Loading loading_screen;

} // namespace Pingus

#endif

/* EOF */

