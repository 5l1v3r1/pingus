//  $Id: level_property_window.hxx,v 1.2 2002/07/01 12:46:22 grumbel Exp $
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

#ifndef HEADER_PINGUS_LEVEL_PROPERTY_WINDOW_HXX
#define HEADER_PINGUS_LEVEL_PROPERTY_WINDOW_HXX

#include <ClanLib/gui.h>

class ObjectManager;

namespace Pingus
{
  namespace Editor
  {
    class LevelPropertyWindow : public CL_Window
    {
    private:
      CL_Label    levelname_label;
      CL_InputBox levelname_input;

      CL_Label    descritpion_label;
      //CL_InputBox description_input;

      CL_Label    author_label;
      CL_InputBox author_input;

      CL_Label    number_of_pingus_label;
      CL_InputBox number_of_pingus_input;

      CL_Label    pingus_to_save_label;
      CL_InputBox pingus_to_save_input;

      CL_Label    time_label;
      CL_InputBox time_input;
    public:
      LevelPropertyWindow (CL_Component* parent, ObjectManager*);
      ~LevelPropertyWindow ();
    };
  }
}

#endif

/* EOF */
