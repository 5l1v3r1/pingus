//  $Id$
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
#  include <unistd.h>
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

#include <assert.h>

#include "system.hpp"
#include "path_manager.hpp"
#include "globals.hpp"
#include "font_description.hpp"
#include "resource.hpp"
#include "res_descriptor.hpp"
#include "blitter.hpp"
#include "sprite_description.hpp"
#include "debug.hpp"

ResourceManager Resource::resmgr;
#if 0
std::map<ResDescriptor, CL_Surface>       Resource::surface_map;
#endif

void
Resource::init()
{
  resmgr.add_resources(path_manager.complete("data/core.res"));
  resmgr.add_resources(path_manager.complete("data/entrances.res"));
  resmgr.add_resources(path_manager.complete("data/exits.res"));
  ////  resmgr.add_resources(path_manager.complete("data/fonts.res"));
  resmgr.add_resources(path_manager.complete("data/game.res"));
  resmgr.add_resources(path_manager.complete("data/groundpieces-bridge.res"));
  resmgr.add_resources(path_manager.complete("data/groundpieces-ground.res"));
  resmgr.add_resources(path_manager.complete("data/groundpieces-remove.res"));
  resmgr.add_resources(path_manager.complete("data/groundpieces-solid.res"));
  resmgr.add_resources(path_manager.complete("data/groundpieces-transparent.res"));
  resmgr.add_resources(path_manager.complete("data/hotspots.res"));
  resmgr.add_resources(path_manager.complete("data/liquids.res"));
  resmgr.add_resources(path_manager.complete("data/pingus-player0.res"));
  resmgr.add_resources(path_manager.complete("data/pingus-player1.res"));
  resmgr.add_resources(path_manager.complete("data/pingus-player2.res"));
  resmgr.add_resources(path_manager.complete("data/pingus-player3.res"));
  resmgr.add_resources(path_manager.complete("data/pingus-common.res"));
  resmgr.add_resources(path_manager.complete("data/particles.res"));
  resmgr.add_resources(path_manager.complete("data/story.res"));
  resmgr.add_resources(path_manager.complete("data/textures.res"));
  resmgr.add_resources(path_manager.complete("data/traps.res"));
  resmgr.add_resources(path_manager.complete("data/worldmaps.res"));
  resmgr.add_resources(path_manager.complete("data/worldobjs.res"));
  resmgr.add_resources(path_manager.complete("data/alias.res"));
}

// Returns all resources in the given section
#if 0
std::vector<std::string>
Resource::get_resources(const std::string& type, const std::string& section)
{
  if (section == "")
    return resmgr.get_resources_of_type(type);
  else
    return resmgr.get_resources_of_type(type, section);
}

// Returns a list of sections.  Returns all sections if left blank.
std::vector<std::string>
Resource::get_sections(const std::string& section)
{
  if (section == std::string())
    return resmgr.get_all_sections();
  else
    return resmgr.get_sections(section);
}
#endif

void
Resource::deinit()
{
  cleanup();
#if 0
  surface_map.clear();
#endif
}

Sprite
Resource::load_sprite(const ResDescriptor& desc)
{
  if (desc.modifier == ResourceModifierNS::ROT0)
    {
      return load_sprite(desc.res_name);
    }
  else
    {
      // FIXME: Add code to apply the modifier
      return load_sprite(desc.res_name);
    }
}

Surface
Resource::apply_modifier_to_surface(Surface prov, const ResDescriptor& desc)
{
  switch (desc.modifier)
    {
    case ResourceModifierNS::ROT0:
      return prov;

    case ResourceModifierNS::ROT90:
      return Blitter::rotate_90(prov);

    case ResourceModifierNS::ROT180:
      return Blitter::rotate_180(prov);

    case ResourceModifierNS::ROT270:
      return Blitter::rotate_270(prov);

    case ResourceModifierNS::ROT0FLIP:
      return Blitter::flip_horizontal(prov);

    case ResourceModifierNS::ROT90FLIP:
      return Blitter::rotate_90_flip(prov);

    case ResourceModifierNS::ROT180FLIP:
      return Blitter::rotate_180_flip(prov);

    case ResourceModifierNS::ROT270FLIP:
      return Blitter::rotate_270_flip(prov);

    default:
      perr << "Resource: Unhandled modifier: " << desc.modifier << std::endl;
      return prov;
    }
}

