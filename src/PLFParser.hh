//  $Id: PLFParser.hh,v 1.2 2000/02/09 21:43:40 grumbel Exp $
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

#ifndef PLFParser_HH
#define PLFParser_HH

#include <fstream>
#include <string>
#include <vector>

#ifdef WIN32
using namespace std;
#endif /* WIN32 */


class PLFParserEOF {
public:
  PLFParserEOF();
};


class PLFParser
{
private:
  ifstream in;                 // The file to parse

  char   last_atom;            // The last returned atom
  int    lineno;               // Current line number
  bool   eof;
  //  string filename;             // The name of the current file

  // private functions    
  char   get_char(void);       // Return the next char and to a eof check
  char   get_atom(void);       // Return the next atom and keep the old one
  char   get_raw_atom(void);   // Return the next atom (removes all comments)
  string get_groupname(void);  // Return the groupname and check for errors
  string get_valueid(void);    // Return the value identifer
  string get_value(void);      // Return the value
  string get_cast(void);       // Return the cast, else ""
  void   jump_after(char);     // Jump to the next token, after char
  void   jump(void);           // Jump over spaces to the next token
  void   syntax_error(string); // Do a clean shutdown on a syntax error
  void   parse(void);          // Parse the opened file
  void  open(string);          // Open the file

  // Some virtual functions
  // Put the retrieved value in the correct struct
  virtual void set_value(string valueid,
			 string cast,
			 string value) = 0; 
  virtual void set_group_start(string) = 0;
  virtual void set_group_end(void) = 0;
public:                        //
  PLFParser();
  PLFParser(string);           // Open the file and parse it
  virtual ~PLFParser();        // Close the file

  void init(string);           // Init the PLFParser and start parsing
};

#endif

/* EOF */
