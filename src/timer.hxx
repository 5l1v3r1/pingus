//  $Id: timer.hxx,v 1.3 2002/08/16 13:03:35 torangan Exp $
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

#ifndef HEADER_PINGUS_TIMER_HXX
#define HEADER_PINGUS_TIMER_HXX

#include "pingus.hxx"

/** A simple class for benchmark purpose. It lets you start and stop a
    timer and recieve the time passed.*/
class Timer
{
private:
  ///
  int last_time;
  ///
  bool running;
public:
  ///
  Timer();

  /** Start the timer
      @return The current time, as returned by CL_System::get_time() */
  int start();
  /** Stop the timer
      @return The time passed since the last start() */
  int stop();
}///
;

#endif

/* EOF */
