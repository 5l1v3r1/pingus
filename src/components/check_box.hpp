//  $Id: check_box.hpp 3505 2007-11-09 10:57:45Z grumbel $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_CHECK_BOX_HPP
#define HEADER_CHECK_BOX_HPP

#include <boost/signal.hpp>
#include <string>
#include "gui/rect_component.hpp"

/** */
class CheckBox : public GUI::RectComponent
{
private:
  bool state;

public:
  CheckBox(const Rect& rect);

  void draw(DrawingContext& gc);
  void on_primary_button_press(int x, int y);
  void update_layout() {}

  void set_state(bool v, bool send_signal);

  boost::signal<void (bool)> on_change;

private:
  CheckBox (const CheckBox&);
  CheckBox& operator= (const CheckBox&);
};

#endif

/* EOF */
