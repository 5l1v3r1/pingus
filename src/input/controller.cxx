//  $Id: controller.cxx,v 1.15 2002/08/16 18:13:36 torangan Exp $
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

#include "../xml_helper.hxx"
#include "../pingus_error.hxx"
#include "axis.hxx"
#include "axis_event.hxx"
#include "axis_factory.hxx"
#include "button.hxx"
#include "button_factory.hxx"
#include "controller.hxx"
#include "dummy_axis.hxx"
#include "dummy_button.hxx"
#include "dummy_pointer.hxx"
#include "dummy_scroller.hxx"
#include "pointer.hxx"
#include "pointer_event.hxx"
#include "pointer_factory.hxx"
#include "scroller.hxx"
#include "scroller_factory.hxx"
#include "scroll_event.hxx"

namespace Input
{
  Controller::Controller (const std::string& configfile) : action_axis(0),
                                                           standard_pointer(0), 
							   scroller(0),
							   std_pointer_x(0),
							   std_pointer_y(0)
  {

    xmlDocPtr doc = xmlParseFile(configfile.c_str());
    
    if (!doc)
      PingusError::raise("Controller: config file <" + configfile + "> not found");
      
    xmlNodePtr cur = doc->ROOT;
    
    if (!cur || strcmp(reinterpret_cast<const char*>(cur->name), "pingus-controller") != 0)
      PingusError::raise("Controller: invalid config file <" + configfile + ">");
    cur = XMLhelper::skip_blank(cur->children);

    if (!cur || strcmp(reinterpret_cast<const char*>(cur->name), "controller-config") != 0)
      PingusError::raise("Controller: invalid config file <" + configfile + ">");
    cur = XMLhelper::skip_blank(cur->children);
	       
    while (cur) 
      {
        if (xmlIsBlankNode(cur)) // explicit check cause we need the continue to check for cur again
	  {
            cur = cur->next;
	    continue;
	  }

	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "standard-pointer"))
          standard_pointer = PointerFactory::create(XMLhelper::skip_blank(cur->children));
	  
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "scroller"))
	  scroller = ScrollerFactory::create(XMLhelper::skip_blank(cur->children));
	  
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "primary-button"))
	  buttons.push_back(ButtonEntry(primary, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	  
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "secondary-button"))
	  buttons.push_back(ButtonEntry(secondary, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	  
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "pause-button"))
	  buttons.push_back(ButtonEntry(pause, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));

	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "fast-forward-button"))
	  buttons.push_back(ButtonEntry(fast_forward, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "armageddon-button"))
	  buttons.push_back(ButtonEntry(armageddon, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "escape-button"))
	  buttons.push_back(ButtonEntry(escape, ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "action-buttons"))
	  create_action_buttons(XMLhelper::skip_blank(cur->children));
	
	else if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "action-axis"))
	  action_axis = AxisFactory::create(XMLhelper::skip_blank(cur->children));
	  
	else
	  PingusError::raise(std::string("Unkown Element in Controller Config: ") + ((cur->name) ? reinterpret_cast<const char*>(cur->name) : ""));
	  
	cur = cur->next;
      }

    if (!standard_pointer)
      standard_pointer = new DummyPointer;
    else
      {
        std_pointer_x = standard_pointer->get_x_pos();
	std_pointer_y = standard_pointer->get_y_pos();
      }

    if (!scroller)
      scroller = new DummyScroller;
      
    if (!action_axis)
      action_axis = new DummyAxis;
      
    if (!find_button(primary))
      buttons.push_back(ButtonEntry(primary, new DummyButton));
      
    if (!find_button(secondary))
      buttons.push_back(ButtonEntry(secondary, new DummyButton));

    if (!find_button(pause))
      buttons.push_back(ButtonEntry(pause, new DummyButton));

    if (!find_button(fast_forward))
      buttons.push_back(ButtonEntry(fast_forward, new DummyButton));
      
    if (!find_button(armageddon))
      buttons.push_back(ButtonEntry(armageddon, new DummyButton));

    if (!find_button(escape))
      buttons.push_back(ButtonEntry(escape, new DummyButton));

    button_states.resize(buttons.size());
    for (unsigned int i=0; i < buttons.size(); i++)
      button_states[i] = buttons[i].second->is_pressed();
  }

  void
  Controller::create_action_buttons (xmlNodePtr cur)
  {
    int count = 0;
    
    while (cur)
      {
        if (xmlIsBlankNode(cur))
	  {
	    cur = cur->next;
	    continue;
	  }
	  
	if ( ! strcmp(reinterpret_cast<const char*>(cur->name), "action-button"))
	  buttons.push_back(ButtonEntry(static_cast<ButtonName>(action_1 + count),
	                                ButtonFactory::create(XMLhelper::skip_blank(cur->children))));
	else
	  PingusError::raise(std::string("Wrong Element in Controller Config (action-buttons): ") + reinterpret_cast<const char*>(cur->name));
	
	cur = cur->next;
	count++;
      }
  }

  void
  Controller::update (float delta)
  {
    for (std::list<Event*>::iterator it = events.begin(); it != events.end(); ++it)
      delete *it;

    events.clear ();

    scroller        ->update(delta);
    standard_pointer->update(delta);
    action_axis     ->update(delta);

    for (unsigned int i=0; i < buttons.size(); i++)
      buttons[i].second->update(delta);
	    
    if (std_pointer_x != standard_pointer->get_x_pos() || std_pointer_y != standard_pointer->get_y_pos())
      {
	std_pointer_x = standard_pointer->get_x_pos();
	std_pointer_y = standard_pointer->get_y_pos();
	
        events.push_back(new PointerEvent(standard, std_pointer_x, std_pointer_y));
      }
      
    if (scroller->get_x_delta() || scroller->get_y_delta())
      events.push_back(new ScrollEvent(scroller->get_x_delta(), scroller->get_y_delta()));
    
    for (unsigned int i=0; i < buttons.size(); i++)
      if (buttons[i].second->is_pressed() != button_states[i])
        {
	  button_states[i] = buttons[i].second->is_pressed();
	  if (button_states[i])
  	    events.push_back(new ButtonEvent(buttons[i].first, pressed));
	  else
	    events.push_back(new ButtonEvent(buttons[i].first, released));
	}
    
    const float& temp = action_axis->get_pos();
    if (temp)
      events.push_back(new AxisEvent(temp));
  }

  const Button*
  Controller::get_button (ButtonName name) const
  {
    const Button* const & temp = find_button(name);
    if (temp)
      return temp;
      
    PingusError::raise("Invalid Button requested");
    
    return 0; // never reached
  }

  const Button*
  Controller::find_button (ButtonName name) const
  {
    for (unsigned int i=0; i < buttons.size(); ++i)
      if (buttons[i].first == name)
        return buttons[i].second;

    return 0;  
  }
}

/* EOF */
