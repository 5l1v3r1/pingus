//  $Id: xml_file_writer.hxx,v 1.1 2002/12/20 18:45:41 grumbel Exp $
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

#ifndef HEADER_XML_FILE_WRITER_HXX
#define HEADER_XML_FILE_WRITER_HXX

#include <iostream>
#include <stack>
#include "file_writer.hxx"

/** */
class XMLFileWriter : public FileWriter
{
private:
  /** A reference to the output stream */
  std::ostream* out;

  std::stack<std::string> section_stack;

public:
  XMLFileWriter(std::ostream& out_);
  virtual ~XMLFileWriter();

  void begin_section (const char* name);
  void end_section ();

  void write_int    (const char* name, int);
  void write_float  (const char* name, float);
  void write_bool   (const char* name, bool);
  void write_string (const char* name, const std::string&);
  void write_vector (const char* name, const Vector&);
  
private:
  XMLFileWriter (const XMLFileWriter&);
  XMLFileWriter& operator= (const XMLFileWriter&);
};

#endif

/* EOF */
