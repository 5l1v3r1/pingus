//  $Id: IceBlock.hh,v 1.8 2001/04/21 10:55:17 grumbel Exp $
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

#ifndef ICEBLOCK_HH
#define ICEBLOCK_HH

#include <ClanLib/core.h>
#include "../boost/smart_ptr.hpp"
#include "../WorldObj.hh"
#include "../WorldObjData.hh"
#include "../editor/EditorWorldObj.hh"

class IceBlockData : public WorldObjData
{
public:
  /// The upper/left position  of the iceblock's
  CL_Vector pos;
  /** The number of iceblocks, only complete blocks are supported */
  int width;

  IceBlockData ();

  /** Writte the content of this object formated as xml to the given
      stream */
  virtual void write_xml(ofstream* xml);
  ///
  static boost::shared_ptr<WorldObjData> create(xmlDocPtr doc, xmlNodePtr cur);
};

class IceBlock : public IceBlockData, 
		 public WorldObj
{
private:
  CL_Surface block_sur;
  float thickness;
  bool is_finished;
public:
  ///
  IceBlock (WorldObjData* data);
  ///
  virtual ~IceBlock ();
  ///
  virtual int  get_z_pos() const { return 100; }
  ///
  virtual void draw_colmap();
  ///
  virtual void draw_offset(int x, int y, float s = 1.0);
  ///
  virtual void update(float delta);
};


class EditorIceBlockObj : public EditorWorldObj, 
			  public IceBlockData
{
private:
  
public:
  EditorIceBlockObj();
  EditorIceBlockObj (WorldObjData* obj);
  virtual ~EditorIceBlockObj ();

  static std::list<boost::shared_ptr<EditorObj> > create (WorldObjData* obj);

  /** Create the object with resonable defaults */
  static std::list<boost::shared_ptr<EditorObj> > create (const CL_Vector& pos);

  virtual void save_xml (std::ofstream* xml);
  virtual std::string status_line();
};

#endif

/* EOF */
