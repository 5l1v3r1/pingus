//  $Id: smasher_obj.hxx,v 1.4 2002/09/10 14:33:07 grumbel Exp $
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

#ifndef HEADER_PINGUS_EDITOROBJS_SMASHER_OBJ_HXX
#define HEADER_PINGUS_EDITOROBJS_SMASHER_OBJ_HXX

#include "../editor/sprite_editorobj.hxx"

namespace WorldObjsData {
  class SmasherData;
}

namespace EditorObjs {

class SmasherObj : public SpriteEditorObj
{
  private:
    int frame;
    WorldObjsData::SmasherData* const data;
  
  public:
    SmasherObj (const WorldObjsData::SmasherData& data_);
   ~SmasherObj ();

    static EditorObjLst create (const CL_Vector& pos);
   
    EditorObj* duplicate ();
    
    void write_xml (std::ostream& xml);
    void draw (EditorView* view);
    
    std::string status_line ();
  
  private:
    SmasherObj (const SmasherObj&);
    SmasherObj operator= (const SmasherObj&);
};

}

#endif

/* EOF */
