//  $Id: pingus_resource.cxx,v 1.13 2002/06/28 17:02:25 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef WIN32
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
#endif
#include <assert.h>

#include <ClanLib/png.h>
#include <ClanLib/Display/Font/font.h>
#include "system.hxx"
#include "path_manager.hxx"
#include "globals.hxx"
#include "pingus_resource.hxx"
#include "blitter.hxx"
#include "debug.hxx"

using namespace Pingus;

std::map<std::string, CL_ResourceManager*> PingusResource::resource_map;
std::map<ResDescriptor, CL_Surface>       PingusResource::surface_map;
std::map<ResDescriptor, CL_Font*>          PingusResource::font_map;


std::string
suffix_fixer(const std::string& filename)
{
  std::string wrong_suffix;
  std::string right_suffix;

  // Using compiled datafiles, they load faster, but are larger
  if (use_datafile)
    {
      right_suffix = ".dat";
      wrong_suffix = ".scr";
    }
  else
    {
      right_suffix = ".scr";
      wrong_suffix = ".dat";
    }

  // Filename ends with ".dat", replace it with ".scr" and return.
  if (filename.substr(filename.size() - 4, std::string::npos) == wrong_suffix)
    {
      //std::cout << "PingusResource: Filename with \"" << wrong_suffix << "\" found: " << filename << std::endl;
      return filename.substr(0, filename.size() - 4) + right_suffix;
    }

  // Filename does not end with ".scr", than add it and return
  if (filename.substr(filename.size() - 4, std::string::npos) != right_suffix)
    {
      //std::cout << "PingusResource: filename doesn't contain \"" << right_suffix << "\", fixing: " << filename << std::endl;
      return (filename + right_suffix);
    }

  // Everything should be all right, just return.
  return filename;
}

PingusResource::PingusResource()
{
  //std::cout << "PingusResource Constructor called" << std::endl;
}

CL_ResourceManager*
PingusResource::get(const std::string& arg_filename)
{
  std::string filename = suffix_fixer(arg_filename);
  //std::cout << "PingusResource: getting: " << filename << std::endl;

  CL_ResourceManager* res_manager;

  res_manager = resource_map[filename];

  if (res_manager)
    {
      return res_manager;
    }
  else
    {
      std::string res_filename;

      res_filename = "data/" + filename;

      // FIXME: Memory hole... 
      res_manager = new CL_ResourceManager(path_manager.complete (res_filename.c_str()),
      					   /* is_datafile = */ use_datafile);
      
      resource_map[filename] = res_manager;
      return res_manager;
    }
}

CL_Surface
PingusResource::load_surface(const std::string& res_name, 
			     const std::string& datafile,
			     ResourceModifier modifier)
{
  return load_surface(ResDescriptor(res_name, datafile, 
				    ResDescriptor::RD_RESOURCE,
				    modifier));
}

CL_Surface
PingusResource::load_surface(const ResDescriptor& res_desc)
{
  pout(PINGUS_DEBUG_RESOURCES) << "PingusResource: Loading surface: " << res_desc << std::endl;

  // try to load from cache
  CL_Surface surf = load_from_cache(res_desc);

  if (!surf) // not in cache
    {
      ResDescriptor desc = res_desc;
      desc.modifier = ROT0;

      // Try to an unmodified version from cache
      surf = load_from_cache(desc);

      if (surf) // found unmodified version in cache
	{
	  surf = apply_modifier (surf, res_desc);
      
	  // add to cache (FIXME: doesn't work)
	  surface_map[res_desc] = surf;
	}
      else // never loaded, need to load it from source
	{
	  ResDescriptor desc = res_desc;
	  desc.modifier = ROT0;

	  surf = load_from_source (desc);
	  surface_map[desc] = surf; // add to cache

	  surf = apply_modifier (surf, desc);
	  surface_map[res_desc] = surf; // add modified version to cache
	}
    }

  return surf;
}

CL_Surface
PingusResource::load_from_cache (const ResDescriptor& res_desc)
{
  return surface_map[res_desc];
}

CL_Surface
PingusResource::apply_modifier (const CL_Surface& surf, const ResDescriptor& res_desc)
{
  if (res_desc.modifier != ROT0)
    std::cout << "Using expensive blitting" << std::endl;

  switch (res_desc.modifier)
    {
      // FIXME: muahhhaa... I write slower code than you....
    case ROT0:
      return surf;
      
    case ROT90:
      return Blitter::rotate_90(surf);

    case ROT180:
      return Blitter::rotate_90(Blitter::rotate_90(surf));

    case ROT270:
      return Blitter::rotate_90(Blitter::rotate_90(Blitter::rotate_90(surf)));

    case ROT0FLIP:
      return Blitter::flip_horizontal(surf);

    case ROT90FLIP:
      return Blitter::flip_horizontal(Blitter::rotate_90(surf));

    case ROT180FLIP:
      return Blitter::flip_horizontal(Blitter::rotate_90(Blitter::rotate_90(surf)));

    case ROT270FLIP:
      return Blitter::flip_horizontal(Blitter::rotate_90(Blitter::rotate_90(Blitter::rotate_90(surf))));

    default:
      std::cout << "PingusResource: Unhandled modifier: " << res_desc.modifier << std::endl;
      return surf;
    }
}