Sprite
Resource::load_sprite(const std::string& res_name)
{
  SpriteDescription* desc = resmgr.get_sprite_description(res_name);
  if (desc)
    return Sprite(*desc);
  else
    return Sprite();

#if 0
  try {
    return CL_Sprite(res_name, &resmgr);
  } catch (CL_Error& err) {
    std::cout << "Resource::load_sprite: CL_Error: '" << res_name << "'" << std::endl;
    std::cout << "CL_Error: " << err.message << std::endl;
    return CL_Sprite("core/misc/404sprite", &resmgr);
  }
#endif
}

CollisionMask
Resource::load_collision_mask(const std::string& name)
{
  return CollisionMask(name);
}

CollisionMask
Resource::load_collision_mask(const ResDescriptor& res_desc)
{
  return CollisionMask(res_desc);
}

Surface
Resource::load_surface(const ResDescriptor& desc_)
{
  SpriteDescription* desc = resmgr.get_sprite_description(desc_.res_name);
  if (desc)
    return apply_modifier_to_surface(Surface(desc->filename), desc_);
  else
    return apply_modifier_to_surface(Surface(), desc_);
}

Surface
Resource::load_surface(const std::string& res_name)
{
  return load_surface(ResDescriptor(res_name));
}

#if 0
CL_Surface
Resource::load_surface(const ResDescriptor& res_desc)
{
  // try to load from cache
  CL_Surface surf = load_from_cache(res_desc);

  if (!surf) // not in cache
    {
      ResDescriptor desc = res_desc;
      desc.modifier = ResourceModifierNS::ROT0;

      // Try to an unmodified version from cache
      surf = load_from_cache(desc);

      if (surf) // found unmodified version in cache
	{
	  pout(PINGUS_DEBUG_RESOURCES) << "Resource: Loading surface from cache 1/2: " << res_desc << std::endl;
	  surf = apply_modifier (surf, res_desc);

	  surface_map[res_desc] = surf;
	}
      else // never loaded, need to load it from source
	{
	  desc = res_desc;
	  desc.modifier = ResourceModifierNS::ROT0;

	  pout(PINGUS_DEBUG_RESOURCES) << "Resource: Loading surface from source: " << res_desc << std::endl;
	  surf = load_from_source (desc);
	  surface_map[desc] = surf; // add to cache

	  surf = apply_modifier (surf, res_desc);
	  surface_map[res_desc] = surf; // add modified version to cache
	}
    }
  else
    {
      pout(PINGUS_DEBUG_RESOURCES) << "Resource: Loading surface from cache: " << res_desc << std::endl;
    }

  return surf;
}

CL_Surface
Resource::load_from_cache (const ResDescriptor& res_desc)
{
  std::map<ResDescriptor, CL_Surface>::iterator i = surface_map.find(res_desc);
  if (i == surface_map.end())
    {
      return CL_Surface();
    }
  else
    {
      return i->second;
    }
}
#endif 

Font
Resource::load_font(const std::string& res_name)
{
  FontDescription desc(Pathname("images/" + res_name + ".font", Pathname::DATA_PATH));
  //("data/images/fonts/chalk_large-iso-8859-1.font");
  return Font(desc);
}

void
Resource::cleanup ()
{
#if 0
  CL_Resource res;
  std::vector<std::string> resources = resmgr.get_all_resources();
  for (std::vector<std::string>::iterator i = resources.begin(); i != resources.end(); i++)
    {
      res = resmgr.get_resource(*i);
      while (res.get_reference_count() > 0)
        res.unload();
    }
#endif
}

unsigned int
Resource::get_mtime (const std::string& res_name)
{
  /*
    try
    {
    CL_ResourceManager res_man = Resource::get(datafile);

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
    }
    catch (CL_Error& err)
    {
    std::cout << "Resource::get_mtime: CL_Error: " << err.message << std::endl;
    return 0;
    }
    #endif
  */
  return 0;
}

Sprite
Resource::load_thumb_sprite(const std::string& name)
{
  Sprite sprite = Resource::load_sprite(name);

  Size thumb_size;
  if (sprite.get_width() <= 48)
    thumb_size.width = sprite.get_width();
  else
    thumb_size.width = 48;

  if (sprite.get_height() <= 48)
    thumb_size.height = sprite.get_height();
  else
    thumb_size.height = 48;

  sprite.scale(thumb_size.width, thumb_size.height);

  sprite.set_hotspot(origin_top_left, (48 - sprite.get_width())/2, (48 - sprite.get_height())/2);

  return sprite;
}

/* EOF */
