//  $Id: PingusGameSession.cc,v 1.8 2001/07/27 15:00:47 grumbel Exp $
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

#include "XMLPLF.hh"
#include "Client.hh"
#include "TrueServer.hh"
#include "MouseController.hh"

#include "PingusGameSession.hh"

using boost::shared_ptr;
using boost::dummy_ptr;


bool
PingusGameSessionResults::finished ()
{
  // FIXME: Always success
  return true;
}

float
PingusGameSessionResults::percentage_saved ()
{
  return 100.0;
}

float 
PingusGameSessionResults::percentage_time ()
{
  return 100.0;
}

PingusGameSession::PingusGameSession (std::string arg_filename)
  : filename (arg_filename),
    plf(new XMLPLF (filename)),
    server (new TrueServer (plf)),
    client (new Client(shared_ptr<Controller>(new MouseController ()), 
		       server.get ()))
{
}

PingusGameSession::~PingusGameSession ()
{
}

void 
PingusGameSession::start ()
{
  std::cout << "PingusGameSession: Giving control to the client..." << std::endl;
  client->display();
  std::cout << "PingusGameSession: Got control back from the client." << std::endl;
}

PingusGameSessionResults 
PingusGameSession::get_results ()
{
  return PingusGameSessionResults ();
}

/* EOF */
