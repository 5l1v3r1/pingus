//  $Id: World.cc,v 1.24 2000/07/04 22:59:13 grumbel Exp $
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

#include <vector>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <functional>

#include "PinguBmpMap.hh"
#include "PingusSpotMap.hh"
#include "PinguRandomMap.hh"

#include "PingusError.hh"
#include "algo.hh"
#include "globals.hh"
#include "Background.hh"
#include "World.hh"
#include "traps/traps.hh"
#include "Result.hh"
#include "Liquid.hh"
#include "ActionHolder.hh"
#include "entrances/entrances.hh"
#include "FVec.hh"
#include "Timer.hh"

using namespace std;

// Workaround for a VC bug
#ifdef WIN32
#  define for if(0);else for
#endif /* WIN32 */

// Structure for the sorting algorithm (stable_sort)
struct WorldObj_less : public binary_function<WorldObj*, WorldObj*, bool>
{
  bool operator() (WorldObj* a, WorldObj* b) const 
    {
      return (*a) < (*b);
    }
};

World::World()
{
  released_pingus = 0;
  map = 0;
  background = 0;
  exit_world = false;
}

World::World(PLF* plf)
{ 
  init(plf);
}

World::~World()
{
  std::cout << "World:~World" << std::endl;

  delete map;
  delete background;

  for(vector<WorldObj*>::iterator obj = world_obj_bg.begin();
      obj != world_obj_bg.end();
      obj++)
    {
      delete *obj;
    }
}

// Merge the different layers on the screen together
void 
World::draw(int x1, int y1, int w, int h,
	    int x_of, int y_of, float s)
{
  x_of += x1;
  y_of += y1;

  background->draw_offset(x_of, y_of, s);

  for(vector<WorldObj*>::iterator obj = world_obj_bg.begin(); obj != world_obj_bg.end(); obj++)
    {
      (*obj)->draw_offset(x_of, y_of, s);
    }

  map->draw(x1, y1, w, h, x_of, y_of, s);

  for(vector<WorldObj*>::iterator obj = world_obj_fg.begin(); obj != world_obj_fg.end(); obj++)
    {
      (*obj)->draw_offset(x_of, y_of, s);
    }
  
  particle.draw_offset(x_of, y_of, s);
}

void 
World::let_move()
{
  if (!exit_world && (allowed_pingus == released_pingus || do_armageddon)
      && pingus.size() == 0) 
    {
      if (verbose) cout << "World: world finished, going down in the next seconds..." << endl;
      exit_world = true;
      exit_time = GameTime::get_time() + 75;
    }

  if (do_armageddon && armageddon_count != pingus.end())
    {
      (*armageddon_count)->set_action(action_holder->get_uaction("bomber"));
      armageddon_count++;
    }
  
  // Create new pingus, if enough time is passed
  if (!do_armageddon && (unsigned int)pingus.total_size() < allowed_pingus)
    {
      for(vector<Entrance*>::iterator i = entrance.begin(); i != entrance.end(); i++) 
	{
	  if ((*i)->pingu_ready())
	    {
	      pingus.push_back((*i)->get_pingu());
	      ++released_pingus;
	    }
	}
    }
  
  // Let all pingus move and
  // Let the pingus catch each other and
  // Let the traps catch the pingus and
  // Let the exit catch the pingus

  for(PinguIter pingu = pingus.begin(); pingu != pingus.end(); ++pingu)
    {
      (*pingu)->let_move();

      if ((*pingu)->need_catch()) {
	for(PinguIter i = pingus.begin(); i != pingus.end(); i++) {
	  (*pingu)->catch_pingu(*i);
	}
      }
    
      for(vector<Trap*>::iterator obj = traps.begin(); obj != traps.end(); obj++)
	(*obj)->catch_pingu(*pingu);
      
      for(vector<Exit*>::iterator obj = exits.begin(); obj != exits.end(); obj++) 
	(*obj)->catch_pingu(*pingu);
    }

  for(vector<trap_data>::size_type i=0; i < traps.size(); ++i)
    traps[i]->let_move();
  
  for(vector<entrance_data>::size_type i2=0; i2 < entrance.size(); ++i2) 
    entrance[i2]->let_move();
  
  particle.let_move();
  background->let_move();
  
  // Clear the explosion force list
  ForcesHolder::clear_explo_list();
}

void 
World::init(PLF* plf_data)
{
  plf = plf_data;
  do_armageddon = false;
  allowed_pingus = plf->get_pingus();
  number_to_save = plf->get_number_to_save();
  released_pingus = 0;

  exit_time = plf->get_time();
  
  init_map();
  init_background();

  Timer timer;

  timer.start();
  cout << "World: Initing world objects... " << flush;
  init_worldobjs();
  cout << "done " << timer.stop() << endl;
}

void
World::init_map()
{
  // load the foreground map
  switch (plf->map_type()) 
    {
    case SPOT:
      map = new PingusSpotMap(plf);
      break;
    case BMP:
    case RANDOM:
    default:
      throw PingusError("World: Error in PLF file: Undef or unsupported Maptype");
      break;
    }
  
  colmap = map->get_colmap();

  Particle::set_map(map);
}

