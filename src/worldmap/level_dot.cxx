//  $Id: level_dot.cxx,v 1.6 2002/11/27 20:05:42 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include "../xml_helper.hxx"
#include "../pingus_resource.hxx"
#include "../graphic_context.hxx"
#include "../plf.hxx"
#include "../path_manager.hxx"
#include "../screen_manager.hxx"
#include "../game_session.hxx"
#include "level_dot.hxx"

namespace WorldMapNS {

LevelDot::LevelDot(xmlDocPtr doc, xmlNodePtr cur)
  : Dot(doc, XMLhelper::skip_blank(cur->children)),
    green_dot_sur("misc/dot_green", "core"),
    red_dot_sur("misc/dot_red", "core"),
    plf(0)
{
  green_dot_sur.set_align_center();
  red_dot_sur.set_align_center();

  cur = cur->children;
  // Skip dot entry
  cur = cur->next;
  cur = XMLhelper::skip_blank(cur);

  cur = cur->next;
  cur = XMLhelper::skip_blank(cur);


  while(cur)
    {
      if (XMLhelper::equal_str(cur->name, "levelname"))
        {
          levelname = XMLhelper::parse_string(doc, cur);
          std::cout << "Levelname: " << levelname << std::endl;         
          plf = PLF::create(path_manager.complete("levels/") + levelname);
        }
      else
        {
          std::cout << "92834Unknown: " << cur->name  << std::endl;
        }
      
      cur = cur->next;
      cur = XMLhelper::skip_blank(cur);
    }
}

void
LevelDot::draw(GraphicContext& gc)
{
  //std::cout << "Drawing level dat: " << pos << std::endl;
  gc.draw (green_dot_sur, pos);
}

void
LevelDot::update()
{
}

void
LevelDot::on_click()
{
  std::cout << "Starting level: " << levelname << std::endl;
  ScreenManager::instance()->fade_out();
  ScreenManager::instance()->push_screen(new PingusGameSession (path_manager.complete("levels/") + levelname),
                                         true);
}

} // namespace WorldMapNS

/* EOF */
