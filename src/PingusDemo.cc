//  $Id: PingusDemo.cc,v 1.1 2000/02/04 23:45:18 mbn Exp $
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

#include <cstdio>
#include <assert.h>

#include "globals.hh"
#include "PingusDemo.hh"
#include "PingusError.hh"

PingusDemo::PingusDemo()
{
}

PingusDemo::~PingusDemo()
{
  in.close();
}

void
PingusDemo::open(string filename, PingusDemoMode mode)
{
  switch(mode) {
  case (PingusDemoMode)play:
    in.open(filename.c_str());
    
    if (!in) 
      throw PingusError("PingusDemo: Couldn't open out file: " + filename);
    break;
  case (PingusDemoMode)record:
    out.open(filename.c_str());
    if (!out) 
      throw PingusError("PingusDemo: Couldn't open in file: " + filename);
    break;
  }
}

PingusEvent
PingusDemo::get_next_event(void)
{
  assert(in);
  PingusEvent event;
  // BUG: This could be very slow:
  char c = ' ';
  string temp;

  while ((c = in.get()) != '\n' && !in.eof()){
    temp += c;
  }

  // spliting the string
  {
    if (verbose) {
      cout << "Event:"  << temp << endl;
    }

    char tmp[1024];
    sscanf(temp.c_str(), "%d:%[^\n]", &event.game_time, tmp);
    
    event.str = tmp;
  }  

  return event;
}

void
PingusDemo::set_next_event(string event)
{
  out << event << endl;
  cout << event << endl;
}

/* EOF */
