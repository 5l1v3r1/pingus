//  $Id: Cursor.hh,v 1.3 2002/01/13 15:24:18 grumbel Exp $
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

#ifndef CURSOR_HH
#define CURSOR_HH

#include "boost/smart_ptr.hpp"
#include "Display.hh"
#include "Controller.hh"
#include "Sprite.hh"

class Cursor : public DisplayHook
{
private:
  Sprite sprite;
  boost::shared_ptr<Controller> controller;
  
public:
  Cursor (std::string ident, std::string datafile, boost::shared_ptr<Controller>);
  virtual ~Cursor ();
  
  virtual void update (float delta);
  virtual void on_event();
};

#endif

/* EOF */
