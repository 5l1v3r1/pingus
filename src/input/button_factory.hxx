//  $Id: button_factory.hxx,v 1.2 2002/07/09 17:00:10 torangan Exp $
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

#ifndef HEADER_PINGUS_INPUT_BUTTON_FACTORY_HXX
#define HEADER_PINGUS_INPUT_BUTTON_FACTORY_HXX

#include "../libxmlfwd.hxx"

namespace Input {

  class Button;

  class ButtonFactory 
  {
    private:
      static inline Button* joystick_button (xmlNodePtr cur);
      static inline Button* key_button      (xmlNodePtr cur);
      static inline Button* mouse_button    (xmlNodePtr cur);
      static inline Button* multiple_button (xmlNodePtr cur);
    
    public:
      static Button* create (xmlNodePtr cur);
  };
}

#endif

/* EOF */
