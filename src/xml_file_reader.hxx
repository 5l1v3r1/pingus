//  $Id: xml_file_reader.hxx,v 1.1 2002/12/20 18:45:41 grumbel Exp $
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

#ifndef HEADER_XML_FILE_READER_HXX
#define HEADER_XML_FILE_READER_HXX

#include "xml_helper.hxx"
#include "file_reader.hxx"

/** */
class XMLFileReader : public FileReader
{
private:
  /** Pointer to the XML document */
  xmlDocPtr  doc;
  
  /** Pointer to the current section node, if one wants to access the
      content of the section one has to use cur->children */
  xmlNodePtr section_node;

  xmlNodePtr find_node(const char* name);
public:
  XMLFileReader(xmlDocPtr doc, xmlNodePtr node);
  
  bool read_int   (const char* name, int*);
  bool read_float (const char* name, float*);
  bool read_bool  (const char* name, bool*);
  bool read_string(const char* name, std::string*);
  bool read_vector(const char* name, Vector*);

private:
  XMLFileReader (const XMLFileReader&);
  XMLFileReader& operator= (const XMLFileReader&);
};

#endif

/* EOF */
