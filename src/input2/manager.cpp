/*  $Id$
**
**  Pingus - A free Lemmings clone
**  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include "string_util.hpp"
#include "pingus_error.hpp"
#include "path_manager.hpp"
#include "sdl_driver.hpp"
#include "core_driver.hpp"
#include "manager.hpp"

namespace Input {

Manager::Manager()
{
  desc.add_axis("test-axis",  TEST_AXIS);

  desc.add_pointer("standard-pointer",   STANDARD_POINTER);
  desc.add_scroller("standard-scroller", STANDARD_SCROLLER);

  desc.add_button("primary-button",      PRIMARY_BUTTON);
  desc.add_button("secondary-button",    SECONDARY_BUTTON);
  desc.add_button("fast-forward-button", FAST_FORWARD_BUTTON);
  desc.add_button("armageddon-button",   ARMAGEDDON_BUTTON);
  desc.add_button("pause-button",        PAUSE_BUTTON);
  desc.add_button("escape-button",       ESCAPE_BUTTON);
  desc.add_button("action-up-button",    ACTION_UP_BUTTON);
  desc.add_button("action-down-button",  ACTION_DOWN_BUTTON);
  desc.add_button("action-1-button",     ACTION_1_BUTTON);
  desc.add_button("action-2-button",     ACTION_2_BUTTON);
  desc.add_button("action-3-button",     ACTION_3_BUTTON);
  desc.add_button("action-4-button",     ACTION_4_BUTTON);
  desc.add_button("action-5-button",     ACTION_5_BUTTON);
  desc.add_button("action-6-button",     ACTION_6_BUTTON);
  desc.add_button("action-7-button",     ACTION_7_BUTTON);
  desc.add_button("action-8-button",     ACTION_8_BUTTON);
  desc.add_button("action-9-button",     ACTION_9_BUTTON);
  desc.add_button("action-10-button",    ACTION_10_BUTTON);
}

std::string get_non_driver_part(const std::string& fullname)
{
  std::string::size_type i = fullname.find_first_of(':');
  if (i != std::string::npos)
    {
      return fullname.substr(i+1);
    }
  else
    {
      return fullname;
    }
}

std::string get_driver_part(const std::string& fullname)
{
  std::string::size_type i = fullname.find_first_of(':');
  if (i != std::string::npos)
    {
      return fullname.substr(0, i);
    }
  else
    {
      return "core";
    }
}

void
Manager::load(const std::string& filename)
{
  controller.load(desc);

  FileReader reader = FileReader::parse(filename);

  if (reader.get_name() != "pingus-controller")
    {
      PingusError::raise("Controller: invalid config file '" + filename + "'");
    }
  else
    {
      const std::vector<FileReader>& sections = reader.get_sections();
      for (std::vector<FileReader>::const_iterator i = sections.begin();
           i != sections.end(); ++i)
        {
          if (StringUtil::has_suffix(i->get_name(), "pointer"))
            {
              const std::vector<FileReader>& pointers = i->get_sections();
              for(std::vector<FileReader>::const_iterator j = pointers.begin(); j != pointers.end(); ++j)
                {
                  int id = desc.get_definition(i->get_name()).id;
                  ControllerPointer* ctrl_pointer = controller.get_pointer(id);
                  Pointer* pointer = create_pointer(*j, ctrl_pointer);
                  if (pointer)
                    ctrl_pointer->add_pointer(pointer);
                  else
                    std::cout << "Manager: pointer: Couldn't create pointer" << j->get_name() << std::endl;
                }

            }
          else if (StringUtil::has_suffix(i->get_name(), "scroller"))
            {
              const std::vector<FileReader>& scrollers = i->get_sections();
              for(std::vector<FileReader>::const_iterator j = scrollers.begin(); j != scrollers.end(); ++j)
                {
                  int id = desc.get_definition(i->get_name()).id;
                  ControllerScroller* ctrl_scroller = controller.get_scroller(id);
                  Scroller* scroller = create_scroller(*j, ctrl_scroller);
                  if (scroller)
                    ctrl_scroller->add_scroller(scroller);
                  else
                    std::cout << "Manager: scroller: Couldn't create scroller" << j->get_name() << std::endl;
                }

            }
          else if (StringUtil::has_suffix(i->get_name(), "button"))
            {             
              const std::vector<FileReader>& buttons = i->get_sections();
              for(std::vector<FileReader>::const_iterator j = buttons.begin(); j != buttons.end(); ++j)
                {
                  int id = desc.get_definition(i->get_name()).id;
                  ControllerButton* ctrl_button = controller.get_button(id);
                  Button* button = create_button(*j, ctrl_button);
                  if (button)
                    ctrl_button->add_button(button);
                  else
                    std::cout << "Manager: button: Couldn't create button" << j->get_name() << std::endl;
                }
            }
          else if (StringUtil::has_suffix(i->get_name(), "axis"))
            {
              const std::vector<FileReader>& axes = i->get_sections();
              for(std::vector<FileReader>::const_iterator j = axes.begin(); j != axes.end(); ++j)
                {
                  int id = desc.get_definition(i->get_name()).id;
                  ControllerAxis* ctrl_axis = controller.get_axis(id);
                  Axis* axis = create_axis(*j, ctrl_axis);
                  if (axis)
                    ctrl_axis->add_axis(axis);
                  else
                    std::cout << "Manager: axis: Couldn't create axis" << j->get_name() << std::endl;
                }
            } 
          else
            {
              PingusError::raise(std::string("Manager: Unkown Element in Controller Config: ") 
                                 + i->get_name());
            }
        }
    }
}

void
Manager::update(float delta)
{
  for(Drivers::iterator i = drivers.begin(); i != drivers.end(); ++i)
    {
      (*i)->update(delta);
    }
}

Driver*
Manager::get_driver(const std::string& name)
{
  for(Drivers::iterator i = drivers.begin(); i != drivers.end(); ++i)
    {
      if ((*i)->get_name() == name)
        {
          return *i;
        }
    }
  return 0;
}

Driver*
Manager::load_driver(const std::string& name)
{
  Driver* driver = get_driver(name);

  if (driver)
    {
      return driver;
    }
  else
    {
      std::cout << "Manager: Loading driver '" << name << "'" << std::endl;

      if (name == "sdl") {
        driver = new SDLDriver();
      } else if (name == "core") {
        driver = new CoreDriver();
      } else {
        std::cout << "Manager: Unknown driver: " << name << std::endl;
        return 0;
      }

      drivers.push_back(driver);
      return driver;
    }
}

Button*
Manager::create_button(const FileReader& reader, Button* parent)
{
  std::string driver = get_driver_part(reader.get_name());
                  
  Driver* drv = load_driver(driver);
  if (drv)
    {
      return drv->create_button(reader, parent);
    }
  else
    {
      std::cout << "Manager: Error: Couldn't find driver: '" << driver << "'" << std::endl;
      return 0;
    }
}

Axis*
Manager::create_axis(const FileReader& reader, Axis* parent)
{
  std::string driver = get_driver_part(reader.get_name());
                  
  Driver* drv = load_driver(driver);
  if (drv)
    {
      return drv->create_axis(reader, parent);
    }
  else
    {
      std::cout << "Manager: Error: Couldn't find driver: '" << driver << "'" << std::endl;
      return 0;
    }
}

Pointer*
Manager::create_pointer(const FileReader& reader, Pointer* parent)
{
  std::string driver = get_driver_part(reader.get_name());
                  
  Driver* drv = load_driver(driver);
  if (drv)
    {
      return drv->create_pointer(reader, parent);
    }
  else
    {
      std::cout << "Manager: Error: Couldn't find driver: '" << driver << "'" << std::endl;
      return 0;
    }
}

Scroller*
Manager::create_scroller(const FileReader& reader, Scroller* parent)
{
  std::string driver = get_driver_part(reader.get_name());
                  
  Driver* drv = load_driver(driver);
  if (drv)
    {
      return drv->create_scroller(reader, parent);
    }
  else
    {
      std::cout << "Manager: Error: Couldn't find driver: '" << driver << "'" << std::endl;
      return 0;
    }
}

} // namespace Input

/* EOF */
