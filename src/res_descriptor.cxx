//  $Id: res_descriptor.cxx,v 1.18 2003/10/20 19:28:54 grumbel Exp $
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

#include <assert.h>
#include <iostream>
#include "res_descriptor.hxx"
#include "pingus_error.hxx"

namespace Pingus {

/*
   uri -> file:///home/ingo/.pingus/images/...
   uri -> resource://core/result/ok
   uri -> file://bla.png (relative to ~/.pingus/images/)
   ResDescriptor(const std::string& uri);
*/

ResDescriptor::ResDescriptor()
{
  res_name = "";
  datafile = "global";
  modifier = ResourceModifierNS::ROT0;
}

ResDescriptor::ResDescriptor(const std::string& arg_res_name,
			     const std::string& arg_datafile,
			     ResourceModifierNS::ResourceModifier arg_modifier)
{
  res_name = arg_res_name;
  datafile = arg_datafile;
  modifier = arg_modifier;
}

bool
ResDescriptor::operator<(const ResDescriptor& res_desc) const
{
  // FIXME: This is ugly and slow
  //return (datafile + res_name + CL_String::to (type) + to_string (modifier))
  //  < (res_desc.datafile + res_desc.res_name + CL_String::to (res_desc.type) + to_string (res_desc.modifier));

  if (datafile < res_desc.datafile)
    return true;
  else if (datafile > res_desc.datafile)
    return false;
  else
    {
      if (res_name < res_desc.res_name)
	return true;
      else if (res_name > res_desc.res_name)
	return false;
      else
	{
	  if (modifier < res_desc.modifier)
	    return true;
	  else if (modifier > res_desc.modifier)
	    return false;
	  else
            return false;
	}
    }
}

} // namespace Pingus

std::ostream& operator<<(std::ostream& s, const Pingus::ResDescriptor& desc)
{
  using namespace Pingus;

  return s << "[" << desc.res_name << ", " << desc.datafile
           << ", " << ResourceModifierNS::rs_to_string(desc.modifier) << "]";
}

/* EOF */
