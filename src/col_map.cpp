//  $Id: col_map.cxx,v 1.23 2003/10/21 21:37:06 grumbel Exp $
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

#include <iostream>
#include "SDL.h"
#include "display/drawing_context.hpp"
#include "globals.hpp"
#include "col_map.hpp"
#include "collision_mask.hpp"
#include "pixel_buffer.hpp"
#include "pingus_error.hpp"
#include "gettext.h"

#define COLMAP_WITH_MEMORY_HOLE 1


// Obtain the colmap from a memory area
ColMap::ColMap(int w, int h)
  : serial(0),
    width(w),
    height(h),
    colmap(new unsigned char[width * height])
{
  // Clear the colmap
  memset(colmap, Groundtype::GP_NOTHING, sizeof(unsigned char) * width * height);
}

ColMap::~ColMap()
{
  //std::cout << "ColMap:~ColMap" << std::endl;
  delete[] colmap;
}

int
ColMap::getpixel(int x, int y)
{
  if (x >= 0 && x < width && y >= 0 && y < height) {
    return colmap[x+y*width];
  } else {
    return Groundtype::GP_OUTOFSCREEN;
  }
}

unsigned char*
ColMap::get_data()
{
  return colmap;
}

int
ColMap::get_height()
{
  return height;
}

int
ColMap::get_width()
{
  return width;
}

void
ColMap::remove(const CollisionMask& mask, int x, int y)
{
#if 0
	++serial;

  int swidth  = provider.get_width();
  int sheight = provider.get_height();
  int y_offset = -y;
  int x_offset = -x;
  if (y_offset < 0) y_offset = 0;
  if (x_offset < 0) x_offset = 0;

  provider.lock();

  if (provider.get_format().get_depth() == 32)
	{
		for(int line = y_offset; line < sheight && (line + y) < height; ++line)
		{
			for (int i = x_offset; i < swidth && (i+x) < width; ++i)
			{
				if (provider.get_pixel(i, line).get_alpha() != 0)
				{
					if (colmap[i + (width*(line+y) + x)] != Groundtype::GP_SOLID)
						colmap[i + (width*(line+y) + x)] = Groundtype::GP_NOTHING;
				}
			}
		}
	}
	else if (provider.get_format().get_depth() == 8)
	{
		unsigned char* buffer;
		buffer = static_cast<unsigned char*>(provider.get_data());

		for(int line = y_offset; line < sheight && (line + y) < height; ++line)
		{
			for (int i = x_offset; i < swidth && (i+x) < width; ++i)
			{
				if (buffer[i + (swidth*line)])
				{
					if (colmap[i + (width*(line+y) + x)] != Groundtype::GP_SOLID)
						colmap[i + (width*(line+y) + x)] = Groundtype::GP_NOTHING;
				}
			}
		}
	}
	else
	{
		PingusError::raise("ColMap::remove() - image format not supported");
	}

	provider.unlock();
#endif
}

void
ColMap::put(int x, int y, Groundtype::GPType p)
{
  ++serial;

  if (x > 0 && x < width
      && y > 0 && y < height)
    {
      colmap[x+y*width] = p;
    }
  else
    {
      if (verbose > 2)
	std::cout << "ColMap: remove: Out of map" << std::endl;
    }
}

bool
ColMap::blit_allowed (int x, int y,  Groundtype::GPType gtype)
{
  // FIXME: Inline me
  if (gtype == Groundtype::GP_BRIDGE)
    {
      int pixel = getpixel (x, y);
      return pixel == Groundtype::GP_NOTHING;
    }
  else
    {
      return true;
    }
}

