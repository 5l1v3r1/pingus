//  $Id: PinguAction.hh,v 1.23 2001/08/05 23:50:14 grumbel Exp $
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

#ifndef PINGU_ACTION_HH
#define PINGU_ACTION_HH

#include <ClanLib/core.h>
#include "boost/smart_ptr.hpp"

#include "WorldObj.hh"
#include "AnimCounter.hh"
#include "PinguEnums.hh"
#include "Pingu.hh"
#include "my_gettext.hh"

///
class Pingu;
class ActionHolder;

enum ActionType
{
  ONCE = 1<<1,
  WALL = 1<<2,
  FALL = 1<<3
};

// This class provides an abstract interface for pingu actions. It is 
// used to inherit classes which represent the actions. The actions
// are stored in a seperate library, have a look in actions/ for some
/// examples.
class PinguAction : public WorldObj
{
protected:
  /** A pointer to the pingu, which hold the action. */
  Pingu*      pingu;

public:
  /** Indicate if the action should be canceled at the next possible
      point. FIXME: Only keeped public for lazyness. */
  bool is_finished;

  PinguAction();
  virtual ~PinguAction();

  /// Gives the PinguAction class access to the data of the Pingu.
  void set_pingu(Pingu*);

  /// Get the pixel from the colmap, relative to the pingu position. 
  int  rel_getpixel(int x, int y);

  /** Returns the enviroment, used to check if an action can be
      applied. */
  virtual PinguEnvironment get_environment() const =0;
  
  /** Used to load all data, which is needed by the action, its
      seperated and called in set_pingu(), because some data will be
      only valid if set_pingu() is called. */
  virtual void  init(void) {};

  /// The "AI" of the pingu. The walker and faller is in class Pingu
  virtual void  update(float delta) = 0;

  /** Draws the surfaced defined by the action, can be overwritten if
      the action needs a more complicated way of drawing. */
  virtual void  draw_offset(int x, int y, float s) =0;

  /// Returns the action type
  virtual ActionType get_type(void);

  /// The name of the action, used in PinguInfo.hh
  virtual std::string get_name(void) const =0;
  
  /// Catch another pingu and act on it (see blocker.hh)
  virtual bool  need_catch();

  ///
  virtual void  catch_pingu(Pingu*) { /* do nothing */}

  /// The time the action needs to get activated (see bomber.cc)
  virtual int   activation_time() { return -1; };

  /** Return true if the pingu can be catched with the mouse and
      another action can be applied, false otherwise (exiter,
      splashed, etc.) */
  virtual bool catchable () { return true; }
};

class PinguActionFactory
{  
private:
  static std::map<std::string, PinguActionFactory*>  actions;
  
protected:
  PinguActionFactory (std::string);
  virtual ~PinguActionFactory ();
  virtual PinguAction* create () =0; 

public:
  static  boost::shared_ptr<PinguAction> create (std::string action_name);
};

// Now follows a little Factory Macro
//
#define REGISTER_PINGUACTION(f_class, a_class, name)   \
class f_class : public PinguActionFactory              \
{                                                      \
public:                                                \
  f_class () : PinguActionFactory (name) {             \
     /*std::cout << _("Name: ") << name << std::endl;*/\
  }                                                    \
  PinguAction* create () {                             \
    return new a_class ();                             \
  }                                                    \
}

#endif /* PINGU_ACTION_HH */

/* EOF */
