//  $Id: game_counter.hxx,v 1.6 2002/09/27 11:26:43 torangan Exp $
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

#ifndef HEADER_PINGUS_GAME_COUNTER_HXX
#define HEADER_PINGUS_GAME_COUNTER_HXX

#include "pingus.hxx"

class GameCounter
{
public:
  enum CounterType { loop, once, ping_pong };
private:
  int last_time;
  double count;
  double add;
  double size;
  bool is_finished;
  CounterType type;

  void check_overflow (void);
public:
  GameCounter ();
  ~GameCounter ();

  void set_type (CounterType t);
  void set_size (int);
  int  get_size ();
  bool finished ();
  void set_speed (double i);
  int  value ();
  bool enough_time_passed ();
  int  operator++ ();
  int  operator++ (int);
  int  operator-- ();
  int  operator= (int i);
  operator int ();
  
private:
  GameCounter (const GameCounter&);
  GameCounter& operator= (const GameCounter&);
};

#endif

/* EOF */
