//  $Id: PingusCounter.hh,v 1.3 2000/03/16 21:28:05 grumbel Exp $
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

#ifndef PINGUSCOUNTER_HH
#define PINGUSCOUNTER_HH

#include <ClanLib/core.h>

#include "Client.hh"
#include "World.hh"
#include "GuiObj.hh"

class Client;

class PingusCounter : public GuiObj
{
private:
  CL_Font* font;
  World* world;
  Client* client;
public:
  PingusCounter();

  void draw(void);
  void set_client(Client*);
};

#endif

/* EOF */
