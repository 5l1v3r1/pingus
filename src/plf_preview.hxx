//  $Id: plf_preview.hxx,v 1.5 2002/08/23 15:49:50 torangan Exp $
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

#ifndef HEADER_PINGUS_PLF_PREVIEW_HXX
#define HEADER_PINGUS_PLF_PREVIEW_HXX

#include "pingus.hxx"
#include <ClanLib/Display/Display/surface.h>

class CL_Canvas;
class PLF;

/// A class to load and manage a small level preview surface
class PLFPreview
{
private:
  CL_Surface surface;
  CL_Canvas* provider;
  PLF* plf;
public:
  PLFPreview(PLF*);
  void load(PLF*);
  CL_Surface get_surface();
  
private:
  PLFPreview (const PLFPreview&);
  PLFPreview operator= (const PLFPreview&);
};

#endif

/* EOF */



