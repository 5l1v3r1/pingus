//  $Id: WorldObjDataFactory.hh,v 1.1 2001/08/09 12:04:49 grumbel Exp $
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

#ifndef WORLDOBJFACTORY_HH
#define WORLDOBJFACTORY_HH

#include <string>
#include <map>
#include "WorldObj.hh"
#include "PingusError.hh"
#include "XMLhelper.hh"

class WorldObjDataAbstractFactory;

/** WorldObjDataFactory which can be used to create all kinds of
    WorldObjData's by given its id */
class WorldObjDataFactory
{
private:
  std::map<std::string, WorldObjDataAbstractFactory*> factories;

  static WorldObjDataFactory* instance_;

  WorldObjDataFactory ();
public:
  static WorldObjDataFactory* instance ();
  boost::shared_ptr<WorldObjData> create (xmlDocPtr doc, xmlNodePtr cur);
  void register_factory (const std::string& id,
			 WorldObjDataAbstractFactory* factory);
};

/** WorldObjDataAbstractFactory, interface for creating factories */
class WorldObjDataAbstractFactory
{
public:
  WorldObjDataAbstractFactory (const std::string& id) {
    WorldObjDataFactory::instance ()-> register_factory (id, this);
  }
  
  virtual boost::shared_ptr<WorldObjData> create (xmlDocPtr doc, xmlNodePtr cur) =0;
};

/** Template to create factories, usage:
    new WorldObjDataFactoryImpl<"liquid", Liquid>; */
template<class T>
class WorldObjDataFactoryImpl : public WorldObjDataAbstractFactory
{
public:
  WorldObjDataFactoryImpl (const std::string& id)
    : WorldObjDataAbstractFactory (id) {}
  
  boost::shared_ptr<WorldObjData> create (xmlDocPtr doc, xmlNodePtr cur) { return T::create (doc, cur); }
};

#endif

/* EOF */
