//  $Id: PathManager.cc,v 1.4 2001/12/02 21:43:47 grumbel Exp $
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

#include <iostream>
#include "globals.hh"
#include "System.hh"
#include "PathManager.hh"

PathManager path_manager;

PathManager::PathManager ()
  : path_found (false)
{
}

PathManager::~PathManager ()
{
}

void 
PathManager::add_path (std::string path)
{
  path_list.push_back (path);
}

std::string 
PathManager::complete (std::string relative_path)
{
  if (!broken_clanlib_resource_handling)
    {
      std::string comp_path = base_path + "/" + relative_path;
      if (pingus_debug_flags & PINGUS_DEBUG_LOADING)
	std::cout << "PathManager: " << relative_path << " -> " << comp_path << std::endl;
      
      return comp_path;
    }
  else
    {
      // FIXME: correct handling is disabled cause we use the change_dir () hack in PingusMain.cc
      return relative_path;
    }
}

bool 
PathManager::find_path (std::list<std::string> file_list)
{
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      bool found_file = true;
      for (PathIter f = file_list.begin (); found_file && f != file_list.end (); ++f)
	{
	  if (!System::exist(*i + "/" + *f))
	    found_file = false;
	}
      if (found_file)
	{
	  path_found = true;
	  base_path = *i;

	  if (pingus_debug_flags & PINGUS_DEBUG_LOADING)
	    std::cout << "PathManager: Using base_path: " << base_path << std::endl;

	  return true;
	}
    }

  if (pingus_debug_flags & PINGUS_DEBUG_LOADING)
    std::cout << "PathManager: No base path found" << std::endl;

  return false;
}

/** Search for a path which contains the file 'file' */
bool 
PathManager::find_path (std::string file)
{
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      if (System::exist(*i + "/" + file))
	{
	  path_found = true;
	  base_path = *i;

	  if (pingus_debug_flags & PINGUS_DEBUG_LOADING)
	    std::cout << "PathManager: Using base_path: " << base_path << std::endl;

	  return true;
	}
    }

  if (pingus_debug_flags & PINGUS_DEBUG_LOADING)
    std::cout << "PathManager: No base path found" << std::endl;

  return false;
}

void 
PathManager::set_path (std::string path)
{
  base_path = path;
}

/* EOF */
