//  Pingus - A free Lemmings clone
//  Copyright (C) 2007 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "pingus/resource_manager.hpp"

#include <algorithm>

#include "engine/display/sprite_description.hpp"
#include "lisp/parser.hpp"
#include "pingus/globals.hpp"
#include "util/log.hpp"
#include "util/sexpr_file_reader.hpp"
#include "util/string_util.hpp"
#include "util/system.hpp"

ResourceManager::ResourceManager() :
  m_cache(),
  m_resources(),
  m_aliases()
{
}

ResourceManager::~ResourceManager()
{
}

std::vector<std::string>
ResourceManager::get_section(const std::string& name)
{
  std::vector<std::string> lst;
  for (auto i = m_cache.begin(); i != m_cache.end(); ++i)
  {
    if (StringUtil::has_prefix(i->first, name))
    {
      lst.push_back(i->first);
    }
  }

  for (auto i = m_resources.begin(); i != m_resources.end(); ++i)
  {
    if (StringUtil::has_prefix(*i, name))
    {
      lst.push_back(*i);
    }
  }

  return lst;
}

void
ResourceManager::add_resources(const std::string& filename)
{
  log_info(filename);

  std::shared_ptr<lisp::Lisp> sexpr = lisp::Parser::parse(filename);
  if (sexpr)
  {
    SExprFileReader reader(sexpr->get_list_elem(0));

    if (reader.get_name() == "pingus-resources")
    {
      std::vector<FileReader> sections = reader.get_sections();
      for(std::vector<FileReader>::iterator i = sections.begin(); i != sections.end(); ++i)
      {
        //log_info("Section: " << i->get_name());
        parse("", *i);
      }
    }
    else
    {
      log_error("couldn't find section 'pingus-resources' section in file " << filename
                << "\ngot " << reader.get_name());
    }
  }
  else
  {
    log_info("ResourceManager: File not found " << filename);
  }
}

void
ResourceManager::add_resources_from_directory(const Pathname& path)
{
  assert(path.get_type() == Pathname::DATA_PATH);

  std::vector<std::string> files = System::opendir_recursive(path.get_sys_path());
  for(auto it = files.begin(); it != files.end(); ++it)
  {
    if (StringUtil::has_suffix(*it, ".sprite") ||
        StringUtil::has_suffix(*it, ".png") ||
        StringUtil::has_suffix(*it, ".jpg"))
    {
      // FIXME: ugly hack to remove "data/images/" prefix, need better
      // way to cut stuff away
      m_resources.insert(System::cut_file_extension(it->substr(12)));
    }
  }
}

void
ResourceManager::parse(const std::string& section, FileReader& reader)
{
  if (reader.get_name() == "section")
  {
    parse_section(section, reader);
  }
  else if (reader.get_name() == "sprite")
  {
    std::string name;
    reader.read_string("name", name);
    if (!section.empty())
      name = section + "/" + name;
 
    m_cache[name].reset(new SpriteDescription(reader));
  }
  else if (reader.get_name() == "alias")
  {
    std::string name;
    std::string link;
    if (reader.read_string("name", name) &&
        reader.read_string("link", link))
    {
      //log_info("alias: " << name << " -> " << link);
      m_aliases[name] = link;
    }
  }
  else if (reader.get_name() == "name")
  {
    // ignore (ugly)
  }
  else
  {
    log_info("ResourceManager: unknown token: '" << reader.get_name() << "'");
  }
}

void
ResourceManager::parse_section(const std::string& section, FileReader& reader)
{
  std::string name;
  reader.read_string("name", name);

  std::vector<FileReader> sections = reader.get_sections();
  for(std::vector<FileReader>::iterator i = sections.begin(); i != sections.end(); ++i)
  {    
    if (section.empty())
      parse(name, *i);
    else
      parse(section + "/" + name, *i);
  }
}

std::shared_ptr<SpriteDescription>
ResourceManager::get_sprite_description_from_file(const std::string& resname)
{
  // try to load a .sprite file
  std::string filename = "images/" + resname + ".sprite";
  Pathname path(filename, Pathname::DATA_PATH);
  if (path.exist())
  {
    SpriteDescriptionPtr desc = SpriteDescription::from_file(path);

    // resolve relative filenames
    if (!desc->filename.absolute())
    {
      // path normalization is important here to allow overlay paths,
      // as a path of the form "pingus/blocker/../blocker.png" would
      // fail when "pingus/blocker/" is missing, even so
      // "pingus/blocker.png" exists
      desc->filename = Pathname(System::normalize_path(System::dirname(filename) + "/" + desc->filename.get_raw_path()),
                                Pathname::DATA_PATH);
    }

    return desc;
  }

  // try to load a .png file
  filename = "images/" + resname + ".png";
  path = Pathname(filename, Pathname::DATA_PATH);
  if (path.exist())
  {
    SpriteDescriptionPtr desc(new SpriteDescription);
    desc->filename = path;
    return desc;
  }

  // try to load a .jpg file
  filename = "images/" + resname + ".jpg";
  path = Pathname(filename, Pathname::DATA_PATH);
  if (path.exist())
  {
    SpriteDescriptionPtr desc(new SpriteDescription);
    desc->filename = path;
    return desc;
  }

  // give up
  return SpriteDescriptionPtr();
}

SpriteDescription* 
ResourceManager::get_sprite_description(const std::string& name)
{
  auto i = m_cache.find(name);
  if (i != m_cache.end())
  {
    return i->second.get();
  }
  else
  {
    SpriteDescriptionPtr desc = get_sprite_description_from_file(name);
    if (desc)
    {
      m_cache[name] = desc;
      return desc.get();
    }
    else
    {
      auto j = m_aliases.find(name);
      if (j != m_aliases.end())
      {
        log_warn("using alias \"" << j->first << "\" -> \"" << j->second << "\"");
        return get_sprite_description(j->second);
      }
      else
      {
        return 0;
      }
    }
  }  
}

/* EOF */
