//  $Id: blitter.hh,v 1.1 2000/02/04 23:45:19 mbn Exp $
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

#ifndef BLITTER_HH
#define BLITTER_HH

#include <ClanLib/core.h>


/*void put_surface(CL_LockableSurface* provider, CL_Surface* surface,
		 int x, int y);
void put_surface(CL_LockableSurface* provider, CL_SurfaceProvider* surface,
                 int x, int y);
*/
void put_surface(CL_Canvas*, CL_SurfaceProvider*,
		 int x, int y);
void put_alpha_surface(CL_Canvas*, CL_SurfaceProvider*,
		 int x, int y);

CL_Surface* convert_to_emptyprovider(CL_Surface*);
CL_Canvas* convert_to_emptyprovider(CL_SurfaceProvider*);

#endif 

/* EOF */
