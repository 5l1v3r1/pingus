//  $Id: button_panel.cxx,v 1.6 2002/07/29 11:57:38 grumbel Exp $
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

#include <ClanLib/Core/System/system.h>
#include <ClanLib/Display/Input/mouse.h>
#include <ClanLib/Display/Display/display.h>
#include "globals.hxx"
#include "button_panel.hxx"
#include "controller.hxx"
#include "client.hxx"
#include "server.hxx"
#include "world.hxx"
#include "plf.hxx"

using namespace Pingus::Actions;

CL_Surface ButtonPanel::button_cap;

ButtonPanel::ButtonPanel(PLF* plf, Controller* arg_controller,
                  			 int arg_x_pos, int arg_y_pos)
  : armageddon_pressed(false),
    left_pressed(0),
    last_press(0),
    controller (arg_controller),
    x_pos (arg_x_pos), 
    y_pos (arg_y_pos)
{

  std::vector<ActionData> buttons_data = plf->get_actions();

  y_pos -= (buttons_data.size() * 38)/2 + 70;

  if (buttons_data.size() == 0)
    {
      std::cout << "ButtonPanel: No actions given in this level, fall back to default" << std::endl;
      buttons_data.push_back(ActionData(Bridger, 20));
      buttons_data.push_back(ActionData(Basher, 20));
      buttons_data.push_back(ActionData(Digger, 20));
      buttons_data.push_back(ActionData(Miner, 20));
    }

  for(std::vector<ActionData>::size_type i = 0; i < buttons_data.size(); i++)
    {
      a_buttons.push_back(new VerticalActionButton (x_pos, i * 38 + y_pos,
						    buttons_data[i].name,
						    controller->get_owner ()));
    }

  armageddon = new ArmageddonButton(CL_Display::get_width() - 40,     CL_Display::get_height() - 62);
  forward    = new ForwardButton   (CL_Display::get_width() - 40 * 2, CL_Display::get_height() - 62);
  pause      = new PauseButton     (CL_Display::get_width() - 40 * 3, CL_Display::get_height() - 62);

  forward->pressed = false;
  pause->pressed   = false;
    
  
  
  pressed_button = a_buttons.begin();
}

ButtonPanel::~ButtonPanel()
{
  for (AButtonIter it = a_buttons.begin(); it != a_buttons.end(); ++it) 
  {
    delete *it;
  }
  
  delete armageddon;
  delete forward;
  delete pause;
}

void
ButtonPanel::update(float delta)
{
  (*pressed_button)->update(delta);

  if (last_press + 350 < CL_System::get_time()) 
    {
      armageddon_pressed = 0;
    } 
}

ActionName
ButtonPanel::get_action_name()
{
  return (*pressed_button)->get_action_name();
}

void 
ButtonPanel::draw() 
{
  float alpha;

  if (fast_mode)
    alpha = 1.0;
  else 
    alpha = 0.5;
  
  // draw the buttons
  for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); ++button) 
    {
      if (button == pressed_button) 
	(*button)->pressed = true;
      else
	(*button)->pressed = false;

      (*button)->draw();
    }

  armageddon->draw();
  pause->draw();
  forward->draw();
}

void
ButtonPanel::set_server(Server* s)
{
  server = s;

  for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); ++button) 
    {
      (*button)->set_action_holder(server->get_action_holder());
    }

  pause->server = server;
  armageddon->server = server;
  forward->server = server;
}

void
ButtonPanel::set_client(Client* c)
{
  client = c;
}

void
ButtonPanel::set_button(int i)
{
  if ((unsigned int)(i) < a_buttons.size())
    {
      pressed_button = a_buttons.begin() + i;
    }
}

void
ButtonPanel::on_button_press(int x, int y)
{
  for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); button++)
    {
      if ((*button)->mouse_over(controller->get_pos ()))
	pressed_button = button;
    }
  
  if (armageddon->mouse_over(CL_Vector (x, y)))
    {
      last_press = CL_System::get_time();
      
      if (verbose) std::cout << "Armageddon: " << armageddon_pressed << std::endl;
      armageddon_pressed++;
           
      if (armageddon_pressed == 2)
	{
	  arma_counter = 0;
	  armageddon_pressed = 4;
	  armageddon->pressed = true;
	  server->get_world()->armageddon();
	}
      return;
    }
    
  if (pause->mouse_over(controller->get_pos ()))
    {
      client->set_pause(!client->get_pause());
      return;
    }
  else if (forward->mouse_over(controller->get_pos ()))
    {
      client->set_fast_forward(!client->get_fast_forward());
      return;
    }
}

bool
ButtonPanel::is_at (int x, int y)
{
  for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); button++)
    {
      if ((*button)->mouse_over(CL_Vector (x, y)))
	return true;
    }
  return false;
}

void
ButtonPanel::on_button_release(int x, int y)
{

  //forward->pressed = false;
  //pause->pressed = false;
  
}

/// Select the next action
void 
ButtonPanel::next_action ()
{
  ++pressed_button;
  if (pressed_button == a_buttons.end ())
    pressed_button = a_buttons.begin ();
}

/// Select the previous action
void 
ButtonPanel::previous_action ()
{
  if (pressed_button == a_buttons.begin ())
    pressed_button = a_buttons.end ();

  --pressed_button;
}

/* EOF */