void 
World::init_background()
{
  // load the background map
  background = new Background(plf->get_bg());
}

void
World::init_worldobjs()
{
  vector<exit_data>     exit_d     = plf->get_exit();
  vector<entrance_data> entrance_d = plf->get_entrance();
  vector<trap_data>     trap_d     = plf->get_traps();
  vector<hotspot_data>  hspot_d    = plf->get_hotspot();
  vector<liquid_data>   liquid_d   = plf->get_liquids();

  // Creating Exit and Entrance
  for(vector<exit_data>::iterator i = exit_d.begin(); i != exit_d.end(); i++) 
    exits.push_back(new Exit(*i));
  
  for(vector<entrance_data>::size_type i = 0; i < entrance_d.size(); ++i) 
    entrance.push_back(get_entrance(entrance_d[i]));

  for(vector<trap_data>::size_type i=0; i < trap_d.size(); ++i)
    traps.push_back(get_trap(trap_d[i]));

  // Creating the foreground and background hotspots
  for(vector<hotspot_data>::size_type i = 0; i < hspot_d.size(); ++i)
    hotspot.push_back(new Hotspot(hspot_d[i]));
  
  for(vector<liquid_data>::size_type i=0; i < liquid_d.size(); i++) 
    liquid.push_back(new Liquid(liquid_d[i]));
  
  Pingu::set_colmap(colmap);
  Pingu::set_map(map);
  Pingu::SetParticleHolder(&particle);
  Trap::SetParticleHolder(&particle);
  Entrance::SetParticleHolder(&particle);

  //world_obj.push_back(map);

  // Push all objects to world_obj vector
  for(vector<hotspot_data>::size_type i = 0; i < hotspot.size(); i++)
    {
      if (hotspot[i]-> z_pos <= 0)
	world_obj_bg.push_back(hotspot[i]);
      else 
	world_obj_fg.push_back(hotspot[i]);
    }

  for(vector<exit_data>::size_type i=0; i < exits.size(); i++)
    { 
      if (exits[i]->z_pos <= 0)
	world_obj_bg.push_back(exits[i]);
      else 
	world_obj_fg.push_back(exits[i]);
    }  
  
  for(vector<entrance_data>::size_type i=0; i < entrance.size(); ++i)
    {
      if (entrance[i]->z_pos <= 0)
	world_obj_bg.push_back(entrance[i]);
      else 
	world_obj_fg.push_back(entrance[i]);
    }

  for(vector<liquid_data>::size_type i=0; i < liquid_d.size(); ++i)
    {
      if (liquid[i]->z_pos <= 0)
	world_obj_bg.push_back(liquid[i]);
      else 
	world_obj_fg.push_back(liquid[i]);
    }
  
  for(vector<trap_data>::size_type i=0; i < traps.size(); ++i) 
    {
      if (traps[i]->z_pos <= 0)
	world_obj_bg.push_back(traps[i]);
      else 
	world_obj_fg.push_back(traps[i]);
    }

  world_obj_fg.push_back(&pingus);

  // After all objects are in world_obj, sort them to there z_pos
  stable_sort(world_obj_bg.begin(), world_obj_bg.end(), WorldObj_less());
  stable_sort(world_obj_fg.begin(), world_obj_fg.end(), WorldObj_less());

  // Drawing all world objs to the colmap
  for(vector<WorldObj*>::iterator obj = world_obj_bg.begin(); obj != world_obj_bg.end(); obj++)
    (*obj)->draw_colmap(colmap);

  for(vector<WorldObj*>::iterator obj = world_obj_fg.begin(); obj != world_obj_fg.end(); obj++)
    (*obj)->draw_colmap(colmap);
  
  // Setup the gravity force
  // Clear all old forces
  ForcesHolder::clear_all_forces();
  ForcesHolder::add_force(GravityForce(grav));
}

PinguHolder*
World::get_pingu_p(void)
{
  return &pingus;
}

int
World::get_width(void)
{
  assert(map);
  return map->get_width();  
}

int
World::get_height(void)
{
  assert(map);
  return map->get_height();
}

int
World::get_time(void)
{
  if (exit_time) // There is a time limit
    {
      return exit_time - GameTime::get_time();
    }
  else // No timelimit given, lets run forever
    {
      return GameTime::get_time();
    }
}

void 
World::armageddon(void)
{
  do_armageddon = true;
  armageddon_count = pingus.begin();
}

bool
World::is_finished(void)
{
  // Return true if the world is finished and some time has passed
  if (exit_time < GameTime::get_time()) 
    {
      return true;
    } 
  else 
    {
      return false;
    }
}

ColMap*
World::get_colmap()
{
  return colmap;
}

PLF*    
World::get_plf()
{
  return plf;
}

void
World::set_action_holder(ActionHolder* a)
{
  action_holder = a;
}

/* EOF */
