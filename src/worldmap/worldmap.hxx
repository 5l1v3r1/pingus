//  $Id: worldmap.hxx,v 1.5 2002/08/03 09:59:23 grumbel Exp $
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

#ifndef HEADER_PINGUS_WORLDMAP_WORLDMAP_HXX
#define HEADER_PINGUS_WORLDMAP_WORLDMAP_HXX

#include "stat.hxx"

class CL_Key;
class CL_Font;
class CL_InputDevice;
class PingusWorldMapPingus;

namespace Pingus
{
  namespace WorldMap
  {

    /** A class for loading, displaying and managing the worldmap. */
    class WorldMap
    {
    private:
      CL_Surface background;
      CL_Font*   font;

      Sprite green_dot;
      Sprite red_dot;
      Sprite dot_border;
      Sprite green_flag; 

      //Graph<PingusWorldMapNode>* graph;
      Graph graph_data;
      typedef Graph::iterator GraphIter;

      PingusWorldMapPingus* pingus;
  
      bool catch_input;

      bool do_quit;
      boost::shared_ptr<Pingus::WorldMap::Node> last_node;
      typedef boost::shared_ptr<Pingus::WorldMap::Node> NodePtr;
      unsigned int last_node_time;
  
      boost::shared_ptr<PingusWorldMapStat> stat;
    public:
      /** Load a worldmap from a given worldmap description file */
      WorldMap (std::string filename);

      /** Destruct the worldmap */
      ~WorldMap ();

      /** Launch the level at the given node
	  @param node The current node from which the level should be started */
      void start_level (Pingus::WorldMap::Node* node);

      /** Start up the music and other things that need only to me run
	  once on startup of a new WorldMap */
      void init ();

      /** Save the current status to a file */
      void save ();
  
      /** React on button press:
	  - calculate which level was clicked
	  - calculate the shortest path
	  - let the pingu walk */
      void on_primary_button_press (int x, int y);

      /** Disable all event catching */
      void disable_button_events ();
  
      /** Enable all event catching */
      void enable_button_events ();
  
      /** Draw the world worldmap */
      void draw ();
  
      /** Returns true if the worldmap is finished and the
	  PingusWorldMapManager can quit */
      bool do_exit ();

      /** Let the woldmap do some stuff, like animating smoke, playing
	  sounds or reacting on special events */
      void update (float delta);

      /** Returns a pointer to the node under the given coordinates */
      NodePtr get_node (int x, int y);
  
      /** Callculate the offset which is used for drawing and collision
	  detection. The offset will be used for scrolling when the
	  background is larger than the screen. 
	  @return the currently used draw offset */
      CL_Vector get_offset ();

      /** Set the pingu to the given node with 'id' */
      void set_pingus (int node_id);
    };

  }
}

#endif

/* EOF */
