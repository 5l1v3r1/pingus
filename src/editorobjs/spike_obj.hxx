//  $Id: spike_obj.hxx,v 1.12 2003/10/18 23:17:28 grumbel Exp $
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

#ifndef HEADER_PINGUS_EDITOROBJS_SPIKE_OBJ_HXX
#define HEADER_PINGUS_EDITOROBJS_SPIKE_OBJ_HXX

#include "../editor/sprite_editorobj.hxx"

namespace Pingus {

namespace WorldObjsData {
class SpikeData;
} // namespace WorldObjsData

namespace EditorObjs {

class SpikeObj : public EditorNS::SpriteEditorObj
{
private:
  WorldObjsData::SpikeData* const data;

public:
  SpikeObj (const WorldObjsData::SpikeData& data_);
  ~SpikeObj ();

  static EditorNS::EditorObjLst create (const Vector& pos);

  EditorNS::EditorObj* duplicate ();
  
  void write_xml (std::ostream& xml);
  void draw (EditorNS::EditorView* view);

  std::string status_line ();
  EditorNS::PropertyFrame* get_gui_dialog(EditorNS::Editor*) { return 0; }
private:
  SpikeObj (const SpikeObj&);
  SpikeObj& operator= (const SpikeObj&);
};

} // namespace EditorObjs
} // namespace Pingus

#endif

/* EOF */
