//  $Id: spot_map.hxx,v 1.11 2003/10/22 11:11:22 grumbel Exp $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#ifndef HEADER_PINGUS_SPOT_MAP_HXX
#define HEADER_PINGUS_SPOT_MAP_HXX

#include <vector>
#include <ClanLib/Display/pixel_buffer.h>
#include "globals.hxx"
#include "pingu_map.hxx"
#include "worldobjsdata/groundpiece_data.hxx"

class CL_PixelBuffer;

namespace Pingus {

class PLF;
class ColMap;

class MapTileSurface
{
private:
  bool empty;

public:
  CL_Surface     surface;
  CL_PixelBuffer buffer;

  MapTileSurface ();
  virtual ~MapTileSurface ();

  MapTileSurface (const MapTileSurface& old);
  MapTileSurface& operator= (const MapTileSurface& old);

  CL_Surface get_surface() const { return surface; }
  void reload ();

  inline bool is_empty() { return empty; }
  void mark_dirty ();
  void set_empty (bool);
};

/** This map type is the defaulh maptype, it is should be used for the
    most levels. It allows to construct a map, from a set of simple
    small images, this allows the generation of large map without
    using to much diskspace. */
class PingusSpotMap : public PinguMap
{
private:
  ColMap* colmap;

  typedef std::vector<MapTileSurface>::size_type TileIter;

  /** The tiles out of which the map is constructed */
  std::vector<std::vector<MapTileSurface> > tile;

  /** Width of the map */
  int width;
  /** Height of the map */
  int height;

public:
  PingusSpotMap(PLF*);
  virtual ~PingusSpotMap();

  void draw(GraphicContext& gc);

  ColMap* get_colmap();

  int  get_height();
  int  get_width();

  /** Put the gives surface provider onto the given coordinates */
  void put(CL_PixelBuffer, int x, int y);

  /** Remove the gives surface provider onto the given coordinates
      (everything non-transparent is removed from the map) */
  void remove(CL_PixelBuffer, int x, int y);

  float get_z_pos () const { return 0; }

private:
  /** Low level version of the remove() call, acts on a single canvas
      instead on the complete map-tiles */
  void put_alpha_surface(CL_PixelBuffer provider, CL_PixelBuffer sprovider,
			 int x, int y, int real_x, int real_y);

  /** Draw the collision map onto the screen */
  void draw_colmap(GraphicContext& gc);

  PingusSpotMap (const PingusSpotMap&);
  PingusSpotMap& operator= (const PingusSpotMap&);
};

} // namespace Pingus

#endif

/* EOF */
