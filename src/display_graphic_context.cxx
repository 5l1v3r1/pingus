//  $Id: display_graphic_context.cxx,v 1.3 2002/09/05 11:26:35 grumbel Exp $
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

#include <ClanLib/Display/Display/display.h>
#include <ClanLib/Display/Font/font.h>
#include "math.hxx"
#include "sprite.hxx"
#include "display_graphic_context.hxx"

using namespace Pingus;

DisplayGraphicContext::DisplayGraphicContext (int x1, int y1, int x2, int y2, 
					      int /*x_offset*/, int /*y_offset*/)
  : x1 (x1), y1 (y1), x2 (x2), y2 (y2), offset (-(x2 - x1)/2.0f, -(y2-x1)/2.0f, 1.0f)
{
  center = CL_Vector ((x2 - x1)/2.0f + x1,
		      (y2 - y1)/2.0f + y1);
  std::cout << "View: " << x1 << ", " << y1 << ", " << x2 << ", " << y2 
  << std::endl;
}

DisplayGraphicContext::~DisplayGraphicContext ()
{
}

void
DisplayGraphicContext::set_offset (float x, float y)
{
  offset.x = x;
  offset.y = y;
}

CL_Rect
DisplayGraphicContext::get_clip_rect()
{
  assert (!"DisplayGraphicContext::get_clip_rect(): unimplemented");
  return CL_Rect ();
}

CL_Vector
DisplayGraphicContext::get_offset ()
{
  return offset;
}

float
DisplayGraphicContext::get_zoom ()
{
  return offset.z;
}

void
DisplayGraphicContext::set_zoom (float new_zoom)
{
  offset.z = new_zoom;
  //std::cout << "Zoom: " << offset.z << std::endl;
}

void 
DisplayGraphicContext::zoom_to (const CL_Rect & arg_rect)
{
  CL_Rect rect;

  rect.x1 = Math::min (arg_rect.x1, arg_rect.x2);
  rect.x2 = Math::max (arg_rect.x1, arg_rect.x2);
  rect.y1 = Math::min (arg_rect.y1, arg_rect.y2);
  rect.y2 = Math::max (arg_rect.y1, arg_rect.y2);
  
  CL_Vector pos1 = screen_to_world (CL_Vector(rect.x1, rect.y1));
  CL_Vector pos2 = screen_to_world (CL_Vector(rect.x2, rect.y2));

  CL_Vector center = (pos2 + pos1) * 0.5f;
  offset = -center;

  float width  = pos2.x - pos1.x;
  float height = pos2.y - pos1.y;

  if (width < 10 && height < 10)
    return ;

  float screen_relation = get_width () / get_height ();
  float rect_reation = width / height;
  
  if (rect_reation > screen_relation)
    {
      set_zoom (get_width () / (pos2.x - pos1.x));
    }
  else
    {
      set_zoom (get_height () / (pos2.y - pos1.y));
    }
}

int 
DisplayGraphicContext::get_width ()
{
  return x2 - x1;
}

int
DisplayGraphicContext::get_height ()
{
  return y2 - y1;
}

void 
DisplayGraphicContext::move (const CL_Vector & delta)
{
  offset += delta;
}

CL_Vector
DisplayGraphicContext::screen_to_world (CL_Vector pos)
{
  return ((pos - center) * (1.0f/offset.z)) - offset;
}

CL_Vector
DisplayGraphicContext::world_to_screen (CL_Vector pos)
{
  return ((pos + offset) * offset.z) + center;
}

float 
DisplayGraphicContext::get_x_offset ()
{
  return offset.x;
}

float 
DisplayGraphicContext::get_y_offset ()
{
  return offset.y;
}

void 
DisplayGraphicContext::draw (Sprite& sprite, const CL_Vector& pos)
{
  CL_Vector tmp_pos = pos;
  sprite.put_screen (tmp_pos + offset + center);
}

void 
DisplayGraphicContext::draw (Sprite& sprite, const CL_Vector& pos, int frame)
{
  CL_Surface sur (sprite.get_surface ());
  draw (sur, 
	(int) pos.x + sprite.get_x_align (),
	(int) pos.y + sprite.get_y_align (), 
	frame);
}

void 
DisplayGraphicContext::draw (CL_Surface& sur, const CL_Vector& pos)
{
  if (offset.z == 1.0)
    {   
      sur.put_screen (int(pos.x + get_x_offset () + center.x),
		      int(pos.y + get_y_offset () + center.y));
    }
  else
    {
      sur.put_screen (int((pos.x + get_x_offset ()) * offset.z + center.x),
		      int((pos.y + get_y_offset ()) * offset.z + center.y),
		      offset.z, offset.z);
    }
  //CL_Display::draw_line (x1, y1, x2, y2, 1.0, 1.0, 0.0);
  //CL_Display::draw_line (x1, y2, x2, y1, 1.0, 1.0, 0.0);
}

void 
DisplayGraphicContext::draw (CL_Surface& sur, const CL_Vector& pos, int frame)
{
  draw (sur, int(pos.x), int(pos.y), frame);
}

