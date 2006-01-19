//  $Id: level_objs.hxx,v 1.00 2005/11/15 23:41:12 Jave27 Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_PINGUS_EDITOR_LEVEL_OBJS_HXX
#define HEADER_PINGUS_EDITOR_LEVEL_OBJS_HXX

#include <ClanLib/Display/sprite.h>
#include "../vector.hxx"
#include "../res_descriptor.hxx"
#include <string>

namespace Pingus {

	class XMLFileWriter;
	class DrawingContext;

namespace Editor {

	const unsigned HAS_TYPE = 1;
	const unsigned HAS_SPEED = 2;
	const unsigned HAS_PARALLAX = 4;
	const unsigned HAS_WIDTH = 8;
	const unsigned HAS_OWNER = 16;
	const unsigned HAS_COLOR = 32;
	const unsigned HAS_SCROLL = 64;
	const unsigned HAS_PARA = 128;
	const unsigned HAS_STRETCH = 256;
	const unsigned HAS_DIRECTION = 512;
	const unsigned HAS_RELEASE_RATE = 1024;
	const unsigned HAS_SURFACE = 2048;
	// HAS_SURFACE_FAKE means it has a generic image in the editor, but isn't saved.
	const unsigned HAS_SURFACE_FAKE = 4096;
	const unsigned CAN_ROTATE = 8192;

	/** Returns a number representing which attributes this object possesses */
	inline unsigned int get_attributes(std::string obj_type)
	{
		unsigned val;
		if (obj_type == "groundpiece")
			val = HAS_TYPE | HAS_SURFACE | CAN_ROTATE;
		else if (obj_type == "hotspot")
			val = HAS_SPEED | HAS_PARALLAX | HAS_SURFACE | CAN_ROTATE;
		else if (obj_type == "liquid")
			val = HAS_SPEED | HAS_WIDTH | HAS_SURFACE;
		else if (obj_type == "surface-background")
			val = HAS_COLOR | HAS_STRETCH | HAS_PARA | HAS_SCROLL | HAS_SURFACE;
		else if (obj_type == "entrance" || obj_type == "woodthing")
			val = HAS_TYPE | HAS_DIRECTION | HAS_RELEASE_RATE | HAS_OWNER | HAS_SURFACE_FAKE;
		else if (obj_type == "exit")
			val = HAS_OWNER | HAS_SURFACE;
		else
			val = 0;

		return val;
	}

	class LevelImpl;

/** Generic Level Object (groundpiece, sign, etc.)  Only special objects will have
		to inherit from this class - most objects will be able to use this class alone */
	class LevelObj
{
protected:
	/** Sprite used to draw this object */
	CL_Sprite sprite;

	/** Level to which this object belongs */
	LevelImpl* level;

	/** Resource Desciptor of this object */
	ResDescriptor desc;

	/** Location of this object in the World */
	Vector pos;

	/** Location of this object before moving it around */
	Vector orig_pos;

	/** Name of the section header for this object (hotspot, groundpiece, etc.) */
	std::string section_name;

	/** Optional type field for certain objects */
	std::string object_type;

	/** Optional speed field for certain objects */
	int speed;

	/** Optional parallax field for certain objects */
	float parallax;

	/** Optional width field for certain objects */
	int width;

	/** Optional owner id field for certain objects */
	int owner_id;

	/** Optional release rate field for certain objects (entrances) */
	int release_rate;

	/** Optional direction field for certain objects */
	std::string direction;

	/** Optional scroll field in the x direction for certain objects */
	float scroll_x;

	/** Optional scroll field in the y direction for certain objects */
	float scroll_y;

	/** Optional stretch field in the x direction for certain objects */
	bool stretch_x;

	/** Optional stretch field in the y direction for certain objects */
	bool stretch_y;

	/** Optional field for keeping the aspect ratio of stretched objects */
	bool keep_aspect;

	/** Optional parallax field in the x direction for certain objects */
	float para_x;

	/** Optional parallax field in the y direction for certain objects */
	float para_y;

	/** Optional color field for certain objects */
	CL_Colorf color;
	
	/** Optional translation origin of the sprite */
	CL_Origin origin;

	/** Number representing which attributes this object possesses */
	unsigned attribs;

	/** Marks if this object has been deleted or not */
	bool removed;

	/** Marks is this object is currently selected */
	bool selected;

	/** Loads any generic images necessary for objects with HAS_FAKE_SURFACE */
	void load_generic_surface();

	/** Write any additional properties to the XML file for this type */
	virtual void write_extra_properties(XMLFileWriter& xml) { }


/////////////////////////////////////////////////////////
/// Retrieve info
public:
	/** Retrieve the object's position */
	Vector get_pos() const { return pos; }
	Vector get_orig_pos() const { return orig_pos; }

