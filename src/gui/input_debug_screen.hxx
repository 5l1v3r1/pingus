//  $Id: input_debug_screen.hxx,v 1.3 2003/10/19 12:25:47 grumbel Exp $
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

#ifndef HEADER_PINGUS_INPUT_DEBUG_SCREEN_HXX
#define HEADER_PINGUS_INPUT_DEBUG_SCREEN_HXX

#include "screen.hxx"

namespace Pingus {

class InputDebugScreen : public Screen
{
private:

public:
  InputDebugScreen ();
  virtual ~InputDebugScreen ();

  /** Draw this screen */
  bool draw (GraphicContext& gc);

  /** Pass a delta to the screen */
  void update (const GameDelta& delta);

  /** Called once the screen gets activated and becomes the current
      screen */
  void on_startup ();

  /** Called once the screen gets replaced or poped or shadowed by a
      newly pushed screen */
  void on_shutdown ();
};

} // namespace Pingus

#endif

/* EOF */
