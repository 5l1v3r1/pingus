//  $Id: PingusMusicProvider.hh,v 1.1 2000/04/20 17:17:15 grumbel Exp $
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

#ifndef PINGUSMUSICPROVIDER_HH
#define PINGUSMUSICPROVIDER_HH

#include <list>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class PingusMusicProvider
{
private:
  struct music_pair {
    Mix_Music* data;
    string     filename;
  };
  static list<music_pair> music;
public:
  static Mix_Music* load(string);
  static Mix_Music* get(string);
};

#endif

/* EOF */
