//  $Id: server.cxx,v 1.20 2002/10/03 01:02:12 grumbel Exp $
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

#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "system.hxx"
#include "pingu.hxx"
#include "server.hxx"
#include "pingu_holder.hxx"
#include "pingus_error.hxx"
#include "string_converter.hxx"
#include "game_time.hxx"
#include "world.hxx"

using namespace std;
using Actions::action_from_string;

/** PinguID search functor */
struct PinguId : public unary_function<Pingu*, bool>
{
  int pingu_id;

  PinguId(){}
  PinguId(int i) {
    pingu_id = i;
  }
 
  bool operator()(Pingu* pingu) {
    return (pingu->get_id() == pingu_id);
  }
};

PingusEvent::PingusEvent ()
{
}

PingusEvent::PingusEvent (const std::string& event_str)
{
  std::string game_time_str;
  std::string::size_type split_pos = event_str.find(":");
  
  game_time_str = event_str.substr(0, split_pos);
  str = event_str.substr(split_pos + 1);

  if (sscanf(game_time_str.c_str(), "%d", &game_time) != 1) {
    PingusError::raise("PingusEvent: Unable to parse: " + event_str);
  }
}

PingusEvent::PingusEvent (const PingusEvent& old) : game_time(old.game_time),
                                                    str(old.str)
{
}

PingusEvent&
PingusEvent::operator= (const PingusEvent& old)
{
  if (this == &old)
    return *this;
    
  game_time = old.game_time;
  str       = old.str;
  
  return *this;
}


Server::Server (PLF* plf)
  : action_holder (plf)
{
  demo_mode = false;
  get_next_event = true;
  finished = false;
  //demo_out.open("/tmp/demo.plt", (PingusDemoMode)record); 
}

Server::~Server ()
{
  // Here we write down the demo file
  // FIXME: syntax will be different in the final version, this is just a quick hack
  std::string date_str;
  
  {
    char buffer[32];
    time_t curtime;
    struct tm *loctime;
    curtime = time (NULL);
    loctime = localtime(&curtime);
    strftime(buffer, 32, "%Y%m%d-%H%M%S", loctime);

    date_str = buffer;
    
    date_str = System::get_statdir() + "demos/" + date_str + ".xml";
  }

  std::cout << "Writing demo to: " << date_str << std::endl;

  std::ofstream xml(date_str.c_str());
  
  xml << "<pingus-events>" << std::endl;
  for(std::vector<ServerEvent>::iterator i = events.begin();
      i != events.end();
      ++i)
    i->write_xml(xml);
  xml << "</pingus-events>" << std::endl;
}

World*
Server::get_world()
{
  return world;
}

void
Server::update()
{
}

void
Server::send_armageddon_event()
{
  armageddon = true;
  world->armageddon();

  events.push_back(ServerEvent::make_armageddon_event(get_time()));
}

void
Server::send_pingu_action_event(Pingu* pingu, Actions::ActionName action)
{
  PinguAction* tmp_action = action_holder.get_action(action);
	  
  if (tmp_action)
    {
      if (!(pingu->request_set_action(tmp_action)))
	{
	  action_holder.push_action(action);
	}
    }

  events.push_back(ServerEvent::make_pingu_action_event(get_time(), pingu->get_id(), action));
}

bool
Server::is_finished()
{
  if (finished) {
    return true;
  } else {
    return world->is_finished();
  }
}

void
Server::set_finished()
{
  finished = true;
}

ActionHolder*
Server::get_action_holder()
{
  return &action_holder;
}

int
Server::get_time()
{
  return get_world()->get_game_time()->get_ticks();
}

/* EOF */
