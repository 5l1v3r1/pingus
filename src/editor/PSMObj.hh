// $Id: PSMObj.hh,v 1.7 2000/07/30 01:47:37 grumbel Exp $
//
// Pingus - A free Lemmings clone
// Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef PSMOBJ_HH
#define PSMOBJ_HH

#include <cstdio>
#include "EditorObj.hh"
#include "../SurfaceData.hh"

///
class PSMObj : public EditorObj
{
private:
  ///
  SurfaceData::Type type;
public:
  ///
  PSMObj(SurfaceData data);
  ///
  PSMObj(const PSMObj&);
  ///
  virtual ~PSMObj();

  ///
  virtual void save(std::ofstream* plf, std::ofstream* psm);
  ///
  virtual void save_xml(std::ofstream* xml);
  ///
  EditorObj*   duplicate();
  ///
  std::string obj_type() { return "Groundpiece"; }///
;
  ///
  std::string status_line();
}///
;

#endif

/* EOF */


