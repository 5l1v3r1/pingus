//  $Id: waiter.hxx,v 1.15 2003/10/18 23:17:27 grumbel Exp $
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

#ifndef HEADER_PINGUS_ACTIONS_WAITER_HXX
#define HEADER_PINGUS_ACTIONS_WAITER_HXX

#include "../pingu_action.hxx"

namespace Pingus {
namespace Actions {

/** A Waiting action for the bridger, it gets activated when the
    bridger is out of bridges. It then waits two seconds (meanwhile doing a
    funny animation) and then he changes back to a normal walker. */
class Waiter : public PinguAction
{
private:
  float countdown;
  CL_Sprite sprite;

public:
  Waiter (Pingu*);

  ActionName get_type () const { return Actions::Waiter; }

  void draw (DrawingContext& gc);
  void update ();

private:
  Waiter (const Waiter&);
  Waiter& operator= (const Waiter&);
};

} // namespace Actions
} // namespace Pingus

#endif

/* EOF */
