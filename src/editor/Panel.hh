//  $Id: Panel.hh,v 1.9 2002/06/10 11:00:28 torangan Exp $
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

#ifndef PANEL_HH
#define PANEL_HH

#include <vector>

class CL_Font;
class Editor;

///
class EditorEvent;

class PanelIcon
{
protected:
  CL_Font* font;
  ///
  CL_Surface sur;
  ///
  CL_Surface button;
  ///
  CL_Surface button_pressed;
  ///
  std::string tooltip;
  /// 
  unsigned int mouse_over_time;
public:
  ///
  static Editor* editor;
  ///
  PanelIcon();
  ///
  virtual ~PanelIcon();
  ///
  void start();
  ///
  void put_screen(int x, int y);
  ///
  virtual void on_click();
}///
;

///
class Panel
{
private:
  ///
  bool is_init;
  ///
  std::vector<PanelIcon*> buttons;
  ///
  std::vector<PanelIcon*>::iterator pressed_button;
  ///
  Editor* editor;
  ///
  CL_Surface logo;

public:
  ///
  Panel();
  ///
  ~Panel();

  ///
  void draw();
  ///
  void init();
  ///
  void on_click();
  ///
  void on_release();
  ///
  bool mouse_over(int x, int y);
  ///
  void set_editor(Editor* e);
}///
;

#endif

/* EOF */