void 
DisplayGraphicContext::draw (CL_Surface& sur, int x_pos, int y_pos)
{
  if (offset.z == 1.0)
    {
      sur.put_screen (int(x_pos + get_x_offset () + center.x),
		      int(y_pos + get_y_offset () + center.y));
    }
  else
    {
      sur.put_screen (int((x_pos + get_x_offset ()) * offset.z + center.x),
		      int((y_pos + get_y_offset ()) * offset.z + center.y),
		      offset.z, offset.z);
    }
}

void 
DisplayGraphicContext::draw (CL_Surface& sur, int x_pos, int y_pos, int frame)
{
  if (offset.z == 1.0)
    {
      sur.put_screen (int(x_pos + get_x_offset () + center.x),
		      int(y_pos + get_y_offset () + center.y),
		      frame);  
    }
  else
    {
      sur.put_screen (int((x_pos + get_x_offset ()) * offset.z + center.x),
		      int((y_pos + get_y_offset ()) * offset.z + center.y),
		      offset.z, offset.z,
		      frame);  
    }
}

void 
DisplayGraphicContext::draw (CL_Surface& sur, int x_pos, int y_pos, 
	    float size_x, float size_y, int frame)
{
  sur.put_screen (int(x_pos + get_x_offset () + center.x),
		  int(y_pos + get_y_offset () + center.y),
		  size_x * offset.z, 
		  size_y * offset.z, frame); 
}

void 
DisplayGraphicContext::draw_line (const CL_Vector& pos1, const CL_Vector& pos2,
		       float r, float g, float b, float a)
{
  draw_line (int(pos1.x), int(pos1.y), int(pos2.x), int(pos2.y), r, g, b, a);
}

void 
DisplayGraphicContext::draw_line (int x1, int y1, int x2, int y2, 
		       float r, float g, float b, float a)
{
  CL_Display::draw_line (int((x1 + get_x_offset ()) * offset.z + center.x),
			 int((y1 + get_y_offset ()) * offset.z + center.y),
			 int((x2 + get_x_offset ()) * offset.z + center.x),
			 int((y2 + get_y_offset ()) * offset.z + center.y),
			 r, g, b, a);
}

void 
DisplayGraphicContext::draw_fillrect (int x1, int y1, int x2, int y2, 
			   float r, float g, float b, float a)
{
  CL_Display::fill_rect (int((x1 + get_x_offset ()) * offset.z + center.x),
			 int((y1 + get_y_offset ()) * offset.z + center.y), 
			 int((x2 + get_x_offset ()) * offset.z + center.x),
			 int((y2 + get_y_offset ()) * offset.z + center.y),
			 r, g, b, a);
}

void 
DisplayGraphicContext::draw_rect (int x1, int y1, int x2, int y2, 
		 float r, float g, float b, float a)
{
  CL_Display::draw_rect (int((x1 + get_x_offset ()) * offset.z + center.x),
			 int((y1 + get_y_offset ()) * offset.z + center.y), 
			 int((x2 + get_x_offset ()) * offset.z + center.x),
			 int((y2 + get_y_offset ()) * offset.z + center.y),
			 r, g, b, a);
}

void 
DisplayGraphicContext::draw_pixel (int /*x_pos*/, int /*y_pos*/, 
		   float /*r*/, float /*g*/, float /*b*/, float /*a*/)
{
  //CL_Display::put_pixel (x1 + get_x_offset (),
  //			 y1 + get_y_offset (), r, g, b, a);
  std::cout << "View::draw_pixel () not implemented" << std::endl;
}

void 
DisplayGraphicContext::draw_circle (int x_pos, int y_pos, int radius,
				    float r, float g, float b, float a)
{
  // FIXME: Probally not the fast circle draw algo on this world...
  const float pi = 3.1415927f * 2.0f;
  const float steps = 8;
  CL_Vector current (radius, 0);
  CL_Vector next = current.rotate (pi/steps, CL_Vector (0, 0, 1.0f));

  for (int i = 0; i < steps; ++i)
    {
      draw_line (int(x_pos + current.x), int(y_pos + current.y),
		 int(x_pos + next.x), int(y_pos + next.y),
		 r, g, b, a);
      current = next;
      next = next.rotate (pi/8, CL_Vector (0, 0, 1.0f));
    }
}

void
DisplayGraphicContext::print_left (FontHandle font, int x_pos, int y_pos, const std::string& str)
{
  font->print_left(int(x_pos + get_x_offset () + center.x),
		   int(y_pos + get_y_offset () + center.y),
		   str.c_str ());
}

void
DisplayGraphicContext::print_center (FontHandle font, int x_pos, int y_pos, const std::string& str)
{
  font->print_center(int(x_pos + get_x_offset () + center.x),
		     int(y_pos + get_y_offset () + center.y),
		     str.c_str ());  
}
  
void
DisplayGraphicContext::print_right (FontHandle font, int x_pos, int y_pos, const std::string& str)
{
  font->print_right(int(x_pos + get_x_offset () + center.x),
		    int(y_pos + get_y_offset () + center.y),
		    str.c_str ());
}

/* EOF */
