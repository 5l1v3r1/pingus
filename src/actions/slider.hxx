//  $Id: slider.hxx,v 1.3 2002/06/26 19:13:13 grumbel Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_SLIDER_HXX
#define HEADER_PINGUS_ACTIONS_SLIDER_HXX

#include "../sprite.hxx"
#include "../pingu_action.hxx"

class Slider : public PinguAction
{
private:
  Sprite sprite;
  float  speed;
public:
  Slider ();

  void  init(void);
  std::string get_name() const { return "Slider"; }
  void  update(float delta);
  void  draw_offset(int x, int y, float s);
};

#endif

/* EOF */
