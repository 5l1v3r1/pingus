//  $Id: root_gui_manager.cxx,v 1.10 2003/10/19 12:25:47 grumbel Exp $
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

#include <assert.h>
#include "root_gui_manager.hxx"
#include "../input/controller.hxx"

namespace Pingus {

using namespace GUI;
using namespace Input;

RootGUIManager::RootGUIManager (Input::Controller* c)
  : controller(c)
{
}

RootGUIManager::~RootGUIManager ()
{
}

void
RootGUIManager::update (float delta)
{
  assert (!"ERROR RootGUIManager absolete");
  assert (controller);
  //GUIManager::update (delta);
  //process_input (controller->get_events ());

  UNUSED_ARG(delta);
}

} // namespace Pingus

/* EOF */
