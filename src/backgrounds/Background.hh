//  $Id: Background.hh,v 1.4 2000/12/30 23:54:06 grumbel Exp $
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

#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include "../WorldObj.hh"
#include "BackgroundData.hh"

/** Abstract representation of the background, all classes, which
    inherit from this can be used as background 
    @see BackgroundData */
class Background : public WorldObj
{
public:
  /// Empty costructor
  Background();

  /// Empty destructor
  virtual ~Background();

  /// Draw the background
  virtual void draw_offset(int x_of, int y_of, float s=1.0) =0;

  /// Move the background once a game loop
  virtual void let_move() =0;

  /** Create and allocate a new background out of the given background
      data */
  static boost::shared_ptr<Background> create (boost::shared_ptr<BackgroundData>);
};

#endif

/* EOF */
