//  $Id: ActionHolder.cc,v 1.35 2002/06/09 13:03:11 grumbel Exp $
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

#include <iostream>
#include "globals.hh"

#include "PingusError.hh"
#include "Timer.hh"
#include "globals.hh"
#include "PLF.hh"

#include "PinguActionFactory.hh"
#include "ActionHolder.hh"

using namespace boost;

ActionHolder::ActionHolder (PLF* plf)
{
  std::vector<ActionData> action_data = plf->get_actions ();
  
  for(std::vector<ActionData>::iterator i = action_data.begin(); i != action_data.end(); ++i) {
    set_actions(i->name, i->number_of);
  }
}

ActionHolder::~ActionHolder ()
{
  //FIXME: This is not really a good place to free the actions
  //FIXME: But not otherwise to possible at the moment due to the
  //FIXME: singleton thing.
  PinguActionFactory::instance ()->delete_actions ();
}

void
ActionHolder::set_actions(const std::string& name, int available)
{
  available_actions[name] = available;
}

void
ActionHolder::push_action(const std::string& name)
{
  available_actions[name]++;
}

int
ActionHolder::get_available(const std::string& name)
{
  return available_actions[name];
}

PinguAction*
ActionHolder::get_action(const std::string& name)
{
  if (unlimited_actions) // runtime option; defined in global.hh
    {    
      return PinguActionFactory::instance ()->create(name);
    } 
  else 
    {
      int& count = available_actions[name];
      if (count > 0) 
	{
	  --count;
	  return PinguActionFactory::instance ()->create(name);
	}
      else // Out of actions
	{
	  return 0;
	}
    }
}

/* EOF */