// Puts a surface on the colmap
void
ColMap::put(const CollisionMask& mask, int sur_x, int sur_y, Groundtype::GPType pixel)
{
  // transparent groundpieces are only drawn on the gfx map, not on the colmap
  if (pixel == Groundtype::GP_TRANSPARENT)
    return;

  if ((sur_x > width) || (sur_y > height))
    {
      if (verbose > 3)
	{
	  std::cout << "Warning: ColMap: Spot out of screen" << std::endl;
	  std::cout << "sur_x: " << sur_x << " sur_y: " << sur_y << std::endl;
	}
      return;
    }

  uint8_t* source = mask.get_data();
  for (int y=0; y < mask.get_height(); ++y)
    for (int x=0; x < mask.get_width(); ++x)
      {
        if (source[y * mask.get_width() + x])
          if (blit_allowed(x + sur_x, y + sur_y, pixel))
            put(x + sur_x, y + sur_y, pixel);
      }

#if 0 

  // FIXME: Little slow
  provider.lock();
  // Rewritting blitter for 32bit depth (using get_pixel())
  for (int y=0; y < provider.get_height(); ++y)
    for (int x=0; x < provider.get_width(); ++x)
      {
        Color color = provider.get_pixel(x, y);
        if (color.a > 32) // Alpha threshold
          {
            if (blit_allowed (x + sur_x, y + sur_y, pixel))
              put(x + sur_x, y + sur_y, pixel);
          }
      }
  provider.unlock();

  else if (provider.get_format().get_depth() == 8)
    {
      unsigned char* buffer;
      int swidth = provider.get_width();
      int sheight = provider.get_height();
      int y_offset = -sur_y;
      int x_offset = -sur_x;
      if (y_offset < 0) y_offset = 0;
      if (x_offset < 0) x_offset = 0;

      //provider.lock();
      buffer = static_cast<unsigned char*>(provider.get_data());

      if (provider.get_format().has_colorkey())
	{
	  unsigned int colorkey = provider.get_format().get_colorkey();
	  for(int line = y_offset; line < sheight && (line + sur_y) < height; ++line)
	    for (int i = x_offset; i < swidth && (i+sur_x) < width; ++i)
	      {
		if (buffer[i + (swidth*line)] != colorkey)
		  {
		    if (blit_allowed (i + sur_x, line + sur_y, pixel))
		      colmap[i + (width*(line+sur_y) + sur_x)] = pixel;
		  }
	      }
	}
      else
	{
	  for(int line = y_offset; line < sheight && (line + sur_y) < height; ++line)
	    for (int i = x_offset; i < swidth && (i+sur_x) < width; ++i)
	      {
		if (blit_allowed (i + sur_x, line + sur_y, pixel))
		  colmap[i + (width*(line+sur_y) + sur_x)] = pixel;
	      }
	}
    }
  else
    {
      std::cout << "ColMap: Unsupported color depth, ignoring" << std::endl;
    }

  // FIXME: Memory hole
  // provider.unlock();
#endif
}

void
ColMap::draw(DrawingContext& gc)
{
#if 0
  PixelBuffer canvas(width, height);
  unsigned char* buffer;

  canvas.lock();
  buffer = static_cast<unsigned char*>(canvas.get_data());

  for(int i = 0; i < (width * height); ++i)
    {
      switch(colmap[i])
	{
	case Groundtype::GP_NOTHING:
	  buffer[i * 4 + 0] = 0;
	  buffer[i * 4 + 1] = 0;
	  buffer[i * 4 + 2] = 0;
	  buffer[i * 4 + 3] = 0;
	  break;

	case Groundtype::GP_SOLID:
	  buffer[i * 4 + 0] = 255;
	  buffer[i * 4 + 1] = 100;
	  buffer[i * 4 + 2] = 100;
	  buffer[i * 4 + 3] = 100;
	  break;

	case Groundtype::GP_BRIDGE:
	  buffer[i * 4 + 0] = 255;
	  buffer[i * 4 + 1] = 0;
	  buffer[i * 4 + 2] = 0;
	  buffer[i * 4 + 3] = 200;
	  break;

	default:
	  buffer[i * 4 + 0] = 255;
	  buffer[i * 4 + 1] = 200;
	  buffer[i * 4 + 2] = 200;
	  buffer[i * 4 + 3] = 200;
	  break;
	}
    }

  canvas.unlock();

  Sprite sprite(canvas);

  //FIXME:gc.draw(sprite, 0, 0);
#endif
}

unsigned
ColMap::get_serial()
{
  return serial;
}


/* EOF */
