//  $Id: PingusLevelDesc.hh,v 1.10 2001/04/13 13:45:09 grumbel Exp $
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

#ifndef PINGUSLEVELDESC_HH
#define PINGUSLEVELDESC_HH

#include <ClanLib/core.h>

#include "Controller.hh"
#include "MultiLineText.hh"
#include "PLF.hh"

///
class PingusLevelDesc
{
private:
  ///
  CL_Surface background;
  ///
  CL_Surface level;
  ///
  CL_Font* font;
  ///
  CL_Font* title;
  ///
  boost::shared_ptr<PLF>    plf;
  
  ///
  MultiLineText description;
  ///
  boost::shared_ptr<Controller> controller;
  ///
  std::string         levelname;
public:
  ///
  enum LoadingStatus { LOADING, FINISHED };
  ///
  PingusLevelDesc(boost::shared_ptr<PLF>,  boost::shared_ptr<Controller>);
  
  ///
  void draw(PingusLevelDesc::LoadingStatus status);
};

#endif

/* EOF */
