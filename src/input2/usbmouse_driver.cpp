/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
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

#include <stdexcept>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

#include "math/vector2i.hpp"
#include "usbmouse_driver.hpp"

namespace Input {

class USBMouse
{
private:
  int fd;
  Vector2i mouse_pos;

  std::string device;
  std::vector<bool> buttons;
  std::vector<Pointer*> pointer;
  
public: 
  USBMouse(const std::string& device_) 
    : device(device_),
      buttons(5)
  {
    fd = open(device.c_str (), O_RDWR | O_NONBLOCK);

    if (fd == -1)
      {
        throw std::runtime_error(strerror(errno));
      }

    {
      // Microsoft init sequence for Explorer mouse (wheel + 5 buttons)
      static unsigned char data[] = { 0xF3, 0xC8, 
                                      0xF3, 0xC8,
                                      0xF3, 0x50 };
      write(fd, data, sizeof(data));
    }

    char data[4];
    read(fd, data, sizeof (data));
    read(fd, data, sizeof (data));
    read(fd, data, sizeof (data));
  }

  ~USBMouse()
  {
    close(fd);
  }

  void add_listener(Pointer* p)
  {
    pointer.push_back(p);
  }

  std::string get_device() const { 
    return device; 
  }

  void update(float delta)
  {
    unsigned char data[4];
    while(read(fd, data, sizeof (data)) > 0)
      {		
        // Mouse Move:
        int delta_x = (data[0] & 0x10) ? data[1]-256 : data[1];
        int delta_y = (data[0] & 0x20) ? data[2]-256 : data[2];

        if (delta_x != 0 || delta_y != 0)
          {
            mouse_pos.x += delta_x;
            mouse_pos.y -= delta_y; // y-axis is reversed on-screen

            if (mouse_pos.x < 0) 
              mouse_pos.x = 0;
            else if (mouse_pos.x > 800) // FIXME: Shouldn't hardcore 800x600 resolution
              mouse_pos.x = 800 - 1;

            if (mouse_pos.y < 0) 
              mouse_pos.y = 0;
            else if (mouse_pos.y > 600)
              mouse_pos.y = 600 - 1;

            for(std::vector<Pointer*>::iterator i = pointer.begin(); i != pointer.end(); ++i)
              (*i)->set_pos(mouse_pos);

            // send_ball_move(delta_x, delta_y);
            // send_pointer_move(mouse_pos);
          }

        // Scrollwheel move
        int delta_z = (data[3] & 0x08) ? (data[3] & 0x0F)-16 : (data[3] & 0x0F);

        if (delta_z > 0)
          {
            while (delta_z != 0)
              {
                --delta_z;
                //send_key_event(CL_MOUSE_WHEEL_DOWN, true);
                //send_key_event(CL_MOUSE_WHEEL_DOWN, false);
              }
          } 
        else if (delta_z < 0)
          {
            while (delta_z != 0)
              {
                ++delta_z;
                //send_key_event(CL_MOUSE_WHEEL_UP, true);
                //send_key_event(CL_MOUSE_WHEEL_UP, false);
              }
          }

        // Button event
        std::vector<bool> new_state(5);

        new_state[0] = ((data[0] &  1)>0);
        new_state[1] = ((data[0] &  2)>0);
        new_state[2] = ((data[0] &  4)>0);
        new_state[3] = ((data[3] & 16)>0);
        new_state[4] = ((data[3] & 32)>0);

        for (int i = 0; i < 5; ++i)
          {
            if (new_state[i] != buttons[i])
              {
                buttons[i] = new_state[i];
              }
          }

        buttons = new_state;
      }
  }
};

USBMouseDriver::USBMouseDriver()
{
}

USBMouseDriver::~USBMouseDriver()
{
  for(USBMice::iterator i = usbmice.begin(); i != usbmice.end(); ++i)
    delete *i;
}

void
USBMouseDriver::update(float delta)
{
  for(USBMice::iterator i = usbmice.begin(); i != usbmice.end(); ++i)
    (*i)->update(delta);
}

Button*
USBMouseDriver::create_button(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "usbmouse:button")
    {
      return 0;
    }
  else
    {
      return 0;
    }
}

Pointer*
USBMouseDriver::create_pointer(const FileReader& reader, Control* parent)
{
  if (reader.get_name() == "usbmouse:pointer")
    {
      std::string device;
      if (reader.read_string("device", device))
        {
          USBMouse* mouse = get_mouse(device);
          if (mouse)
            {
              Pointer* pointer = new Pointer(parent);
              mouse->add_listener(pointer);
              return pointer;
            }
          else
            {
              return 0;
            }
        }
      else
        {
          std::cout << "USBMouseDriver: 'device' entry is missing" << std::endl;
          return 0;
        }
    }
  else
    {
      return 0;
    }
}

USBMouse*
USBMouseDriver::get_mouse(const std::string& device)
{
  for(USBMice::iterator i = usbmice.begin(); i != usbmice.end(); ++i)
    {
      if ((*i)->get_device() == device)
        return *i;
    }

  try 
    {
      USBMouse* usbmouse = new USBMouse(device);
      usbmice.push_back(usbmouse);
      return usbmouse;
    }
  catch (std::exception& err) 
    {
      std::cout << "USBMouseDriver: " << err.what() << std::endl;
      return 0;
    }
}

} // namespace Input

/* EOF */
