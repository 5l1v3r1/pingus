//  $Id: ButtonPanel.cc,v 1.1 2000/02/04 23:45:18 mbn Exp $
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

#include "PingusSound.hh"
#include "PingusResource.hh"
#include "globals.hh"
#include "Pingu.hh"
#include "ButtonPanel.hh"

CL_Surface* ButtonPanel::button_cap;

ButtonPanel::ButtonPanel(PLF* plf)
{
  last_press = 0;

  vector<button_data> buttons_data = plf->get_buttons();

  for(vector<button_data>::size_type i = 0; i < buttons_data.size(); i++)
    {
      if (horizontal_button_panel) 
	{
	  a_buttons.push_back(new HorizontalActionButton(38 * i,
							 CL_Display::get_height() - 56,
							 buttons_data[i].name));
	}
      else
	{
	  a_buttons.push_back(new VerticalActionButton(2,
						       i * 38 + 30,
						       buttons_data[i].name));
	}
    }

  armageddon = new ArmageddonButton(CL_Display::get_width() - 38, CL_Display::get_height() - 56);
  forward    = new ForwardButton(CL_Display::get_width() - 38 * 2, CL_Display::get_height() - 56);
  pause      = new PauseButton(CL_Display::get_width() - 38 * 3, CL_Display::get_height() - 56);

  /*  forward->pressed = false;
  pause->pressed   = false;
  armageddon_pressed = false;
  */
  left_pressed = 0;
  
  pressed_button = *a_buttons.begin();
}

ButtonPanel::~ButtonPanel()
{
  delete armageddon;
  delete forward;
  delete pause;
}

void
ButtonPanel::let_move()
{
  pressed_button->let_move();
  /*  
  if (CL_Keyboard::get_keycode(CL_KEY_SPACE))
    {
      forward->pressed = !forward->pressed;
      client->set_fast_forward(forward->pressed);
      while(CL_Keyboard::get_keycode(CL_KEY_SPACE))
	CL_System::keep_alive();
    }
*/
  if (CL_Mouse::left_pressed()) 
    {
      last_press = CL_System::get_time();
    
      for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); button++)
	{
	  if ((*button)->mouse_over()) {
	    pressed_button = *button;
	  }
	}

      if (armageddon->mouse_over()) 
	{
	  if (armageddon_pressed == 0) 
	    {
	      //armageddon_pressed = 1;
	      //armageddon->pressed = true;
	    } 
	  else if (armageddon_pressed == 2) 
	    {
	      armageddon_pressed = 3;
	    }

	  if (armageddon_pressed == 3)
	    {
	      arma_counter = 0;
	      armageddon_pressed = 4;
	      world->armageddon();
	    }
	}
    
      if (pause->mouse_over() && !left_pressed) 
	{
	  //pause->pressed = !pause->pressed;
	  //server->set_pause(pause->pressed);
	}
    
      if (forward->mouse_over() && !left_pressed)
	{
	  client->set_fast_forward(!client->get_fast_forward());
	}
    
      left_pressed = true;
    }
  else 
    {
      left_pressed = false;
    }

  if (armageddon_pressed <= 2) 
    {
      if (last_press + 350 < CL_System::get_time()) 
	{
	  armageddon_pressed = 0;
	} 
      else if (armageddon_pressed == 1) 
	{
	  armageddon_pressed = 2;
	}
    }
}

string
ButtonPanel::get_action_name()
{
  return pressed_button->get_action_name();
}

void 
ButtonPanel::draw() 
{
  float alpha;

  if (fast_mode)
    {
      alpha = 1.0;
    } 
  else 
    {
      alpha = 0.5;
    }
  
  /*  CL_Display::fill_rect(0, CL_Display::get_height() - 56,
			640, CL_Display::get_height(),
			0.0, 0.0, 0.0, 1.0);
  */

  // draw the buttons
  for(AButtonIter button = a_buttons.begin(); button != a_buttons.end(); ++button) 
    {
      if (*button == pressed_button) 
	{
	  (*button)->pressed = true;
	} 
      else
	{
	  (*button)->pressed = false;
	}
      (*button)->draw();
    }
  
  //FIXME
  armageddon->draw();
  pause->draw();
  forward->draw();
}

void
ButtonPanel::set_server(Server* s)
{
  server = s;
  world = server->get_world();

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
      pressed_button = a_buttons[i];
    }
}

/* EOF */
