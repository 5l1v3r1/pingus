//  $Id: savegame_manager.hxx,v 1.3 2003/04/19 10:23:17 torangan Exp $
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

#ifndef HEADER_SAVEGAME_MANAGER_HXX
#define HEADER_SAVEGAME_MANAGER_HXX

#include <map>
#include "savegame.hxx"

/** */
class SavegameManager
{
private:
  static SavegameManager* instance_;
  typedef std::map<std::string, Savegame*> SavegameTable;

  std::string filename;
  SavegameTable savegames;
public:
  static SavegameManager* instance();

  SavegameManager(const std::string& filename);
  ~SavegameManager();

  Savegame* get(const std::string& levelname);
  void store(Savegame&);

  /** Write the current savegames down to file */
  void flush();
private:
  SavegameManager (const SavegameManager&);
  SavegameManager& operator= (const SavegameManager&);
};

#endif

/* EOF */
