//  $Id: screen_manager.hxx,v 1.4 2002/08/01 21:40:01 grumbel Exp $
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

#ifndef HEADER_PINGUS_SCREEN_MANAGER_HXX
#define HEADER_PINGUS_SCREEN_MANAGER_HXX

#include <vector>

class Screen;

class ScreenManager
{
private:
  static ScreenManager* instance_;

  /** Screen stack (first is the screen, second is delete_screen,
      which tells if the screen should be deleted onces it got poped
      or replaced) */
  std::vector<std::pair<Screen*, bool> > screens;

  ScreenManager ();
public:
  ~ScreenManager ();

  /** Start the screen manager and let it take controll, this will
      not return until the somebody signals a quit() */
  void display ();

  /** Replace the current screen */
  void replace_screen (Screen*, bool delete_screen = false);
    
  /** Add a screen on top of another screen */
  void push_screen (Screen*, bool delete_screen = false);

  /** Remove the current screen and fall back to the last one */
  void pop_screen ();

  static ScreenManager* instance ();
};

#endif

/* EOF */
