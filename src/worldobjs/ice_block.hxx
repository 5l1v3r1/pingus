//  $Id: ice_block.hxx,v 1.7 2002/08/23 15:49:57 torangan Exp $
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

#ifndef HEADER_PINGUS_WORLDOBJS_ICE_BLOCK_HXX
#define HEADER_PINGUS_WORLDOBJS_ICE_BLOCK_HXX

#include "../worldobj_data.hxx"
#include "../editor/sprite_editorobj.hxx"

class WorldObj;

class IceBlockData : public WorldObjData
{
public:
  /// The upper/left position  of the iceblock's
  CL_Vector pos;
  /** The number of iceblocks, only complete blocks are supported */
  int width;

  int last_contact;

  IceBlockData ();
  IceBlockData (xmlDocPtr doc, xmlNodePtr cur);

  /** Write the content of this object formatted as xml to the given
      stream */
  void write_xml(std::ostream& xml);
  
  /** Create an WorldObj from the given data object */
  WorldObj* create_WorldObj ();

  /** Create an EditorObj from the given data object */
  EditorObjLst create_EditorObj ();
  
private:
  IceBlockData (const IceBlockData&);
  IceBlockData operator= (const IceBlockData&);
};

class IceBlock : public IceBlockData, 
		 public WorldObj
{
private:
  CL_Surface block_sur;
  float thickness;
  bool is_finished;
public:
  IceBlock (const IceBlockData& data);

  float get_z_pos () const { return 100; }
  void draw_colmap ();
  void draw_offset (int x, int y, float s = 1.0);
  void update (float delta);
  
private:
  IceBlock (const IceBlock&);
  IceBlock operator= (const IceBlock&);
};


class EditorIceBlockObj : public IceBlockData,
			  public SpriteEditorObj			  
{
private:
  
public:
  EditorIceBlockObj (const IceBlockData& data);

  /** Create the object with resonable defaults */
  static EditorObjLst create (const CL_Vector& pos);

  void write_xml(std::ostream& xml) { IceBlockData::write_xml (xml); }
  EditorObj* duplicate();
  std::string status_line();
  
private:
  EditorIceBlockObj (const EditorIceBlockObj&);
  EditorIceBlockObj operator= (const EditorIceBlockObj&);
};

#endif

/* EOF */



