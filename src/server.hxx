//  $Id: server.hxx,v 1.12 2002/10/04 16:54:04 grumbel Exp $
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

#ifndef HEADER_PINGUS_SERVER_HXX
#define HEADER_PINGUS_SERVER_HXX

#include <vector>
#include "server_event.hxx"
#include "action_holder.hxx"

class Pingu;
class PLF;
class World;
class DemoRecorder;
class GoalManager;

/** A abstract server-like class */
class Server
{
private:
  PLF* plf;
  World* world;

  /** Manager class for the number of available actions */
  ActionHolder action_holder;

  GoalManager* goal_manager;

  DemoRecorder* demo_recorder;

public:
  Server(PLF*);
  virtual ~Server();

  virtual void update();

  PLF* get_plf () { return plf; }

  int get_time();

  World* get_world();
  ActionHolder* get_action_holder();

  /** @return true if the server is finished and the game can be
      exited */
  bool is_finished();

  /** set the server into the finshed state, this is used when you
      press ESCAPE inside a game */
  void set_finished();

  /* Event handling stuff */
  void send_armageddon_event();
  void send_pingu_action_event(Pingu* pingu, Actions::ActionName action);
  
private:
  Server (const Server&);
  Server& operator= (const Server&);
};

#endif

/* EOF */
