//  $Id: bmp_map.cxx,v 1.2 2002/08/16 15:13:59 torangan Exp $
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

#include <ClanLib/Display/Display/surfaceprovider.h>
#include "bmp_map.hxx"
#include "globals.hxx"
#include "pingus_error.hxx"
#include "pingus_resource.hxx"
#include "col_map.hxx"

/* Headers needed for i18n / gettext */
#include <clocale>
#include <config.h>
#include "my_gettext.hxx"


PinguBmpMap::PinguBmpMap()
{
  colmap  = 0;
}

PinguBmpMap::PinguBmpMap(ResDescriptor res_desc)
{
  colmap = 0;
  if (verbose > 1)
    std::cout << "Creating BMP Map" << std::endl;

  surface = PingusResource::load_surface(res_desc);
  
  if (!surface) {
    PingusError::raise(res_desc.res_name + _(": Could not open file\n"));;
  }
}

PinguBmpMap::~PinguBmpMap()
{
  /* BUG: Segfault
  if (surface)
    delete surface;
  */
}

int
PinguBmpMap::get_width()
{
  return surface.get_width();
}

int
PinguBmpMap::get_height()
{
  return surface.get_height();  
}

void
PinguBmpMap::draw_offset(int x, int y, float s)
{
  if (s == 1.0)
    surface.put_screen(x,y);	  
  else
    surface.put_screen((int)(x * s), (int)(y * s),s , s);
}

ColMap*
PinguBmpMap::get_colmap()
{
  unsigned char* buffer;
  void* vbuffer;
  CL_SurfaceProvider* provider;

  std::cout << "PinguBmpMap::get_colmap" << std::endl;

  assert(surface);

  if (colmap) {
    return colmap;
  } else {
    provider = surface.get_provider();
    assert(provider);
    provider->lock();

    vbuffer = provider->get_data();
    assert(vbuffer);
    if (provider->get_depth() != 8)
      PingusError::raise(_("PingusBmpMap::get_colmap: Surface has wrong pixel format, need 8bpp!"));
    
    buffer = new unsigned char [provider->get_pitch() * provider->get_height()];
    memcpy(buffer, vbuffer, provider->get_pitch() *  provider->get_height());

    colmap = new ColMap();
    colmap->load(buffer, get_width(), get_height());

    provider->unlock();
    return colmap;
  }

  //  return 0;
}

CL_Surface
PinguBmpMap::get_surface()
{
  return CL_Surface ();
}

/* EOF */
