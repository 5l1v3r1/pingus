//  $Id: psm_parser.cxx,v 1.4 2002/08/16 15:13:59 torangan Exp $
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

#include <stdio.h>
#include "globals.hxx"
#include "pingus_error.hxx"

#include "psm_parser.hxx"

using namespace std;

PSMParser::PSMParser()
{
  lines = 0;
}

PSMParser::~PSMParser()
{
  
}

void
PSMParser::parse(string filename)
{
  try {
    if (verbose > 1) cout << "PSMParser: Filename: " << filename << endl;
    
    in.open(filename.c_str());

    if (!in) 
      PingusError::raise("Cannot open: " + filename);
    
    GroundpieceData temp;
    
    while(!in.eof()) {
      jump_spaces();
      std::string str = get_string();
      
      temp.gptype = GroundpieceData::string_to_type(str);

      expect(':');

      jump_spaces();
      temp.desc = get_resdesc();
      temp.desc.res_name = get_string();
      expect(':');

      jump_spaces();
      temp.pos.x = get_int();
      expect(':');

      jump_spaces();
      temp.pos.y = get_int();
      expect(';');

      surface.push_back(temp);
    }
  }
  catch (PSMParseError err) {
    cout << "PSMParseError occured: " << err.message << " at line: " << lines << endl;
    PingusError::raise(err.message);
  }
  catch (PSMEOF) {}
  file_parsed = true;
  in.close();
}
/*
void
PSMParser::load_surfaces(void)
{
  assert(file_parsed);

  for (vector<GroundpieceData>::size_type i=0; i < surface.size(); ++i) {
    if (verbose > 1) {
      cout << "Surface: " << "(" << "?? - section broken - ??" << ":" << surface[i].res_desc.datafile << ") " 
	   << surface[i].res_desc.res_name << endl;
    }
    surface[i].surface = PingusResource::load_surface(surface[i].res_desc);
  }
}
*/
vector<GroundpieceData>
PSMParser::get_surfaces(void)
{
  return surface;
}

char
PSMParser::get_char(void)
{
  char c;
  c = in.get();

  if (in.eof()) {
    throw PSMEOF();
  }

  if (c == '\n')
    ++lines;

  return c;
}

char
PSMParser::get_atom(void)
{
  return get_char();
}

void
PSMParser::jump_spaces()
{
  char c;
  while (isspace(c = get_char()));
  in.putback(c);
}

string
PSMParser::get_string(void)
{
  string str;
  char   c;

  while (!isspace(c = get_atom()) && c != ':') {
    str += c;
  }
  
  if (c == ':')
    in.putback(c);

  if (str.empty())
    throw PSMParseError("PSMParser::get_string(): String is empty!");

  return str;
}

int
PSMParser::get_int(void)
{
  string str;
  char   c;
  int    i;

  if ((c = get_atom()) == '-')
    str += c;
  else
    in.putback(c);

  while (isdigit(c = get_atom())) {
    str += c;
  }

  in.putback(c);

  if (sscanf(str.c_str(), "%d", &i) != 1)
    throw PSMParseError("Couldn't convert: " + str + " to int");

  return i;
}

// FIXME: This is broken the res_name is actually the cast...
ResDescriptor
PSMParser::get_resdesc(void)
{
  ResDescriptor temp;
  char c;
  
  temp.res_name = "";
  temp.datafile = "";

  jump_spaces();

  if ((c = get_atom()) != '(') {
    in.putback(c);
    jump_spaces();
    return ResDescriptor();
  } else {
    jump_spaces();
    while ((c = get_atom()) != ')' && c != ':') {
      temp.res_name += c;
    }
    
    if (c == ')') {
      jump_spaces();
      return ResDescriptor(temp.res_name, "global");
    } else { // c == ':'
      while ((c = get_atom()) != ')') {
	temp.datafile += c;
      }
      jump_spaces();
      return ResDescriptor(temp.res_name, temp.datafile);
    }
  }
}

void
PSMParser::expect(char b)
{
  char c;
  jump_spaces();
  c = get_atom();
  if (c == b) {
    return;
  } else {
    throw PSMParseError(string("Didn't find expected char: '") + b + "', found '" + c +"' instead.");
    return;
  }
}

/* EOF */
