//  $Id: playfield_view.hxx,v 1.10 2003/10/19 12:25:47 grumbel Exp $
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

#ifndef HEADER_PINGUS_PLAYFIELD_VIEW_HXX
#define HEADER_PINGUS_PLAYFIELD_VIEW_HXX

#include "gui/display_graphic_context.hxx"
#include "gui_obj.hxx"

class CL_Rect;

namespace Pingus {

class Vector;
class World;
class Pingu;

/** FIXME: Document me */
class PlayfieldView : public GuiObj
{
private:
  DisplayGraphicContext gc;
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
  void scroll (Vector delta);

  // Return the pingu at the given *screen* coordinates
  Pingu* get_pingu (const Vector& pos);

private:
  PlayfieldView (const PlayfieldView&);
  PlayfieldView& operator= (const PlayfieldView&);
};

} // namespace Pingus

#endif

/* EOF */
