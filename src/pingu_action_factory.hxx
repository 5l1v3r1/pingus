//  $Id: pingu_action_factory.hxx,v 1.1 2002/06/12 19:06:12 grumbel Exp $
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

#ifndef PINGUACTIONFACTORY_HH
#define PINGUACTIONFACTORY_HH

#include <map>
#include <string>

class PinguActionAbstractFactory;
class PinguAction;

namespace boost {
  template <class T> class shared_ptr;
}

class PinguActionFactory
{
private:
  /** This vector saves all allocated actions to delete them at a later point */
  std::vector<PinguAction*> all_actions;

  std::map<std::string, PinguActionAbstractFactory*> factories;
  static PinguActionFactory* instance_;
  
  PinguActionFactory ();
  void register_core_actions ();
public:
  static PinguActionFactory* instance ();
  void register_factory (const std::string& id, PinguActionAbstractFactory*);

  /** Delete all actions which this class has allocated. This needs to
      be called seperatly from the constructor, due to the used
      singleton pattern. [FIXME] */
  void delete_actions ();

  /** Allocate the given action */
  PinguAction* create (const std::string& id);
};

class PinguActionAbstractFactory
{
public:
  PinguActionAbstractFactory (const std::string& id) {
    PinguActionFactory::instance ()-> register_factory (id, this);
  }
  
  virtual PinguAction* create () =0;
};

template<class T>
class PinguActionFactoryImpl : public PinguActionAbstractFactory
{
public:
  PinguActionFactoryImpl (const std::string& id)
    : PinguActionAbstractFactory (id)
  {
  }

  PinguAction* create () {
    return new T ();
  }
};

#endif

/* EOF */
