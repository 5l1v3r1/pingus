//  $Id: surface_button.hxx,v 1.2 2002/06/24 22:52:57 grumbel Exp $
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

#ifndef HEADER_PINGUS_SURFACE_BUTTON_HXX
#define HEADER_PINGUS_SURFACE_BUTTON_HXX

#include <string>
#include "worldmap/manager.hxx"
#include "multiplayer_config.hxx"
#include <ClanLib/Display/Display/surface.h>

class PingusMenu;

/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */
/* !FIXME! All this should be rewritten... */


///
class SurfaceButton
{
protected:
  CL_Surface surface;
  CL_Surface surface_p;
  CL_Font*    font;
  CL_Font*    font_large;
  bool is_mouse_over;
  
  int x_pos;
  int y_pos;

  std::string desc;
  std::string line1;
  std::string line2;
public:
  SurfaceButton();
  virtual ~SurfaceButton();
  
  void draw();
  bool mouse_over();
  virtual void on_click() = 0;
};

///
class PlayButton : public SurfaceButton
{
private:
  PingusMenu* menu;
public:
  PlayButton(PingusMenu* menu);
  virtual ~PlayButton();
  void on_click();
};

///
class OptionsButton : public SurfaceButton
{
private:
  PingusMenu* menu;
public:
  OptionsButton(PingusMenu* menu);
  virtual ~OptionsButton();

  void on_click();
};

///
class QuitButton : public SurfaceButton
{
private:
  PingusMenu* menu;
public:
  QuitButton(PingusMenu*);
  virtual ~QuitButton();

  void on_click();
};

///
class LoadButton : public SurfaceButton
{
private:
  ///  FileSelector file;
public:
  LoadButton();
  ///
  virtual ~LoadButton();
  ///
  void on_click();
};

///
class EditorButton : public SurfaceButton
{
private:
  PingusMenu* menu;

public:
  ///
  EditorButton(  PingusMenu* menu);
  ///
  virtual ~EditorButton();
  ///
  void on_click();
  void load_level(const std::string& str);
};

class StoryButton : public SurfaceButton
{
private:
  PingusMenu* menu;
  Pingus::WorldMapManager worldmap_manager;
public:
  StoryButton(PingusMenu* menu);
  ~StoryButton();
  void on_click();
};

///
class ThemeButton : public SurfaceButton
{
private:
  PingusMenu* menu;
public:
  ThemeButton(PingusMenu* menu);
  void on_click();
};

///
class MultiplayerButton : public SurfaceButton
{
private:
  MultiplayerConfig multiplayer_config;
  PingusMenu* menu;
public:
  ///
  MultiplayerButton(PingusMenu* menu);
  ///
  virtual ~MultiplayerButton();
  ///
  void on_click();
};

#endif

/* EOF */



