//  $Id: game_session.cxx,v 1.36 2003/03/26 12:01:17 grumbel Exp $
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

#include <iostream>
#include "gui/screen_manager.hxx"
#include "client.hxx"
#include "true_server.hxx"
#include "game_session.hxx"
#include "game_session_result.hxx"
#include "timer.hxx"
#include "pingus_resource.hxx"
#include "plf.hxx"
#include "pingu_holder.hxx"
#include "world.hxx"
#include "result_screen.hxx"
#include "savegame_manager.hxx"
#include "globals.hxx"

PingusGameSession::PingusGameSession (PLFHandle arg_plf, bool arg_show_result_screen)
  : plf(arg_plf),
    show_result_screen(arg_show_result_screen)
{
  Timer plf_timer("GameSession plf creation");

  plf_timer.stop();

  Timer server_timer("GameSession server creation");
  server = new TrueServer(*plf);
  server_timer.stop();

  Timer client_timer("GameSession client creation");
  client = new Client(server);
  client_timer.stop();

  number_of_redraws = 0;
  number_of_updates = 0;

  left_over_time = 0;
}

PingusGameSession::~PingusGameSession ()
{
  if (maintainer_mode)
    std::cout << "XXXXXXXX"
              << " Redraws: " << number_of_redraws
              << " Updates: " << number_of_updates 
              << " FrameSkip: " << number_of_updates - number_of_redraws
              << std::endl;

  delete client;
  delete server;
}

void
PingusGameSession::on_startup()
{
  client->on_startup();
}

void
PingusGameSession::on_shutdown()
{
  client->on_shutdown();
}

PingusGameSessionResult
PingusGameSession::get_result ()
{
  return PingusGameSessionResult ();
}

bool
PingusGameSession::draw(GraphicContext& gc)
{
  ++number_of_redraws;
  client->draw (gc);
  return true;
}

void
PingusGameSession::update (const GameDelta& delta)
{
  // FIXME: Timing code could need another rewrite...
  if (server->is_finished())
    {
      //ScreenManager::instance()->pop_screen();
      PinguHolder* pingu_holder = server->get_world()->get_pingus();
      Result result;
      
      result.plf    = server->get_plf();

      result.saved  = pingu_holder->get_number_of_exited();
      result.killed = pingu_holder->get_number_of_killed();
      result.total  = server->get_plf()->get_pingus();

      result.needed = server->get_plf()->get_number_to_save();

      result.max_time  = server->get_plf()->get_time();
      result.used_time = server->get_time();

      { // Write the savegame
        Savegame savegame;
        savegame.levelname    = result.plf->get_filename();
        savegame.time         = result.used_time;
        savegame.saved_pingus = result.saved;
        if (result.saved >= result.needed)
          savegame.status     = Savegame::FINISHED;
        else
          savegame.status     = Savegame::ACCESSIBLE;

        SavegameManager::instance()->store(savegame);
      }

      if (show_result_screen)
        ScreenManager::instance()->replace_screen(new ResultScreen(result));
      else
        ScreenManager::instance()->pop_screen();
      return;
    }

  int time_passed = int(delta.get_time() * 1000) + left_over_time;
  int update_time = game_speed;

  left_over_time = 0;

  {
    int i;
    for (i = 0; 
         ((i * update_time < time_passed)
          || i < min_frame_skip)
           && !(i > max_frame_skip);
         ++i)
      {
        // This updates the world and all objects
        server->update ();
        ++number_of_updates;
      }
      
    // Time that got not used for updates
    left_over_time = time_passed - (i * update_time);
  }

  if (!max_cpu_usage && left_over_time < 0)
    {
      // FIXME: This doesn't really belong here
      CL_System::sleep(-left_over_time);
    }
  
  // Client is independend of the update limit, well, not completly...
  client->update (delta);

#if 0
  // Move the game one loop further
  server->update ();
  client->update (delta);
#endif
}

void
PingusGameSession::on_pause_press ()
{
  client->on_pause_press (); 
}

void
PingusGameSession::on_fast_forward_press ()
{
  client->on_fast_forward_press (); 
}

void
PingusGameSession::on_armageddon_press () 
{
  client->on_armageddon_press (); 
}

void
PingusGameSession::on_escape_press () 
{ 
  client->on_escape_press (); 
}

/* EOF */
