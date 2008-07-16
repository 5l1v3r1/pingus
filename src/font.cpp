//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "font.hpp"
#include "surface.hpp"
#include "line_iterator.hpp"
#include "font_description.hpp"
#include "display/framebuffer.hpp"
#include "display/display.hpp"

static bool vline_empty(SDL_Surface* surface, int x, Uint8 threshold)
{
  if (x >= surface->w)
    return true;

  Uint8* pixels = (Uint8*)surface->pixels;

  for(int y = 0; y < surface->h; ++y)
    {
      const Uint8& p = pixels[surface->pitch*y + x*surface->format->BytesPerPixel + 3];
      if (p > threshold)
        {
          return false;
        }
    }
  return true;
}

class FontImpl
{
public:
  FramebufferSurface framebuffer_surface;
  Rect chrs[256];
  int space_length;
  float char_spacing;
  float vertical_spacing;
  
  FontImpl(const FontDescription& desc)
    : space_length(desc.space_length),
      char_spacing(desc.char_spacing)
  {
    //std::cout << "desc.image: " << desc.image << std::endl;
    //std::cout << "desc.space: " << desc.space_length << std::endl;
    //std::cout << "Characters: " << desc.characters << std::endl;

    Surface software_surface(desc.image);
    SDL_Surface* surface = software_surface.get_surface();

    if (!surface)
      {
        std::cout << "IMG: " << desc.image.str() << std::endl;
        assert(surface);
      }

    vertical_spacing = (desc.vertical_spacing == -1) ? surface->h : desc.vertical_spacing;

    if (surface->format->BitsPerPixel != 32)
      {
        std::cout << "Error: '" << desc.pathname.str() << "' invalid, fonts need to be RGBA, but is "
                  << surface->format->BitsPerPixel << "bpp" << std::endl;
        assert(0);
      }
        
    SDL_LockSurface(surface);
    
    if (!desc.monospace)
      {
        int first = -1; // -1 signals no character start found yet
        int idx = 0;
        for(int x = 0; x <= surface->w; ++x) // '<=' so we scan one past
          // the last line, to catch
          // the last character
          {
            if (!vline_empty(surface, x, desc.alpha_threshold))
              { // line contains a character
                if (first == -1) 
                  { // found the start of a character
                    first = x;
                  } 
                else 
                  {
                    // do nothing and continue to search for an end
                  }
              }
            else
              { // line doesn't contain a character
                if (first != -1) 
                  { // we have a start and a end, so lets construct a char

                    if (idx < int(desc.characters.size()))
                      {
                        //std::cout << idx << " '" << desc.characters[idx] << "' " 
                        //          <<  " glyph: " << first << " - " << x << std::endl;

                        chrs[static_cast<unsigned char>(desc.characters[idx])]
                          = Rect(Vector2i(first, 0), 
                                 Size(x - first, surface->h));
                      }
                    else
                      {
                        std::cout << "Error: Found more desc.characters then are mapped" << std::endl;
                      }

                    idx += 1;
                    first = -1;
                  }
              }
          }

        if (idx != int(desc.characters.size())) 
          {
            std::cout << "Font: " << desc.image << "\n"
                      << "  Error: glyphs found: " << idx << ", expected "  << desc.characters.size() << "\n"
                      << "  Format: bpp: " << int(surface->format->BitsPerPixel) << "\n"
                      << "  Size: " << surface->w << "x" << surface->h
              //      << "  RMask: " << hex << surface->format->Rmask << "\n"
              //      << "  GMask: " << hex << surface->format->Gmask << "\n"
              //      << "  BMask: " << hex << surface->format->Bmask << "\n"
              //      << "  AMask: " << hex << surface->format->Amask << "\n"
                      << std::endl;
          }
      }
    else // monospace
      {
        assert(surface->w % desc.characters.size() == 0);

        space_length = surface->w / desc.characters.size();
        
        for(int i = 0; i < int(desc.characters.size()); ++i)
          {
            chrs[static_cast<unsigned char>(desc.characters[i])]
              = Rect(Vector2i(i * space_length, 0),
                     Size(space_length, surface->h));
          }
      }

    SDL_UnlockSurface(surface);

    framebuffer_surface = Display::get_framebuffer().create_surface(software_surface);
  }

  ~FontImpl()
  {
  }

  void render(Origin origin, int x, int y_, const std::string& text, Framebuffer& fb)
  {
    float y = float(y_);
    // FIXME: only origins top_left, top_right and top_center to work right now
    LineIterator it(text);
    while(it.next()) {
      render_line(origin, x, int(y), it.get(), fb);
      y += vertical_spacing;
    }
  }

  void render_line(Origin origin, int x, int y, const std::string& text, Framebuffer& fb)
  {
    Vector2i offset = calc_origin(origin, get_size(text));

    float dstx = float(x - offset.x);
    float dsty = float(y - offset.y);
    
    for(std::string::size_type i = 0; i < text.size(); ++i)
      {
        if (text[i] == ' ')
          {
            dstx += space_length + char_spacing;
          }
        else
          {
            Rect& srcrect = chrs[static_cast<unsigned char>(text[i])];
            if (srcrect.get_width() != 0 && srcrect.get_height() != 0)
              {
                fb.draw_surface(framebuffer_surface, srcrect, Vector2i(dstx, dsty));
                dstx += srcrect.get_width() + char_spacing;
              }
            else
              {
                //std::cout << "Font: character " << static_cast<unsigned char>(text[i]) << " missing in font" << std::endl;
              }
          }
      }
  }

  int get_height() const
  {
    return framebuffer_surface.get_height();
  }

  int get_width(char idx) const
  {
    return chrs[static_cast<unsigned char>(idx)].get_width();
  }

  int  get_width(const std::string& text) const
  {
    float width = 0.0f;
    float last_width = 0;
    for(std::string::size_type i = 0; i < text.size(); ++i)
      {
        if (text[i] == ' ')
          {
            width += space_length + char_spacing;
          }
        else if (text[i] == '\n')
          {
            last_width = std::max(last_width, width);
            width = 0;
          }
        else
          {
            width += chrs[static_cast<unsigned char>(text[i])].get_width() + char_spacing;
          }
      }
    return int(std::max(width, last_width));
  }

  Size get_size(const std::string& text) const
  {
    return Size(get_width(text), get_height());
  }

  Rect bounding_rect(int x, int y, const std::string& str) const
  {
    return Rect(Vector2i(x, y), get_size(str));
  }
};

Font::Font()
{
}

Font::Font(const FontDescription& desc)
  : impl(new FontImpl(desc))
{
}

void
Font::render(int x, int y, const std::string& text, Framebuffer& fb)
{
  if (impl)
    impl->render(origin_top_left, x,y,text, fb);
}

void
Font::render(Origin origin, int x, int y, const std::string& text, Framebuffer& fb)
{
  if (impl)
    impl->render(origin, x,y,text, fb); 
}

int
Font::get_height() const
{
  if (impl)
    return impl->get_height();
  else
    return 0;
}

int
Font::get_width(char c) const
{
  if (impl)
    return impl->get_width(c);
  else
    return 0; 
}

int
Font::get_width(const std::string& text) const
{
  if (impl)
    return impl->get_width(text);
  else
    return 0;  
}

Size
Font::get_size(const std::string& str) const
{
  if (impl)
    return impl->get_size(str);
  else
    return Size(); 
}

Rect
Font::bounding_rect(int x, int y, const std::string& str) const
{
  if (impl)
    return impl->bounding_rect(x, y, str);
  else
    return Rect();
}

/* EOF */
