//  $Id: TrueServer.cc,v 1.1 2000/02/04 23:45:19 mbn Exp $
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

#include "PingusLevelDesc.hh"
#include "GameTime.hh"
#include "globals.hh"

#include "TrueServer.hh"

TrueServer::TrueServer(PLF* level_data, Result& r)
{
  local_game_speed = game_speed;
  world = 0;
  client_needs_redraw = true;
  start(level_data);
}

TrueServer::TrueServer()
{
  world = 0;
}

TrueServer::~TrueServer()
{
}

void
TrueServer::let_move(void)
{
  if (enough_time_passed()) {
    client_needs_redraw = true;
    GameTime::increase();
    Server::let_move();
    world->let_move();
  }
}

void
TrueServer::start(PLF* level_data)
{
  vector<button_data> bdata;
  PingusLevelDesc leveldesc(level_data);

  bdata = level_data->get_buttons();

  for(vector<button_data>::iterator b = bdata.begin(); b != bdata.end(); ++b) {
    action_holder.add_action(b->name, b->number_of);
  }

  fast_forward = false;
  pause = false;
  last_time = 0;
  local_game_speed = game_speed;

  if (world)
    delete world;

  world = new World;
  leveldesc.draw(PingusLevelDesc::LOADING);
  world->init(level_data);
  leveldesc.draw(PingusLevelDesc::FINISHED);
  GameTime::reset();
}

bool
TrueServer::enough_time_passed(void)
{
  if (pause) {
    return false;
  }

  if (fast_forward) {
    // BUG: This should skip some frames, so it also works on slower
    // machines
    last_time = CL_System::get_time();
    return true;
  } else {
    if (last_time + local_game_speed > CL_System::get_time())
      return false;
    else {
      // cout << "Delta Time: " << CL_System::get_time() - last_time + local_game_speed << endl;
      last_time = CL_System::get_time();
      return true;
    }
  }
}

void
TrueServer::set_fast_forward(bool value)
{
  fast_forward = value;
  if (fast_forward)
    local_game_speed = 5;
  else 
    local_game_speed = game_speed;
}

void 
TrueServer::set_pause(bool value)
{
  pause = value;
}

bool
TrueServer::get_pause()
{
  return pause;
}

bool
TrueServer::get_fast_forward()
{
  return fast_forward;
}

bool
TrueServer::needs_redraw()
{
  if (client_needs_redraw) {
    client_needs_redraw = false;
    return true;
  }
  return false;
}

/* EOF */
