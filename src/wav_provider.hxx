//  $Id: wav_provider.hxx,v 1.6 2003/04/19 10:23:17 torangan Exp $
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

#ifndef HEADER_PINGUS_WAV_PROVIDER_HXX
#define HEADER_PINGUS_WAV_PROVIDER_HXX

#include "pingus.hxx"
#include <map>
#include <string>

class Mix_Chunk;

class PingusWavProvider
{
private:
  static std::map<std::string, Mix_Chunk*> wave;

public:
  static Mix_Chunk* load (const std::string& str);

private:
  PingusWavProvider ();
  PingusWavProvider (const PingusWavProvider&);
  PingusWavProvider& operator= (const PingusWavProvider&);
};

#endif

/* EOF */