	/** Retrieve this object's attribute number */
	unsigned get_attribs() const { return attribs; }

	/** Retrieve the object's resource name */
	ResDescriptor get_res_desc() const { return desc; }

	/** Retrieve the name of the section header for this object */
	std::string get_section_name() const { return section_name; }

	/** Retrieve the object's type */
	std::string get_type() const { return object_type; }

	/** Retrieve the object's speed */
	int get_speed() const { return speed; }

	/** Retrieve the object's release rate (entrances) */
	int get_release_rate() const { return release_rate; }

	/** Retrive the object's parallax (is this even used???) */
	float get_parallax() const { return parallax; }

	/** Retrieve the object's owner */
	int get_owner() const { return owner_id; }

	/** Retrieve the object's width */
	int get_width() const { return width; }

	/** Retrieve the object's color */
	CL_Colorf get_color() const { return color; }

	/** Returns true if the object is stretched in the x direction */
	bool get_stretch_x() const { return stretch_x; }

	/** Returns true if the object is stretched in the y direction */
	bool get_stretch_y() const { return stretch_y; }

	/** Returns true if the object is to maintain it's aspect ratio if stretched */
	bool get_aspect() const { return keep_aspect; }

	/** Retrive the objects scroll value in the x direction */
	float get_scroll_x() const { return scroll_x; }

	/** Retrive the objects scroll value in the y direction */
	float get_scroll_y() const { return scroll_y; }

	/** Returns the parallax speed multiplier in the x direction */
	float get_para_x() const { return para_x; }

	/** Returns the parallax speed multiplier in the y direction */
	float get_para_y() const { return para_y; }

	bool is_selected() { return selected; }

	/** Retrieve the object's direction */
	std::string get_direction() { return direction; }


/////////////////////////////////////////////////////////
/// Operations
public:
	/** Set the object's position */
	void set_pos(const Vector p) { pos = p; }
	
	/** Original position of the objects before being dragged around */
	void set_orig_pos(const Vector p) { orig_pos = p; }

	/** Set the object's resource name */
	void set_res_desc(const ResDescriptor d);

	/** Set the object's modifier */
	void set_modifier(const std::string m);

	/** Set the object's section header name */
	void set_section_name(const std::string sn) { section_name = sn; }

	/** Set the object's type */
	void set_type(const std::string t) { object_type = t; }

	/** Set the object's speed */
	void set_speed(const int s) { speed = s; }

	/** Set the objects release rate */
	void set_release_rate(const int r) { release_rate = r; }

	/** Set the object's parallax */
	void set_parallax(const float para) { parallax = para; }

	/** Set the object's width */
	void set_width(const int w) { width = w; }

	/** Set the object's owner_id */
	void set_owner(const int id) { owner_id = id; }

	/** Set the object's scroll rate in the x direction */
	void set_scroll_x(const float s) { scroll_x = s; }

	/** Set the object's scroll rate in the y direction */
	void set_scroll_y(const float s) { scroll_y = s; }

	/** Set the objects stretch in the x direction value */
	void set_stretch_x(const bool s);

	/** Set the objects stretch in the y direction value */
	void set_stretch_y(bool s);

	/** Set whether or not the object should maintain it's aspect ratio when stretched */
	void set_aspect(const bool a);

	/** Set the objects color if applicable */
	void set_color(const CL_Colorf c) 
	{ color.alpha = c.alpha; color.blue = c.blue;  
		color.green = c.green; color.red = c.red; }

	/** Set the object's parallax scroll multiplier in the x direction */
	void set_para_x(const float p) { para_x = p; }

	/** Set the object's parallax scroll multiplier in the y direction */
	void set_para_y(const float p) { para_y = p; }

	/** Set the object's direction if applicable */
	void set_direction(const std::string d) { direction = d; }

	/** Soft delete of the object (needed for Undo action) */
	void remove() { removed = true; }

	/** Undelete this object if it's been removed */
	void unremove() { removed = false; }

	/** Select or unselect this object */
	void select() { selected = true; }
	void unselect() { selected = false; }

	/** Write basic properties to the XML file for this type */
	virtual void write_properties(XMLFileWriter &xml);

	/** Call when the sprite needs to be reloaded */
	void refresh_sprite();

	/** Draws the sprite with the modifier applied */
	virtual void draw(DrawingContext &gc);

	/** Returns true if the mouse is hovering over this object */
	virtual bool is_at (int x, int y);

	/** Default Constructor */
	LevelObj(const std::string obj_name, LevelImpl* level_);

	/** Destructor */
	virtual ~LevelObj() { }

private:
	LevelObj (const LevelObj&);
  LevelObj& operator= (const LevelObj&);

};	// LevelObj class

}		// Editor namespace
}		// Pingus namespace

#endif

/* EOF */
