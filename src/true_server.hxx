//  $Id: true_server.hxx,v 1.2 2002/06/24 22:52:57 grumbel Exp $
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

#ifndef HEADER_PINGUS_TRUE_SERVER_HXX
#define HEADER_PINGUS_TRUE_SERVER_HXX

#include "server.hxx"

/** FIXME: This whole Server/Client concept is screwed */
class TrueServer : public Server
{
private:
  bool fast_forward;
  bool pause;
  unsigned int  last_time;
  int  local_game_speed;
  bool client_needs_redraw;
  float delta;

  /** Reference to the PLF for this level, this must not be deleted */
  PLF* plf;
public:
  TrueServer(PLF* plf);
  virtual ~TrueServer();

  bool enough_time_passed(void);
  void update(float delta);
  bool needs_redraw();
  /** Return a reference to the plf used for this level */
  PLF* get_plf ();
  void set_fast_forward(bool value);
  bool get_fast_forward();
  
  void set_pause(bool);
  bool get_pause();
};

#endif

/* EOF */
