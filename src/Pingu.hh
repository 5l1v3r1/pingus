//  $Id: Pingu.hh,v 1.32 2001/08/02 21:51:02 grumbel Exp $
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

#ifndef PINGU_HH
#define PINGU_HH

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include "boost/smart_ptr.hpp"

#include "StringConverter.hh"
#include "WorldObj.hh"
#include "PinguMap.hh"
#include "Direction.hh"
#include "PinguEnums.hh"
#include "Sprite.hh"
#include "PinguAction.hh"

// Forward declarations
class ActionHolder;
class PinguAction; 

/** The class for managing one of the many penguins which are walking
    around in the World. All actions are handled by PinguAction
    objects. */
class Pingu : public WorldObj
{
protected:
  friend class PinguAction;
  ///
  boost::shared_ptr<PinguAction> action;
  ///
  boost::shared_ptr<PinguAction> sec_action;
  ///
  std::vector<boost::shared_ptr<PinguAction> > persist;

  /** The uniq id of the Pingu, this is used to refer to the Pingu in
      a demo file or in a network connection */
  int id;

  /** Static id_counter, which holds the id last pingu, which
      got created. */
  static int id_counter;

  ///
  CL_Font* font;

  /** @name surfaces that represent the Pingu in different situations */
  //@{
  ///
  Sprite walker; 
  ///
  Sprite faller;
  ///
  Sprite tumble;
  //@}

  ///
  int action_time;

  ///
  PinguStatus status;
  ///
  PinguEnvironment environment;
  ///
  int falling;

  ///
  int owner_id;

public:
  // The postion of the pingu (CL_Vector::z is always zero)
  CL_Vector pos;
  ///
  Direction direction;
  /// Current velocity
  CL_Vector velocity; 

  /** Creates a new Pingu at the given coordinates
      @param pos The start position of the pingu
      @param owner The owner id of the pingu (used for multiplayer) */
  Pingu(const CL_Vector& pos, int owner = 0);
  
  /** Destruct the pingu... */
  ~Pingu();
  
  /** @return The world the pingu lives in */
  static World* get_world();

  /** Return the logical pingus position, this is the position which
      is used for collision detection to the ground (the pingus
      feet) */
  CL_Vector get_pos () { return pos; }

  /** Returns the visible position of the pingu, the graphical center
      of the pingu. */
  CL_Vector get_center_pos ();

  /** Returns the x position of the pingu
   * For backward comp. only
   */
  int  get_x(void);

  /** Returns the y position of the pingu
      For backward comp. only */
  int  get_y(void);
  ///
  PinguEnvironment get_environment(); 

  /// Check if the pingu is still alive
  bool is_alive(void);

  /// Return the status of the pingu
  PinguStatus get_status(void) const; 

  ///
  PinguStatus set_status(PinguStatus);

  /// Returns the unique id of the pingu
  int  get_id(void); 
  
  /// Set's the unique id of the pingu
  int  set_id(int);
  
  /// Set the pingu to the given coordinates
  void set_pos(int x, int y);

  /// Set the pingu to the given coordinates
  void set_pos(const CL_Vector& arg_pos);
 
  // Set the pingu in the gives direction
  void set_direction(Direction d);

  ///
  int  set_action(boost::shared_ptr<PinguAction>);
  ///
  void set_action (const std::string action_name);
  ///
  int  set_paction(boost::shared_ptr<PinguAction>);

  ///
  boost::shared_ptr<PinguAction> get_action();

  /** Returns the `color' of the colmap in the walking direction 
      Examples: 
      (0, -1) is the pixel under the pingu
      (1, 0)  is the pixel in front of the pingu
  */
  int  rel_getpixel(int x, int y);

  /** Let the pingu catch another pingu, so that an action can be
      applied (i.e. let a blocker change the direction f another
      pingu) */
  void catch_pingu(Pingu* pingu);

  /** Returns true if the pingu needs to catch another pingu */
  bool need_catch();
  
  ///
  void draw_offset(int x, int y, float s = 1.0);
  ///
  void apply_force(CL_Vector);

  ///
  void update(float delta);
  ///
  void update_persistent(float delta);
  ///
  void update_normal(float delta);
  ///
  void update_falling(float delta);
  ///
  void update_walking(float delta);

  /** Indicate if the pingu's speed is above the deadly velocity */
  bool is_tumbling () const;

  /** @return The owner_id of the owner, only used in multiplayer
      configurations, ought to bed single player */
  int get_owner ();

  ///
  bool   is_over(int x, int y);
  ///
  bool   is_inside (int x1, int y1, int x2, int y2);
  ///
  double dist(int x, int y);
};

#endif /* PINGU_HH */

/* EOF */