CL_Surface
PingusResource::load_from_source (const ResDescriptor& res_desc)
{
  switch(res_desc.type)
    {
    case ResDescriptor::RD_RESOURCE:
      try {
	return CL_Surface (res_desc.res_name.c_str(), get(suffix_fixer(res_desc.datafile)));
      } catch (CL_Error err) {
	pout << "PingusResource:" << res_desc
	     <<  ":-404-:" << err.message << std::endl;
	try {
	  return CL_Surface ("misc/404", get(suffix_fixer("core")));
	} catch (CL_Error err2) {
	  pout << "PingusResource: Fatal error, important gfx files (404.pcx) couldn't be loaded!" << std::endl;
	  throw err;
	}
      }
      break;
	  
    case ResDescriptor::RD_FILE:
      {
	std::string filename = System::get_statdir() + "images/" + res_desc.res_name;
	// FIXME: Memory leak?
	pout << "PingusResource::load_surface(" << res_desc.res_name << ")" << std::endl;
	// FIXME: Add pcx, jpeg, tga support here 
	return CL_Surface(new CL_PNGProvider(filename, NULL), true);
	pout << "DONE" << std::endl;
	break;
      }
	  
    case ResDescriptor::RD_AUTO:
      perr << "PingusResource: ResDescriptor::AUTO not implemented" << std::endl;
      assert (false);

    default:
      perr << "PingusResource: Unknown ResDescriptor::type: " << res_desc.type  << std::endl;
      assert (false);
      return CL_Surface();
      break;
    }
}

CL_Font* 
PingusResource::load_font(const std::string& res_name,
			  const std::string& datafile)
{
  return load_font(ResDescriptor(res_name, datafile, 
				 ResDescriptor::RD_RESOURCE));
}

CL_Font* 
PingusResource::load_font(const ResDescriptor& res_desc)
{
  pout(PINGUS_DEBUG_LOADING) << "PingusResource: Loading font: " << res_desc << std::endl;

  CL_Font* font = font_map[res_desc];
  
  if (font) 
    {
      return font;
    }
  else
    {
      switch(res_desc.type)
	{
	case ResDescriptor::RD_RESOURCE:
	  try {
	    font = CL_Font::load(res_desc.res_name.c_str(),
				 get(suffix_fixer(res_desc.datafile)));
	  } catch (CL_Error err) {
	    pout << "PingusResource: " << err.message << std::endl
	         << "PingusResource: Couldn't load font: " << res_desc << std::endl;
	    assert (!"PingusResource: Fatal error can't continue!");
	  }
	  font_map[res_desc] = font;
	  return font;
	  
	case ResDescriptor::RD_FILE:
	  pout << "PingusResource: ResDescriptor::FILE not implemented" << std::endl;
	  return 0;
	  
	case ResDescriptor::RD_AUTO:
	  pout << "PingusResource: ResDescriptor::AUTO not implemented" << std::endl;
	  return 0;

	default:
	  pout << "PingusResource: Unknown ResDescriptor::type: " << res_desc.type  << std::endl;
	  return 0;
	}
    }
}

void
PingusResource::cleanup ()
{
  pout(PINGUS_DEBUG_RESOURCES) << "PingusResource::cleanup ()" << std::endl;
  
  for (std::map<ResDescriptor, CL_Surface>::iterator i = surface_map.begin ();
       i != surface_map.end (); ++i)
    {
      if (i->first.type == ResDescriptor::RD_FILE
	  && i->second.get_reference_count () == 1)
	{
	  pout(PINGUS_DEBUG_RESOURCES) << "XXX Releasing File: " << i->first
	                               << " => " << i->second.get_reference_count () << std::endl;
	  surface_map.erase(i);
	}
      else if (i->first.type == ResDescriptor::RD_RESOURCE
	       && i->second.get_reference_count () == 2)
	{
	  pout(PINGUS_DEBUG_RESOURCES) << "XXX Releasing Resource : " << i->first
	                               << " => " << i->second.get_reference_count () << std::endl;
	  surface_map.erase(i);
	}
    }
}

unsigned int
PingusResource::get_mtime (const std::string& res_name,
			   const std::string& datafile)
{
  try 
    {
      CL_ResourceManager* res_man = PingusResource::get(datafile);
      
      if (!res_man->is_from_source ())
	{
	  // FIXME: not implemented
	  return 0;
	}
      else
	{
	  CL_Resource& res = res_man->get_resource(res_name);
  
	  std::string filename = res.get_full_location();

#ifndef WIN32
	  struct stat stat_buf;
	  if (stat(filename.c_str(), &stat_buf) == 0)
	    return stat_buf.st_mtime;
	  else
	    return 0;
#else
	  // FIXME: Win32 mtime getter not implemented
	  return 0;
#endif
	}
    } 
  catch (CL_Error& err) 
    {
      std::cout << "PingusResource::get_mtime: CL_Error: " << err.message << std::endl;
      return 0;
    }
}

/* EOF */
