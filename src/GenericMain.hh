//  $Id: GenericMain.hh,v 1.4 2001/11/29 10:47:44 grumbel Exp $
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

#ifndef GENERICMAIN_HH
#define GENERICMAIN_HH

#include <ClanLib/core.h>
#include <ClanLib/application.h>

class AbstractMain
{
public:
  virtual char* get_title() =0;
  virtual int   main (int argc, char* argv[]) =0;
};

class GenericMain : public CL_ClanApplication
{
private:
  AbstractMain* main_obj;
  
public:
  char* get_title();
  int   main (int argc, char* argv[]);
};

#endif

/* EOF */
