//  $Id: joystick_axis.cxx,v 1.6 2003/10/21 11:01:52 grumbel Exp $
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

//#include <ClanLib/Display/input.h>
#include <ClanLib/Display/input_device.h>
//#include <ClanLib/Display/inputaxis.h>
#include "joystick_axis.hxx"
#include "../../pingus_error.hxx"

namespace Pingus {
namespace Input {
namespace Axes {

JoystickAxis::JoystickAxis(int id_, int axis_, float angle_) 
  : id(id_), axis(axis_), pos(0), angle(angle_)
{
#ifdef CLANLIB_0_6
  if (static_cast<unsigned int> (id) >= CL_Input::joysticks.size())
    PingusError::raise("JoystickAxis: Invalid joystick id");

  if (axis > CL_Input::joysticks[id]->get_num_axes())
    PingusError::raise("JoystickAxis: Invalid joystick axis id");

  if (angle < 0)
    angle = (static_cast<int>(angle) % 360) + 360;
  else if (angle > 360)
    angle = static_cast<int>(angle) % 360;
#endif
}

const float&
JoystickAxis::get_pos () const
{
  return pos;
}

const float&
JoystickAxis::get_angle () const
{
  return angle;
}

void
JoystickAxis::update (float)
{
#ifdef CLANLIB_0_6
  pos = CL_Input::joysticks[id]->get_axis(axis)->get_pos();
#endif
}

} // namespace Axes
} // namespace Input
} // namespace Pingus

/* EOF */
