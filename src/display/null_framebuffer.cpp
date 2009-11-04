//  Pingus - A free Lemmings clone
//  Copyright (C) 2008 Ingo Ruhnke <grumbel@gmx.de>
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

#include <iostream>
#include "display/null_framebuffer.hpp"

class NullFramebufferSurfaceImpl : public FramebufferSurfaceImpl
{
private:
  Size size;

public:
  NullFramebufferSurfaceImpl(const Size& size_) : size(size_) {}
  ~NullFramebufferSurfaceImpl() {}

  int get_width()  const { return size.width; }
  int get_height() const { return size.height; }
  Surface to_surface() const { return Surface(); }
};

NullFramebuffer::NullFramebuffer() :
  size()
{
}

NullFramebuffer::~NullFramebuffer()
{
}

FramebufferSurface
NullFramebuffer::create_surface(const Surface& surface)
{
  std::cout << "Creating surface: " << surface.get_size() << std::endl;
  return FramebufferSurface(new NullFramebufferSurfaceImpl(surface.get_size()));
}

void
NullFramebuffer::set_video_mode(const Size& size_, bool fullscreen)
{
  size = size_;
  std::cout << "Size: " << size.width << "x" << size.height << " fullscreen: " << fullscreen << std::endl;
}

void
NullFramebuffer::flip()
{
}

void
NullFramebuffer::push_cliprect(const Rect&)
{
}

void
NullFramebuffer::pop_cliprect()
{
}

void
NullFramebuffer::draw_surface(const FramebufferSurface& src, const Vector2i& pos)
{
}

void
NullFramebuffer::draw_surface(const FramebufferSurface& src, const Rect& srcrect, const Vector2i& pos)
{
}

void
NullFramebuffer::draw_line(const Vector2i& pos1, const Vector2i& pos2, const Color& color)
{
}

void
NullFramebuffer::draw_rect(const Rect& rect, const Color& color)
{
}

void
NullFramebuffer::fill_rect(const Rect& rect, const Color& color)
{
}

Size
NullFramebuffer::get_size() const
{
  return size;
}

/* EOF */
