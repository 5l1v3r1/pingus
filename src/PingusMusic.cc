//  $Id: PingusMusic.cc,v 1.2 2000/02/09 21:43:40 grumbel Exp $
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
#include "algo.hh"
#include "globals.hh"
#include "PingusMusic.hh"
#include "PingusError.hh"

PingusMusic::PingusMusic(PLF* data)
{
  string filename;

  if (verbose) 
    cout << "PingusMusic: Creating PingusMusic" << endl;

  filename = data->get_music().res_name;

  filename = find_file(pingus_datadir, "music/" + filename);
  
  if (verbose)
    cout << "PingusMusic: Opening file: " << filename << endl;

  if (!exist(filename)) {
    string error_mes;
    error_mes += "PingusMusic: Couldn't open \'";
    error_mes += filename;
    error_mes +=  "\'";
    cout <<
      "=====================================================================\n"
      "   You probably forgot to download the pingus sound pakage, it is\n"
      "   available at the pingus webpage at: http://pingus.home.pages.de\n"
      "=====================================================================\n"
	 << endl;
    throw PingusError(error_mes);
  }
}

PingusMusic::~PingusMusic()
{
}

void
PingusMusic::play()
{
}

void
PingusMusic::stop()
{
}

void
PingusMusic::set_volume()
{
}

/* EOF */
