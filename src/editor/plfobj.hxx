//  $Id: plfobj.hxx,v 1.8 2002/09/04 14:55:12 torangan Exp $
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

#ifndef HEADER_PINGUS_EDITOR_PLFOBJ_HXX
#define HEADER_PINGUS_EDITOR_PLFOBJ_HXX

#include "../liquid_data.hxx"
#include "../entrance_data.hxx"
#include "../exit_data.hxx"
#include "../trap_data.hxx"
#include "sprite_editorobj.hxx"

class EntranceObj : public SpriteEditorObj,
		    public EntranceData
{
public:
  EntranceObj (const EntranceData&);

  EditorObj* duplicate ();
  void write_xml (std::ostream& xml) { EntranceData::write_xml (xml); }
  std::string status_line ();
  Pingus::Editor::PropertyFrame* get_gui_dialog (CL_Component* parent);
  
private:
  EntranceObj (const EntranceObj&);
  EntranceObj operator= (const EntranceObj&);
};

class ExitObj : public SpriteEditorObj,
		public ExitData
{
public:
  ExitObj (const ExitData&);

  EditorObj* duplicate();
  void write_xml(std::ostream& xml) { ExitData::write_xml (xml); }
  std::string  status_line();
  
private:
  ExitObj (const ExitObj&);
  ExitObj operator= (const ExitObj&);
};


class TrapObj : public SpriteEditorObj,
		protected TrapData
{
private:
  int frame;
public:
  TrapObj (const TrapData&);

  EditorObj* duplicate ();
  void write_xml (std::ostream& xml) { TrapData::write_xml (xml); }
  void draw (EditorView * view);
  std::string status_line ();
  
private:
  TrapObj (const TrapObj&);
  TrapObj operator= (const TrapObj&);
};

class LiquidObj : public SpriteEditorObj,
		  protected LiquidData
{
public:
  LiquidObj(const LiquidData& data);

  EditorObj* duplicate();
  void draw (EditorView * view);
  void draw_mark (EditorView * view);
  void save(std::ostream& plf, std::ofstream* psm);
  void write_xml(std::ostream& xml) { LiquidData::write_xml (xml); }
  std::string  status_line();

  int get_width () { return  sprite.get_width () * width; }

  void make_larger ();
  void make_smaller ();
  
private:
  LiquidObj (const LiquidObj&);
  LiquidObj operator= (const LiquidObj&);
};

#endif

/* EOF */


