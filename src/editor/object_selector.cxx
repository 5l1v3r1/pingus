//  $Id: object_selector.cxx,v 1.37 2003/03/30 13:12:35 grumbel Exp $
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

#include <ClanLib/Core/IOData/directory_scanner.h>
#include <ClanLib/Core/Resources/resource_manager.h>
#include <ClanLib/Core/System/system.h>
#include <ClanLib/Display/Display/display.h>
#include <ClanLib/Display/Font/font.h>
#include <ClanLib/Display/Input/inputbuffer.h>
#include <ClanLib/Display/Input/mouse.h>
#include "../console.hxx"
#include "../globals.hxx"
#include "../loading.hxx"
#include "../my_gettext.hxx"
#include "../path_manager.hxx"
#include "../pingus_resource.hxx"
#include "../string_converter.hxx"
#include "../system.hxx"
#include "object_selector.hxx"
#include "object_manager.hxx"
#include "string_reader.hxx"
#include "thumb_cache.hxx"
#include "weather_obj.hxx"
#include "../prefab.hxx"

#include "../worldobjsdata/entrance_data.hxx"
#include "../worldobjsdata/exit_data.hxx"
#include "../worldobjsdata/groundpiece_data.hxx"
#include "../worldobjsdata/hotspot_data.hxx"
#include "../worldobjsdata/liquid_data.hxx"
#include "../worldobjsdata/solid_color_background_data.hxx"
#include "../worldobjsdata/starfield_background_data.hxx"
#include "../worldobjsdata/surface_background_data.hxx"
#include "../worldobjsdata/thunderstorm_background_data.hxx"

#include "../editorobjs/bumper_obj.hxx"
#include "../editorobjs/conveyor_belt_obj.hxx"
#include "../editorobjs/exit_obj.hxx"
#include "../editorobjs/fake_exit_obj.hxx"
#include "../editorobjs/guillotine_obj.hxx"
#include "../editorobjs/groundpiece_obj.hxx"
#include "../editorobjs/hammer_obj.hxx"
#include "../editorobjs/hotspot_obj.hxx"
#include "../editorobjs/ice_block_obj.hxx"
#include "../editorobjs/info_box_obj.hxx"
#include "../editorobjs/laser_exit_obj.hxx"
#include "../editorobjs/smasher_obj.hxx"
#include "../editorobjs/spike_obj.hxx"
#include "../editorobjs/switch_door_obj.hxx"
#include "../editorobjs/teleporter_obj.hxx"

using namespace EditorObjs;
using namespace WorldObjsData;

