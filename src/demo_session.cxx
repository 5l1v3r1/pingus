//  $Id: demo_session.cxx,v 1.10 2003/10/18 23:17:27 grumbel Exp $
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

#include <ClanLib/Display/Input/input.h>
#include <ClanLib/Display/Input/keyboard.h>
#include "math.hxx"
#include "xml_pdf.hxx"
#include "true_server.hxx"
#include "world.hxx"
#include "demo_player.hxx"
#include "pingus_counter.hxx"
#include "gui/gui_manager.hxx"
#include "gui/graphic_context.hxx"
#include "demo_session.hxx"

namespace Pingus {

DemoSession::DemoSession(const std::string& filename)
{
  // Load Demo file
  pdf    = new XMLPDF(filename);

  // Create server
  server      = new TrueServer(pdf->get_plf());
  demo_player = new DemoPlayer(server, pdf);

  // Create GUI
  pcounter = new PingusCounter(server);
  gui_manager->add (pcounter, true);
}

DemoSession::~DemoSession()
{
  delete server;
  delete pdf;
}

/** Draw this screen */
void
DemoSession::draw_background(GraphicContext& gc)
{
  World* world = server->get_world();

  if (CL_Keyboard::get_keycode(CL_KEY_LEFT))
    gc.move(Vector(10.0, 0.0));

  if(CL_Keyboard::get_keycode(CL_KEY_RIGHT))
    gc.move(Vector(-10.0, 0.0));

  if(CL_Keyboard::get_keycode(CL_KEY_UP))
    gc.move(Vector(0.0, 10.0));

  if(CL_Keyboard::get_keycode(CL_KEY_DOWN))
    gc.move(Vector(0.0, -10.0));

  float x_of = -gc.get_x_offset();
  float y_of = -gc.get_y_offset();

  x_of = Math::mid(gc.get_width()/2.0f,
                   x_of,
                   world->get_width() - 1 - gc.get_width()/2.0f);

  y_of = Math::mid(gc.get_height()/2.0f,
                   y_of,
                   world->get_height() - 1 - gc.get_height()/2.0f);

  gc.set_offset(-x_of, -y_of);


  world->draw(gc);
  while (CL_Keyboard::get_keycode(CL_KEY_D))
    {
      server->get_world()->draw(gc);
      CL_System::keep_alive();
    }
}

/** Pass a delta to the screen */
void
DemoSession::update(float delta)
{
  UNUSED_ARG(delta);

  // FIXME: Duplicate all timing code here?!
  server->update();
  demo_player->update();

  int skip_count = 0;
  while (CL_Keyboard::get_keycode(CL_KEY_SPACE) && skip_count < 10)
    {
      ++skip_count;
      server->update();
      demo_player->update();
    }
}

} // namespace Pingus

/* EOF */
