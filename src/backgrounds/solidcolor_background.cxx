//  $Id: solidcolor_background.cxx,v 1.5 2002/09/10 21:03:32 torangan Exp $
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

#include <fstream>
#include <ClanLib/Display/Display/display.h>
#include "solidcolor_background.hxx"
#include "../xml_helper.hxx"

void
SolidColorBackgroundData:: write_xml(std::ostream& xml)
{
  xml << "<worldobj type=\"solidcolor-background\"></worldobj>" << std::endl;
}

SolidColorBackgroundData::SolidColorBackgroundData(xmlDocPtr doc, xmlNodePtr cur)
{
  cur = cur->children;
  while (cur)
    {
      if (xmlIsBlankNode(cur)) 
	{
	  cur = cur->next;
	  continue;
	}

      if (XMLhelper::equal_str(cur->name, "color"))
	{
	  color = XMLhelper::parse_color (doc, cur);
	}
      else
	{
	  std::cout << "SolidColorBackground: Unhandled tag: " << cur->name << std::endl;
	}
      cur = cur->next;
    }
}

SolidColorBackgroundData::SolidColorBackgroundData (const SolidColorBackgroundData& old)
                                                   : WorldObjData(old),
						     color(old.color)
{
}

SolidColorBackgroundData
SolidColorBackgroundData::operator= (const SolidColorBackgroundData& old)
{
  if (this == &old)
    return *this;
    
  WorldObjData::operator=(old);
  
  color = old.color;
  
  return *this;
}

WorldObj* 
SolidColorBackgroundData::create_WorldObj()
{
  return new SolidColorBackground (*this);
}

EditorObjLst 
SolidColorBackgroundData::create_EditorObj()
{
  EditorObjLst lst;
  lst.push_back (new EditorSolidColorBackground (*this));
  return lst;
}

SolidColorBackground::SolidColorBackground (const SolidColorBackgroundData& data)
  : SolidColorBackgroundData (data)
{
}

void
SolidColorBackground::draw_offset (int /*x_of*/, int /*y_of*/, float /*s*/)
{
  // FIXME: Probally fill_rect is better here, but slower?
  CL_Display::clear_display (color.red, color.green, color.blue, color.alpha);
}

/* EOF */


