//  $Id: algo.cc,v 1.5 2000/04/25 17:54:40 grumbel Exp $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA. 

#include "System.hh"
#include "algo.hh"
#include <cctype>
#include <iostream>

// Die algo, die.

bool rect_col(int ax1, int ax2, int ay1, int ay2,
              int bx1, int bx2, int by1, int by2)
{
 if (ax1 > bx2)
   return 0;
 if (ax2 < bx1)
   return 0;
 if (ay1 > by2)
   return 0;
 if (ay2 < by1)
   return 0;
 return 1;
}

// Returns the directory name, of a complete file name:
// /usr/bin/bla would return /usr/bin/
std::string
get_directory(std::string filename)
{
  char* str;
  std::string t_str;

  str = strdup(filename.c_str());

  for(int i=strlen(str); i >= 0; --i) {
    if (str[i] == '/') {
      str[i+1] = '\0';
      break;
    }
  }

  t_str = str;
  free (str);
  return t_str;
}

// Adds the ending slash to a directory name, if it is not pressent.
std::string
add_slash(std::string& str)
{
#ifndef WIN32
  if (str[str.size() - 1] != '/') 
      str += "/";
#else /* !WIN32 */
  if (str[str.size() - 1] != '\\') 
      str += "\\";
#endif /* !WIN32 */     
  return str;
}

char*
tolowerstr(char* s)
{
  //  puts(s);
  for(unsigned int i=0; i < strlen(s); ++i) {
    s[i] = std::tolower(s[i]);
  }
  //  puts(s);
  return s;
}

// Searches the given path to find the given file, it returns the
// complete filename of the searched file.
std::string
find_file(std::string paths, std::string filename)
{
  char* path;
  char* token;
  std::string token_str;
  path = strdup(paths.c_str());

  for(token = strtok(path, ":"); token != 0; token = strtok(0, ":")) {
    token_str = token;
#ifndef WIN32
    if (System::exist(token_str + "/" + filename)) { 
      return token_str + "/" + filename;
    }
#else /* !WIN32 */
    if (System::exist(token_str + "\\" + filename)) { 
      return token_str + "\\" + filename;
    }
#endif
  }
  std::cout << "find_file(): " << filename << ": File not found!" << std::endl;
  free(path);
  return filename;
}
/*
string
basename(std::string filename)
{
  const char* str = filename.c_str();
  int i;
  std::cout << "Getting basename of: " << str << std::endl;
  for(i = filename.size() - 1; i >= 0; --i) {
    //cout << str[i] << std::endl;
    if (*(str + i) == '/') {
	break;
    }
  }
  std::cout << "Basename: " << (str+i + 1) << std::endl;
  return (str+i + 1);
}
*/
/* EOF */
