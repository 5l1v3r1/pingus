//  $Id: worldobj_data_factory.cxx,v 1.3 2002/08/16 15:13:59 torangan Exp $
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

#include "liquid.hxx"
#include "xml_helper.hxx"
#include "pingus_error.hxx"

// Backgrounds
#include "backgrounds/surface_background_data.hxx"
#include "backgrounds/starfield_background.hxx"
#include "backgrounds/solidcolor_background.hxx"
#include "backgrounds/thunderstorm_background_data.hxx"

// Special Objects
#include "worldobjs/switch_door.hxx"
#include "worldobjs/ice_block.hxx"
#include "worldobjs/info_box.hxx"
#include "worldobjs/conveyor_belt.hxx"
#include "worldobjs/teleporter.hxx"

#include "trap_data.hxx"
#include "hotspot_data.hxx"
#include "entrance_data.hxx"
#include "worldobj_data_factory.hxx"

WorldObjDataFactory* WorldObjDataFactory::instance_ = 0;

WorldObjDataFactory::WorldObjDataFactory ()
{
  // Register all WorldObjData's
}

WorldObjDataFactory* 
WorldObjDataFactory::instance () 
{ 
  if ( ! instance_) 
    {
      instance_ = new WorldObjDataFactory ();
      
      // Registring Factories
      new WorldObjDataFactoryImpl<TrapData>("trap");
      new WorldObjDataFactoryImpl<LiquidData>("liquid");
      new WorldObjDataFactoryImpl<HotspotData>("hotspot");
      new WorldObjDataFactoryImpl<EntranceData>("entrance");

      // Special Objects 
      new WorldObjDataFactoryImpl<SwitchDoorData>("switchdoor");
      new WorldObjDataFactoryImpl<InfoBoxData>("infobox");
      new WorldObjDataFactoryImpl<IceBlockData>("iceblock");
      new WorldObjDataFactoryImpl<ConveyorBeltData>("conveyorbelt");
      new WorldObjDataFactoryImpl<TeleporterData>("teleporter");

      // Backgrounds
      new WorldObjDataFactoryImpl<SurfaceBackgroundData>("surface-background");
      new WorldObjDataFactoryImpl<StarfieldBackgroundData>("starfield-background");
      new WorldObjDataFactoryImpl<SolidColorBackgroundData>("solidcolor-background");
      new WorldObjDataFactoryImpl<ThunderstormBackgroundData>("thunderstorm-background");
    }

  return instance_;
}

WorldObjData*
WorldObjDataFactory::create (xmlDocPtr doc, xmlNodePtr cur)
{
  std::cout << "WorldObjDataFactory::create (xmlDocPtr doc, xmlNodePtr cur)" << std::endl;
  char* type = (char*)xmlGetProp(cur, (xmlChar*)"type");
  if (type)
    {
      return create (type, doc, cur);
    }
  else
    {
      PingusError::raise ("WorldObjDataFactory::create: Error, no type given.");
    }
    
  return 0; //never reached
}

WorldObjData*
WorldObjDataFactory::create (const std::string& id,
			     xmlDocPtr doc, xmlNodePtr cur)
{
  std::cout << "WorldObjDataFactory::create (id, xmlDocPtr doc, xmlNodePtr cur)" << std::endl;

  std::map<std::string, WorldObjDataAbstractFactory*>::iterator it = factories.find(id);
  
  if (it == factories.end())
    PingusError::raise("WorldObjDataFactory: Invalid id: " + id);
  else 
    return it->second->create (doc, cur);
    
  return 0; // never reached
}

void
WorldObjDataFactory::register_factory (const std::string& id,
				       WorldObjDataAbstractFactory* factory)
{
  factories[id] = factory;
}


/* EOF */