namespace EditorNS {

ObjectSelector::ObjectSelector ()
{
  last_object = "GroundPieces/";
  font = PingusResource::load_font("Fonts/courier_small", "fonts");
  //data_loaded = false;
}

ObjectSelector::~ObjectSelector ()
{
}
  
/** FIXME: Ugly interface, the arguments should not be the offset, but
    instead the absolute position */
void
ObjectSelector::get_obj (ObjectManager* arg_obj_mgr,
                         int x_off, int y_off)
{
  // FIXME: Sick coordinate handling...
  x_offset = x_off;
  y_offset = y_off;

  obj_mgr = arg_obj_mgr;
  pos = Vector (CL_Mouse::get_x () - x_offset,
                CL_Mouse::get_y () - y_offset, 
                0.0f);

  select_obj_type();
}

void
ObjectSelector::get_trap ()
{
  CL_Display::clear_display();
  font->print_left(20, 20, _("1 - guillotine"));
  font->print_left(20, 50, _("2 - hammer"));
  font->print_left(20, 80, _("3 - spike"));
  font->print_left(20,110, _("4 - laser_exit"));
  font->print_left(20,140, _("5 - fake_exit"));
  font->print_left(20,170, _("6 - smasher"));
  font->print_left(20,200, _("7 - bumper"));
  Display::flip_display();

  while (true) 
    {
      switch (read_key()) 
	{
	case CL_KEY_1:
	  obj_mgr->add(GuillotineObj::create(pos));
          return;
	case CL_KEY_2:
	  obj_mgr->add(HammerObj::create(pos));
          return;
	case CL_KEY_3:
          obj_mgr->add(SpikeObj::create(pos));
          return;
	case CL_KEY_4:
          obj_mgr->add(LaserExitObj::create(pos));
          return;
	case CL_KEY_5:
	  obj_mgr->add(FakeExitObj::create(pos));
          return;
	case CL_KEY_6:
	  obj_mgr->add(SmasherObj::create(pos));
          return;
	case CL_KEY_7:
	  obj_mgr->add(BumperObj::create(pos));
          return;
        case CL_KEY_ESCAPE:
	  // do nothing
          return;
	}
    }
}

void
ObjectSelector::get_groundpiece (const Groundtype::GPType& gptype)
{
  GroundpieceData data;
  std::string datafile = std::string("groundpieces-") + Groundtype::type_to_string (gptype);

  data.pos = pos;

  std::string str = select_surface(datafile);

  if (!str.empty())
    {
      data.desc = ResDescriptor(str, datafile, ResDescriptor::RD_RESOURCE);
      data.gptype = gptype;

      obj_mgr->add(new EditorObjs::GroundpieceObj(data));
    }
}

void
ObjectSelector::get_hotspot (const std::string& filename)
{
  HotspotData data;
  data.pos = pos;
  std::string str = select_surface(filename);

  if (!str.empty())
    {
      data.desc = ResDescriptor(str, filename, ResDescriptor::RD_RESOURCE);
      data.speed = -1;
    }
  
  data.insert_EditorObjs(obj_mgr);
}

void
ObjectSelector::get_worldobj ()
{
  CL_Display::clear_display();
  font->print_left(20,  20, _("Select a WorldObj"));
  font->print_left(20,  50, _("1 - teleporter"));
  font->print_left(20,  70, _("2 - switch and door"));
  font->print_left(20,  90, _("3 - ConveyorBelt"));
  font->print_left(20, 110, _("4 - IceBlock"));
  font->print_left(20, 130, _("5 - InfoBox"));
  //font->print_left(20, 110, _("5 - Liquid"));
  Display::flip_display();

  while (true) 
    {
      switch (read_key()) 
	{
	case CL_KEY_1:
	  obj_mgr->add(TeleporterObj::create(pos));
	  return;
	  
        case CL_KEY_2:
          obj_mgr->add(SwitchDoorObj::create(pos));
	  return;
          
        case CL_KEY_3:
          obj_mgr->add(ConveyorBeltObj::create(pos));
          return;
          
        case CL_KEY_4:
          obj_mgr->add(IceBlockObj::create(pos));
          return;
          
        case CL_KEY_5:
          obj_mgr->add(InfoBoxObj::create(pos));
          return;
	  
        case CL_KEY_ESCAPE:
          return;
        }
    }
}

void
ObjectSelector::get_weather ()
{
  std::string type;
  bool done = false;

  CL_Display::clear_display();
  font->print_left(20, 20, _("Select a weather"));
  font->print_left(20, 50, _("1 - snow"));
  font->print_left(20, 70, _("2 - rain"));
  Display::flip_display();

  while (!done) 
    {
      switch (read_key()) 
	{
	case CL_KEY_1:
	  type = "snow-generator";
	  done = true;
	  break;
	case CL_KEY_2:
	  type = "rain-generator";
	  done = true;
	  break;
	}
    }
  
  std::cout << "Weather objects currently not implemented" << std::endl;

  obj_mgr->add(new WeatherObj(type));
}

void
ObjectSelector::get_entrance ()
{
  EntranceData entrance;
  bool have_name = false;
  entrance.pos = pos;

  CL_Display::clear_display();
  font->print_left(20, 20, _("Select an entrance"));
  font->print_left(20, 50, _("1 - generic"));
  font->print_left(20, 70, _("2 - woodthing"));
  font->print_left(20, 90, _("3 - cloud"));
  font->print_left(20, 120, _("h - entrance surface (hotspot)"));
  Display::flip_display();

  while (!have_name) 
    {
      switch (read_key()) 
	{

	case CL_KEY_1:
	  entrance.type = "generic";
	  have_name = true;
	  break;

	case CL_KEY_2:
	  entrance.type = "woodthing";
	  have_name = true;
	  break;

	case CL_KEY_3:
	  entrance.type = "cloud";
	  have_name = true;
	  break;

	case CL_KEY_4:
	case CL_KEY_H:
          get_hotspot("entrances");
          break;

	default:
	  if (verbose) std::cout << "Unknown keypressed" << std::endl;
          break;
	}
    }
  
  entrance.insert_EditorObjs (obj_mgr);
}

void
ObjectSelector::get_exit ()
{
  std::string str;
  ExitData data;
  data.pos = pos;
  
  str = select_surface("exits");
  
  last_object = str;

  if (str.empty())
    return;
  
  data.desc = ResDescriptor(str, "exits", ResDescriptor::RD_RESOURCE);
  
  data.insert_EditorObjs (obj_mgr);
}

void
ObjectSelector::get_liquid ()
{
  std::cout << "ObjectSelector::get_liquid() not implemented" << std::endl;
  LiquidData data;

  data.pos = pos;
  data.old_width_handling = false;
  data.width = 5;
  data.desc = ResDescriptor("Liquid/slime", "liquids", ResDescriptor::RD_RESOURCE);

  data.insert_EditorObjs (obj_mgr);
}

void
ObjectSelector::get_from_file ()
{
  CL_Display::clear_display();
  font->print_left(20, 20, _("What object type do you want?"));
  font->print_left(20, 50, _("h - Hotspot"));
  font->print_left(20, 70, _("g - Groundpiece (ground) [not implemented]")); 
  Display::flip_display();

  while (true) 
    {
      switch (read_key()) 
	{
	case CL_KEY_H:
	  {
	    System::Directory dir = System::opendir (System::get_statdir () + "images/");
	    std::list<std::string> strs;

	    for (System::DirectoryIter i = dir.begin (); i != dir.end (); ++i)
	      {
		if (i->type == System::DirectoryEntry::DE_FILE)
		  {
		    //std::cout << "Directory entry: " << System::get_statdir() + "images/" + i->name << std::endl;
		    strs.push_back (System::get_statdir() + "images/" + i->name);
		  }
	      }

	    StringReader reader("Input the image name:",
				System::get_statdir () + "images/");
	    reader.set_strings(&strs);
	    std::string file = reader.read_string();
	    HotspotData data;
	    data.pos = pos;
	    // FIXME: Ugly hack, since ClanLib appends './'
	    data.desc = ResDescriptor ("../../../../../../../../../../../" + file, 
				       "", ResDescriptor::RD_FILE);
            data.insert_EditorObjs(obj_mgr);
	    return;
	  }
	  break;

	case CL_KEY_G:
	  console << "ObjectSelector: Inserting groundpieces is not implemented" << std::endl;
          return;

	case CL_KEY_ESCAPE:
          return;
	}
    }
}

void
ObjectSelector::select_obj_type ()
{
  CL_Display::clear_display();
  font->print_left(20, 20, _("Which object do you want?"));
  font->print_left(20, 70, _("g - Groundpiece (ground)"));
  font->print_left(20, 90, _("s - Groundpiece (solid)"));
  font->print_left(20,110, _("b - Groundpiece (bridge)"));
  font->print_left(20,130, _("n - Groundpiece (transparent)"));
  font->print_left(20,150, _("r - Groundpiece (remove)"));
  font->print_left(20,170, _("h - Hotspot"));
  font->print_left(20,190, _("e - Entrance"));
  font->print_left(20,210, _("x - Exit"));
  font->print_left(20,230, _("l - Liquid"));
  font->print_left(20,250, _("w - Weather"));
  font->print_left(20,270, _("t - Traps"));
  font->print_left(20,290, _("o - WorldObject"));
  font->print_left(20,310, _("z - Background"));
  font->print_left(20,330, _("p - Prefab (ObjectGroup)"));
  font->print_left(20,350, _("f - something from file (~/.pingus/images/)"));
  Display::flip_display();

  while (1) 
    {
      switch (read_key()) 
	{
	case CL_KEY_T:
          get_trap();
	  return;

	case CL_KEY_B:
          get_groundpiece(Groundtype::GP_BRIDGE);
          return;
	  
	case CL_KEY_R:
          get_groundpiece(Groundtype::GP_REMOVE);
          return;
	  
	case CL_KEY_S:
          get_groundpiece(Groundtype::GP_SOLID);
          return;

	case CL_KEY_G:
          get_groundpiece(Groundtype::GP_GROUND);
          return;

	case CL_KEY_N:
          get_groundpiece(Groundtype::GP_TRANSPARENT);
          return;

	case CL_KEY_H:
          get_hotspot("hotspots");
          return;
		  
	case CL_KEY_E:
          get_entrance();
          return;

	case CL_KEY_X:
          get_exit();
          return;

	case CL_KEY_L:
	  std::cout << "ObjectSelector: Liquid not implemented" << std::endl;
          get_liquid();
          return;

	case CL_KEY_W:
          get_weather();
          return;
          
	case CL_KEY_P:
          get_prefab();
          return;

	case CL_KEY_O:
          get_worldobj();
          return;

	case CL_KEY_Z:
          get_background();
          return;
		  
	case CL_KEY_F:
          get_from_file();
          return;

	case CL_KEY_ESCAPE:
	  return;
	}
    }
}


void
ObjectSelector::get_prefab ()
{
  CL_DirectoryScanner dir;
  std::vector<std::string> dir_lst;
  if (dir.scan(path_manager.complete ("prefabs/"), "*.xml"))
    {
      while (dir.next ()) {
        std::string filename = dir.get_name ();
	dir_lst.push_back (filename.substr(0, filename.length()-4));
      }
    }

  CL_Display::clear_display();
  font->print_left(20, 20, _("Which prefab do you want?"));
 
  for (std::vector<std::string>::size_type i = 0; i < dir_lst.size (); ++i)
    {
      font->print_left(20, 60 + i * 30, to_string(i + 1) + " - " + dir_lst[i]); 
    }

  Display::flip_display();
  
  int item = -1;
  while (item == -1) 
    {
      switch (read_key()) 
	{
	case CL_KEY_1:
          item = 1;
          break;
	case CL_KEY_2:
          item = 2;
          break;
	case CL_KEY_3:
          item = 3;
          break;
	case CL_KEY_4:
          item = 4;
          break;
	case CL_KEY_5:
          item = 5;
          break;
	case CL_KEY_6:
          item = 6;
          break;
	case CL_KEY_7:
          item = 7;
          break;
	case CL_KEY_8:
          item = 8;
          break;
	case CL_KEY_9:
          item = 9;
          break;
          
	case CL_KEY_ESCAPE: 
          return;
	}
    }

  if ((item-1) < static_cast<int>(dir_lst.size()))
    {
      std::cout << "ObjectSelector: Inserting prefab: " << dir_lst[item-1] << std::endl;
      Prefab* prefab = Prefab::create(dir_lst[item-1]);
      prefab->get_data()->insert_EditorObjs(obj_mgr);
      delete prefab;
    }
  else
    {
      std::cout << "ObjectSelector: invalid prefab selected" << std::endl;
    }
}

void
ObjectSelector::get_background ()
{
  CL_Display::clear_display();
  font->print_left(20, 20, _("Which object do you want?"));
  font->print_left(20, 50, _("1 - Surface Background"));
  font->print_left(20, 70, _("2 - Solid Color Background"));
  font->print_left(20, 90, _("3 - Starfield Background"));
  font->print_left(20,110, _("4 - Thunderstorm Background"));
  Display::flip_display();

  while (1) 
    {
      switch (read_key()) 
	{
	case CL_KEY_1:
	  {
	    SurfaceBackgroundData data;
	    data.desc.datafile = "textures";
	    data.desc.res_name = select_surface("textures");

	    if (!data.desc.res_name.empty())
	      {
		data.insert_EditorObjs(obj_mgr);
	      }
	    return;
	  }
          return;
	case CL_KEY_2:
          SolidColorBackgroundData().insert_EditorObjs(obj_mgr);
          return;
	case CL_KEY_3:
          StarfieldBackgroundData().insert_EditorObjs(obj_mgr);
          return;
	case CL_KEY_4:
	  ThunderstormBackgroundData ().insert_EditorObjs(obj_mgr);
          return;
	}
    }
}

std::string
ObjectSelector::select_surface (std::vector<surface_obj>& sur_list)
{
  std::cout << "ObjectSelector: Selecting surface out of: " << sur_list.size () << std::endl;
  SurfaceSelector sur_selector(&sur_list);

  return sur_selector.select();
}

std::string
ObjectSelector::select_surface (const std::string & resource_file)
{
  std::string str;
  bool datafile_loaded;
  CL_ResourceManager* res = PingusResource::get(resource_file);
  GroundpieceData data;

  datafile_loaded = data_loaded[resource_file];
  
  data.pos = pos;
  
  std::list<std::string>* liste = res->get_resources_of_type("surface");
  surface_obj sur_obj;
  std::vector<surface_obj> sur_list;
  int j = 0;

  for(std::list<std::string>::iterator i = liste->begin(); i != liste->end(); ++i)
    {
      // FIXME: This should be moved to ThumbCache
      ++j;
      sur_obj.name = *i;
      sur_obj.datafile = resource_file;
      sur_obj.thumbnail = ThumbCache::load (*i, resource_file);

      sur_list.push_back(sur_obj);

      if (!datafile_loaded && (j % 25) == 0)
	{
	  loading_screen.draw_progress(i->c_str(), (float)j / liste->size());
	}
    }
  // Showing the mousecursor again, since loading_screen hides it
  Display::show_cursor();
  data_loaded[resource_file] = true;
  //data_loaded = false;
  return select_surface(sur_list);
}

int
ObjectSelector::read_key ()
{
  CL_InputBuffer keys;
  CL_Key key;

  keys.clear();

  while (true) 
    { 
      CL_System::keep_alive();
      
      if (keys.peek_key().state != CL_Key::NoKey) 
	{
	  key = keys.get_key();
	  //std::cout << "key: " << key.ascii << std::endl;
	  return key.id;
	}
    }
}

std::string
ObjectSelector::read_string (const std::string & description, const std::string & def_str)
{
  StringReader reader(description, def_str);
  reader.set_strings(PingusResource::get("global")->get_resources_of_type("surface"));
  return reader.read_string();
}

} // namespace EditorNS

/* EOF */
