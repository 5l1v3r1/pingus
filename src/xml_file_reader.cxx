//  $Id$
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#include <ClanLib/Display/color.h>
#include <ClanLib/Core/Math/size.h>
#include <ClanLib/Core/XML/dom_element.h>
#include <ClanLib/Core/XML/dom_node_list.h>
#include <ClanLib/Core/XML/dom_named_node_map.h>
#include <ClanLib/Core/System/clanstring.h>
#include "file_reader_impl.hxx"
#include "vector.hxx"
#include "res_descriptor.hxx"
#include "xml_file_reader.hxx"

namespace Pingus {

class XMLFileReaderImpl : public FileReaderImpl
{
private:
  CL_DomElement  root;
  CL_DomNodeList childs;

  CL_DomElement get_node_by_name(const char* name) const
  {
    for(int i = 0; i < childs.get_length(); ++i)
      {
        if (strcmp(childs.item(i).get_node_value().c_str(), name) == 0)
          {
            return childs.item(i).to_element();
          }
      }
    return CL_DomElement();
  }
public:

  XMLFileReaderImpl(CL_DomElement element) 
    : root(element),
      childs(root.get_child_nodes())
  { 
  }

  std::string get_name() const
  {
    return root.get_node_value();
  }

  bool read_int(const char* name, int& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    return !node.is_null() && CL_String::from(node.get_node_value(), value);
  }
  
  bool read_float (const char* name, float& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    return !node.is_null() && CL_String::from(node.get_node_value(), value);
  }

  bool read_bool  (const char* name, bool& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    return !node.is_null() && CL_String::from(node.get_node_value(), value);
  }

  bool read_string(const char* name, std::string& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        value = node.get_node_value();
        return true;
      }
    else
      {
        return false;
      }
  }

  bool read_vector(const char* name, Vector& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        CL_DomNamedNodeMap m = node.get_attributes();
        
        CL_String::from(m.get_named_item("x").get_node_value(), value.x);
        CL_String::from(m.get_named_item("y").get_node_value(), value.y);
        CL_String::from(m.get_named_item("z").get_node_value(), value.z);

        return true;
      }
    else
      {
        return false;
      }
  }

  bool read_color(const char* name, CL_Colorf& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        CL_DomNamedNodeMap m = node.get_attributes();
        
        CL_String::from(m.get_named_item("red").get_node_value(),   value.red);
        CL_String::from(m.get_named_item("green").get_node_value(), value.green);
        CL_String::from(m.get_named_item("blue").get_node_value(),  value.blue);
        CL_String::from(m.get_named_item("alpha").get_node_value(), value.alpha);
        
        return true;
      }
    else
      {
        return false;
      }
  }

  bool read_size(const char* name, CL_Size& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        CL_DomNamedNodeMap m = node.get_attributes();
        
        CL_String::from(m.get_named_item("width").get_node_value(),  value.width);
        CL_String::from(m.get_named_item("height").get_node_value(), value.height);

        return true;
      }
    else
      {
        return false;
      }   
  }

  bool read_desc(const char* name, ResDescriptor& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        value.datafile = "";
        value.res_name = node.get_node_value();
        value.modifier = ResourceModifierNS::ROT0;

        return true;
      }
    else
      {
        return false;
      }
   
  }

  bool read_section(const char* name, FileReader& value) const
  {
    CL_DomElement node = get_node_by_name(name);
    if (!node.is_null())
      {
        value = XMLFileReader(node);
        return true;
      }
    else
      {
        return false;
      }
  }
};

XMLFileReader::XMLFileReader(CL_DomElement element)
  : FileReader(CL_SharedPtr<FileReaderImpl>(new XMLFileReaderImpl(element)))
{
}

} // namespace Pingus

/* EOF */
