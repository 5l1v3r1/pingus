//  $Id: PlayfieldView.hh,v 1.8 2002/06/10 11:00:27 torangan Exp $
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

#ifndef PLAYFIELDVIEW_HH
#define PLAYFIELDVIEW_HH

#include "GuiObj.hh"

class CL_Rect;
class CL_Vector;
class World;
class Pingu;

class PlayfieldView : public GuiObj
{
private:
  World * world;
  int x_offset;
  int y_offset;
public:
  PlayfieldView (World * w, const CL_Rect& rect);
  virtual ~PlayfieldView ();

  // Update the playfield
  void update (float delta);
  
  // Draw the playfied
  void draw ();
  
  // Scroll the playfield
  void scroll (CL_Vector delta);
  
  // Return the pingu at the given *screen* coordinates
  Pingu* get_pingu (const CL_Vector& pos);
};

#endif

/* EOF */
