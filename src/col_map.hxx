//  $Id: col_map.hxx,v 1.5 2002/08/23 15:49:48 torangan Exp $
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

#ifndef HEADER_PINGUS_COL_MAP_HXX
#define HEADER_PINGUS_COL_MAP_HXX

#include "groundpiece_data.hxx"

class ResDescriptor;
class PixelStatus;
class CL_Surface;
class CL_SurfaceProvider;

// Collsion Map
/** The collision map is used to represent the enviroment where the
    Pingus walk around. The ground can have different properties, it
    can contain lava or water, it can be solid and many more. */
class ColMap
{
private:
  /// A array of uchar, each uchar represents a pixel on the map.
  unsigned char* colmap;

  /// The width of the collision map.
  int    width;

  /// The height of the collision map.
  int   height;

  ///
  bool    init;
  
public:
  /// Default constructor, it does nothing
  ColMap();

  /** Init the colmap from a given area of memory.
      The memory will be deleted in the destructor. */
  ColMap(unsigned char* b, int w, int h);

  /** delete[] the uchar array used for the colmap */
  ~ColMap();

  /** Returns the raw uchar array used for the inner representation of
      the colmap. */
  unsigned char* get_data();

  /// Returns the height of the collision map.
  int get_height();

  /// Returns the height of the collision map.
  int get_width();

  ///
  int  load(unsigned char*, int w, int h);

  int  load(ResDescriptor desc);

  int  getpixel(int x, int y);
  
  /** Return true if the given GroundType i*/
  bool blit_allowed (int x, int y,  GroundpieceData::GPType);

  void put(int x, int y, GroundpieceData::GPType p = GroundpieceData::GP_GROUND);
  void put(const CL_Surface&, int x, int y, GroundpieceData::GPType);
  void put(CL_SurfaceProvider*, int x, int y, GroundpieceData::GPType);

  /// void remove(int x, int y);
  void remove(const CL_Surface&, int x, int y);
  void remove(CL_SurfaceProvider*, int x, int y);

  void draw(int, int, float);
  
private:
  ColMap (const ColMap&);
  ColMap operator= (const ColMap&);
};

#endif /* COLMAP_HH */

/* EOF */
