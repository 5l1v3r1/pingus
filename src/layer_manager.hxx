//  $Id: layer_manager.hxx,v 1.10 2003/04/19 10:23:17 torangan Exp $
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

#ifndef HEADER_PINGUS_LAYER_MANAGER_HXX
#define HEADER_PINGUS_LAYER_MANAGER_HXX

#include "pingus.hxx"
#include <cmath>
#include <ClanLib/Display/Display/surface.h>
#include "gui/graphic_context.hxx"

class LayerManager
{
private:
  class Layer
  {
  private:
    CL_Surface sur;

    float x_pos;
    float y_pos;

    float x_update;
    float y_update;

    float x_offset;
    float y_offset;

  public:
    Layer ()
      : x_pos(0), y_pos(0),
        x_update(0), y_update(0),
        x_offset(0), y_offset(0)
    {}

    Layer (const CL_Surface& arg_sur, float x_o, float y_o, float x_u, float y_u)
      : sur(arg_sur),
        x_pos(0), y_pos(0),
        x_update(x_u), y_update(y_u),
        x_offset(x_o), y_offset(y_o)
    {}

    void draw (GraphicContext& gc)
    {
      gc.draw(sur, int(x_pos + x_offset),
              int(y_pos + y_offset));
      gc.draw(sur, int(x_pos + x_offset - 800),
              int(y_pos + y_offset));
    }

    void update (float delta)
    {
      x_pos = fmod((x_pos + x_update * delta),800);
      y_pos = fmod((y_pos + y_update * delta),600);
    }
  };

  std::vector<Layer> layers;

public:
  LayerManager ();
  ~LayerManager();

  void add_layer (const CL_Surface& sur, float x_o, float y_o, float x_u, float y_u);
  void draw (GraphicContext& gc);
  void update (float delta);

private:
  LayerManager (const LayerManager&);
  LayerManager& operator= (const LayerManager&);
};

#endif

/* EOF */
