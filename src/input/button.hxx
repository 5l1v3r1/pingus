//  $Id: button.hxx,v 1.11 2003/10/20 13:33:44 grumbel Exp $
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

#ifndef HEADER_PINGUS_INPUT_BUTTON_HXX
#define HEADER_PINGUS_INPUT_BUTTON_HXX

#include "../pingus.hxx"

namespace Pingus {
namespace Input {

/// abstract base class which defines the button interface
class Button
{
public:
  Button () { }
  virtual ~Button () { }

  /// returns true if the button is pressed, false otherwise
  virtual bool is_pressed ()      const =0;
  virtual void update     (float)       =0;

private:
  Button (const Button&);
  Button& operator= (const Button&);
};

} // namespace Input
} // namespace Pingus

#endif

/* EOF */
