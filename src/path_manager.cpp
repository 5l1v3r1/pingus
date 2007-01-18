//  $Id: path_manager.cxx,v 1.7 2003/10/18 23:17:27 grumbel Exp $
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

#include "globals.hpp"
#include "system.hpp"
#include "path_manager.hpp"
#include "debug.hpp"


PathManager path_manager;

PathManager::PathManager ()
  : path_found (false)
{
}

PathManager::~PathManager ()
{
}

void
PathManager::add_path (const std::string& path)
{
  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: add_path: " << path << std::endl;
  path_list.push_back (path);
}

std::string
PathManager::complete (const std::string& relative_path)
{
  return relative_path;
#if 0
  std::string comp_path = base_path + "/" + relative_path;
  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: " << relative_path << " -> " << comp_path << std::endl;

  return comp_path;
#endif
}

bool
PathManager::find_path (const std::list<std::string>& file_list)
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

	  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: Using base_path: " << base_path << std::endl;

	  return true;
	}
    }

  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: No base path found" << std::endl;

  return false;
}

/** Search for a path which contains the file 'file' */
bool
PathManager::find_path (const std::string& file)
{
  for (PathIter i = path_list.begin (); !path_found && i != path_list.end (); ++i)
    {
      if (System::exist(*i + "/" + file))
	{
	  path_found = true;
	  base_path = *i;

	  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: Using base_path: " << base_path << std::endl;

	  return true;
	}
    }

  pout(PINGUS_DEBUG_PATHMGR) << "PathManager: No base path found" << std::endl;

  return false;
}

void
PathManager::set_path (const std::string& path)
{
  base_path = path;
}


/* EOF */
