##  -*- python -*-
##  $Id: pingus_main.hxx,v 1.14 2003/10/18 12:11:30 grumbel Exp $
##
##  Pingus - A free Lemmings clone
##  Copyright (C) 1999 Ingo Ruhnke <grumbel@gmx.de>,
##                     Francois Beerten
##
##  This program is free software; you can redistribute it and/or
##  modify it under the terms of the GNU General Public License
##  as published by the Free Software Foundation; either version 2
##  of the License, or (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

import sys, os
import SCons.Util

pingus_sources = [
'src/pingus/action_holder.cpp', 
'src/pingus/addon_menu.cpp', 
'src/pingus/blitter.cpp',
'src/pingus/capture_rectangle.cpp', 
'src/pingus/collider.cpp', 
'src/pingus/collision_map.cpp', 
'src/pingus/collision_mask.cpp',
'src/util/command_line.cpp',
'src/util/command_line_generic.cpp',
'src/pingus/config_manager.cpp', 
'src/pingus/credits.cpp', 
'src/pingus/debug.cpp', 
'src/util/debug_stream.cpp', 
'src/pingus/demo_session.cpp', 
'src/pingus/direction.cpp', 
'src/util/file_reader.cpp',
'src/pingus/font.cpp',
'src/pingus/font_description.cpp',
'src/pingus/font_test_screen.cpp',
'src/pingus/fonts.cpp',
'src/pingus/fps_counter.cpp', 
'src/pingus/game_session.cpp', 
'src/pingus/game_time.cpp', 
'src/pingus/gettext.cpp', 
'src/pingus/global_event.cpp', 
'src/pingus/globals.cpp', 
'src/pingus/goal_manager.cpp', 
'src/pingus/graphic_context_state.cpp', 
'src/pingus/ground_map.cpp', 
'src/pingus/groundtype.cpp',
'src/pingus/layer_manager.cpp', 
'src/pingus/level_menu.cpp',
'src/pingus/levelset.cpp',
'src/pingus/line_iterator.cpp',
'src/math/math.cpp',
'src/pingus/mover.cpp', 
'src/pingus/option_menu.cpp',
'src/pingus/path_manager.cpp',
'src/util/pathname.cpp', 
'src/pingus/pingu.cpp', 
'src/pingus/pingu_action.cpp', 
'src/pingus/pingu_enums.cpp', 
'src/pingus/pingu_holder.cpp', 
'src/pingus/pingus_demo.cpp', 
'src/pingus/pingus_error.cpp', 
'src/pingus/pingus_level.cpp', 
'src/pingus/pingus_main.cpp', 
'src/pingus/pingus_menu.cpp', 
'src/pingus/plf_res_mgr.cpp', 
'src/pingus/res_descriptor.cpp', 
'src/pingus/resource.cpp',
'src/pingus/resource_manager.cpp', 
'src/pingus/resource_modifier.cpp', 
'src/pingus/result_screen.cpp', 
'src/pingus/savegame.cpp', 
'src/pingus/savegame_manager.cpp', 
'src/pingus/screenshot.cpp', 
'src/pingus/server.cpp', 
'src/pingus/server_event.cpp', 
'src/util/sexpr_file_reader.cpp', 
'src/util/sexpr_file_writer.cpp', 
'src/pingus/smallmap_image.cpp', 
'src/pingus/sprite.cpp',
'src/pingus/sprite_impl.cpp',
'src/pingus/start_screen.cpp', 
'src/pingus/stat_manager.cpp', 
'src/pingus/state_sprite.cpp', 
'src/pingus/story_screen.cpp', 
'src/pingus/string_format.cpp',
'src/util/string_util.cpp',
'src/pingus/surface.cpp',
'src/util/system.cpp', 
'src/util/utf8.cpp',
'src/pingus/world.cpp', 
'src/pingus/worldobj.cpp', 
'src/pingus/worldobj_factory.cpp', 

'src/actions/angel.cpp', 
'src/actions/basher.cpp', 
'src/actions/blocker.cpp', 
'src/actions/boarder.cpp', 
'src/actions/bomber.cpp', 
'src/actions/bridger.cpp', 
'src/actions/climber.cpp', 
'src/actions/digger.cpp', 
'src/actions/drown.cpp', 
'src/actions/exiter.cpp', 
'src/actions/faller.cpp', 
'src/actions/floater.cpp', 
'src/actions/jumper.cpp', 
'src/actions/laser_kill.cpp', 
'src/actions/miner.cpp', 
'src/actions/rocket_launcher.cpp', 
'src/actions/slider.cpp', 
'src/actions/smashed.cpp', 
'src/actions/splashed.cpp', 
'src/actions/superman.cpp', 
'src/actions/waiter.cpp', 
'src/actions/walker.cpp', 

'src/colliders/pingu_collider.cpp',

'src/components/action_button.cpp', 
'src/components/button_panel.cpp', 
'src/components/check_box.cpp', 
'src/components/choice_box.cpp', 
'src/components/label.cpp', 
'src/components/menu_button.cpp', 
'src/components/pingus_counter.cpp', 
'src/components/playfield.cpp', 
'src/components/slider_box.cpp', 
'src/components/smallmap.cpp', 
'src/components/time_display.cpp', 

'src/display/delta_framebuffer.cpp', 
'src/display/display.cpp', 
'src/display/drawing_context.cpp', 
'src/display/framebuffer_surface.cpp', 
'src/display/null_framebuffer.cpp', 
'src/display/rect_merger.cpp',
'src/display/scene_context.cpp', 
'src/display/sdl_framebuffer.cpp', 
'src/display/sdl_framebuffer_surface_impl.cpp', 

'src/editor/action_properties.cpp', 
'src/editor/button.cpp',
'src/editor/checkbox.cpp',
'src/editor/combobox.cpp', 
'src/editor/editor_level.cpp', 
'src/editor/editor_screen.cpp',
'src/editor/file_dialog.cpp',
'src/editor/file_list.cpp',
'src/editor/gui_style.cpp',
'src/editor/inputbox.cpp',
'src/editor/label.cpp',
'src/editor/level_objs.cpp',
'src/editor/level_properties.cpp',
'src/editor/minimap.cpp', 
'src/editor/object_properties.cpp',
'src/editor/object_selector.cpp',
'src/editor/object_selector_list.cpp',
'src/editor/object_selector_set.cpp',
'src/editor/panel.cpp',
'src/editor/viewport.cpp', 

'src/gui/component.cpp',
'src/gui/group_component.cpp', 
'src/gui/gui_manager.cpp', 
'src/gui/surface_button.cpp',

'src/input/controller_description.cpp',
'src/input/controller.cpp',
'src/input/core_driver.cpp',
'src/input/sdl_driver.cpp',
'src/input/manager.cpp',

'src/lisp/getters.cpp',
'src/lisp/lexer.cpp',
'src/lisp/lisp.cpp',
'src/lisp/parser.cpp',

'src/math/origin.cpp',
'src/math/rect.cpp',
'src/math/size.cpp',
'src/math/vector2f.cpp',
'src/math/vector2i.cpp',
'src/math/vector3f.cpp',

'src/movers/linear_mover.cpp', 

'src/particles/explosive_particle.cpp', 
'src/particles/pingu_particle_holder.cpp', 
'src/particles/rain_particle_holder.cpp', 
'src/particles/smoke_particle_holder.cpp', 
'src/particles/snow_particle_holder.cpp', 

'src/screen/gui_screen.cpp', 
'src/screen/screen.cpp', 
'src/screen/screen_manager.cpp', 

'src/sound/sound.cpp', 
'src/sound/sound_dummy.cpp', 
'src/sound/sound_real.cpp', 
'src/sound/sound_res_mgr.cpp', 

'external/tinygettext/dictionary.cpp',
'external/tinygettext/iconv.cpp',
'external/tinygettext/plural_forms.cpp',
'external/tinygettext/dictionary_manager.cpp',
'external/tinygettext/language.cpp',
'external/tinygettext/po_parser.cpp',
'external/tinygettext/directory.cpp',
'external/tinygettext/log.cpp',
'external/tinygettext/tinygettext.cpp',

'src/worldmap/dot.cpp', 
'src/worldmap/dot_factory.cpp', 
'src/worldmap/drawable.cpp', 
'src/worldmap/drawable_factory.cpp', 
'src/worldmap/graph.cpp', 
'src/worldmap/level_dot.cpp', 
'src/worldmap/path.cpp', 
'src/worldmap/path_drawable.cpp', 
'src/worldmap/path_graph.cpp', 
'src/worldmap/pingus.cpp', 
'src/worldmap/pingus_worldmap.cpp', 
'src/worldmap/sprite_drawable.cpp', 
'src/worldmap/worldmap.cpp', 
'src/worldmap/worldmap_component.cpp', 
'src/worldmap/worldmap_screen.cpp', 
'src/worldmap/worldmap_story.cpp', 

'src/worldobjs/conveyor_belt.cpp', 
'src/worldobjs/entrance.cpp', 
'src/worldobjs/exit.cpp', 
'src/worldobjs/fake_exit.cpp', 
'src/worldobjs/groundpiece.cpp', 
'src/worldobjs/guillotine.cpp', 
'src/worldobjs/hammer.cpp', 
'src/worldobjs/hotspot.cpp', 
'src/worldobjs/ice_block.cpp', 
'src/worldobjs/laser_exit.cpp', 
'src/worldobjs/liquid.cpp', 
'src/worldobjs/rain_generator.cpp', 
'src/worldobjs/smasher.cpp', 
'src/worldobjs/snow_generator.cpp', 
'src/worldobjs/solid_color_background.cpp', 
'src/worldobjs/spike.cpp', 
'src/worldobjs/starfield_background.cpp', 
'src/worldobjs/starfield_background_stars.cpp', 
'src/worldobjs/surface_background.cpp', 
'src/worldobjs/switch_door.cpp', 
'src/worldobjs/teleporter.cpp',
'src/worldobjs/teleporter_target.cpp', 
'src/worldobjs/thunderstorm_background.cpp', 
'src/worldobjs/woodthing.cpp',

'lib/binreloc/binreloc.c'
]

class _SpaceListOptionClass:
   """An option type for space-separated lists with arbitrary elements."""
   def CheckDir(self, val):
      if not os.path.isdir(val):
         raise SCons.Errors.UserError("No directory at %s" % val)

   def _convert(self, key, val, env):
      if SCons.Util.is_List(val): # prefer val if it's already a list
         return val
      elif len(val) > 0 and val[0] == '[' and val[-1] == ']':
         # or a repr of a list
         return eval(val)
      elif env: # otherwise, use whatever's in env
         val = env[key]
         if not SCons.Util.is_List(val):
            val = val.split(None)
         return val
      else: # val was substituted into a string, losing its structure
         # We'll be called again with env, hopefully that's more useful
         raise TypeError("try again with the environment")

   def _validate(self, val, env, check, converter):
      for i in converter(val, env):
         if check(i):
            return True
      return False

   def __call__(self, key, help, check=None, default=[]):
      def converter(val, env = None):
         return self._convert(key, val, env)
 
      validator = None
      if check is not None:
         validator = lambda k, v, e: self._validate(v, e, check, converter)
      return (key, help, default, validator, converter)
 
SpaceListOption = _SpaceListOptionClass()

def DefineOptions(filename, args):
   opts = Variables(filename, args)
   opts.Add('CC', 'C Compiler', 'gcc')
   opts.Add('CXX', 'C++ Compiler', 'g++')
#   opts.Add('debug', 'Build with debugging options', 0)
#   opts.Add('profile', 'Build with profiling support', 0)

   opts.Add('CPPPATH',    'Additional preprocessor paths', [])
   opts.Add('LIBPATH',    'Additional library paths',      [])
   opts.Add('CPPFLAGS',   'Additional preprocessor flags', [])
   opts.Add('CPPDEFINES', 'defined constants', [])
   opts.Add('LIBS',       'Additional libraries', [])
   opts.Add('CCFLAGS',    'C Compiler flags', [])
   opts.Add('CXXFLAGS',   'C++ Compiler flags', [])
   opts.Add('LINKFLAGS',  'Linker Compiler flags', [])

   opts.Add(BoolVariable('with_opengl',        'Build with OpenGL support', True))
   opts.Add(BoolVariable('with_xinput',        'Build with Xinput support', False))
   opts.Add(BoolVariable('with_linuxusbmouse', 'Build with Linux USB mouse support', True))
   opts.Add(BoolVariable('with_linuxevdev',    'Build with Linux evdev support', True))
   opts.Add(BoolVariable('with_wiimote',       'Build with Wiimote support', False))
   opts.Add(BoolVariable('ignore_errors',      'Ignore any fatal configuration errors', False))
   opts.Add('optional_sources', 'Additional source files', [])
   return opts

def CheckSDLLib(context, sdllib):
   """
   On some platforms, SDL does this ugly redefine-main thing, that can
   interact badly with CheckLibWithHeader.
   """
   lib = "SDL_%s" % sdllib
   context.Message('Checking for %s...' % lib)
   text = """
#include "SDL.h"
#include "%s.h"
int main(int argc, char* argv[]) { return 0; }
""" % lib
   context.AppendLIBS(lib)
   if context.BuildProg(text, ".cpp"):
      context.Result("failed")
      return False
   else:
      context.Result("ok")
      return True

def CheckIconv(context):
   text = """
#include <iconv.h>
int main() {
   %s char *foo;
   (void)iconv((iconv_t)0, &foo, (size_t*)0, (char**)0, (size_t*)0);
   return 0;
}
"""
   config.CheckLibWithHeader('iconv', 'iconv.h', 'c++') # Ok to fail
   context.Message('Check how to call iconv...')

   for i in ['', 'const']:
      if config.TryCompile(text % i, ".cpp"):
         context.Result("use '%s'" % i)
         return i
   context.Result("failed")
   return False

def CheckMyProgram(context, prgn):
   context.Message('Checking for %s...' % prgn)
   for i in context.env['ENV']['PATH'].split(":"):
      if os.path.exists(i + "/sdl-config"):
         context.Result(i + "/sdl-config")
         return True
   context.Result("failed")
   return False

Alias('configure')
    
if ('configure' in COMMAND_LINE_TARGETS) or \
   not (os.path.exists('config.py') and os.path.exists('config.h')) and \
   not GetOption('clean'):
    opts = DefineOptions(None, ARGUMENTS)
    env = Environment(options = opts)
    Help(opts.GenerateHelpText(env))

    opts.Update(env)

    if os.environ.has_key('PATH'):
        env['ENV']['PATH'] = os.environ['PATH']
    if os.environ.has_key('HOME'):
       env['ENV']['HOME'] = os.environ['HOME']

    if os.environ.has_key('PKG_CONFIG_PATH'):
        env['ENV']['PKG_CONFIG_PATH'] = os.environ['PKG_CONFIG_PATH']
    
    env['CPPPATH'] += ['.', 'src/', 'external/']

    config_h_defines = []      

    config = env.Configure(custom_tests = {
       'CheckMyProgram' : CheckMyProgram,
       'CheckSDLLib': CheckSDLLib,
       'CheckIconv': CheckIconv,
    })
    fatal_error = ""
    reports = ""

    # FIXME: Seems to require a rather new version of SCons
    # ret = config.CheckBuilder(context, None, "C++")
    # if ret != "":
    #   reports += "  * C++ Compiler missing: " + ret

    if not env['with_opengl']:
       reports += "  * OpenGL support: disabled\n"
    else:
       reports += "  * OpenGL support: enabled\n"
       config_h_defines  += [('HAVE_OPENGL', 1)]
       env['LIBS']       += ['GL']
       env['optional_sources'] += ['src/display/opengl_framebuffer_surface_impl.cpp', 
                                   'src/display/opengl_framebuffer.cpp' ]

    if not env['with_linuxusbmouse']:
        reports += "  * Linux USB mouse support: disabled\n"
    else:
        reports += "  * Linux USB mouse support: enabled\n"
        config_h_defines  += [('HAVE_LINUXUSBMOUSE', 1)]
        env['optional_sources'] += ['src/input/usbmouse_driver.cpp']
    
    if not env['with_linuxevdev']:
        reports += "  * Linux evdev support: disabled\n"
    else:
        reports += "  * Linux evdev support: ok\n"
        config_h_defines  += [('HAVE_LINUXEVDEV', 1)]
        env['optional_sources'] += ['src/input/evdev_driver.cpp',
                                    'src/input/evdev_device.cpp']
    
    if not env['with_wiimote']:
        reports += "  * Wiimote support: disabled\n"        
    elif config.CheckLibWithHeader('cwiid', 'cwiid.h', 'c++'):
        reports += "  * Wiimote support: yes\n"
        config_h_defines  += [('HAVE_CWIID', 1)]
        env['LIBS']       += ['cwiid']
        env['optional_sources'] += ['src/input/wiimote_driver.cpp',
                                    'src/input/wiimote.cpp']
    else:
        reports += "  * Wiimote support: no (libcwiid or cwiid.h not found)\n"

    if not env['with_xinput']:
        reports += "  * XInput support: disabled\n"
    elif not config.CheckLibWithHeader('Xi', 'X11/extensions/XInput.h', 'c++'):
        reports += "  * XInput support: no (library Xi not found)\n" ## FIXME: Need to set a define
    else:
        reports += "  * XInput support: yes\n"
        config_h_defines  += [('HAVE_XINPUT', 1)]
        env['LIBS'] += ['Xi']
        env['optional_sources'] += ['src/input/xinput_driver.cpp',
                                    'src/input/xinput_device.cpp']
        
    if not config.CheckLibWithHeader('boost_signals', 'boost/signals.hpp', 'c++'):
       if not config.CheckLibWithHeader('boost_signals-mt', 'boost/signals.hpp', 'c++'):
          fatal_error += "  * library 'boost_signals' not found\n"

    if not config.CheckLibWithHeader('png', 'png.h', 'c++'):
       fatal_error += "  * library 'png' not found\n"

    if config.CheckMyProgram('sdl-config'):
       env.ParseConfig('sdl-config  --cflags --libs')
       for sdllib in ['image', 'mixer']:
          if not config.CheckSDLLib(sdllib):
             fatal_error += "  * SDL library '%s' not found\n" % sdllib
    else:
       fatal_error += "  * couldn't find sdl-config, SDL missing\n"

    iconv_const = config.CheckIconv()
    if iconv_const == False:
       fatal_error += "  * can't call iconv\n"

    env = config.Finish()
    opts.Save("config.py", env)

    print "Reports:"
    print reports

    if not fatal_error == "":
        print "Fatal Errors:"
        print fatal_error
        if not env['ignore_errors']:
           Exit(1)
        else:
           print "\nError are being ignored, the build continues"

    config_h = open('config.h', 'w')
    config_h.write('#define VERSION "0.7.3"\n')
    config_h.write('#define ENABLE_BINRELOC 1\n')
    config_h.write('#define ICONV_CONST %s\n' % iconv_const)
    for (v,k) in config_h_defines:
        config_h.write('#define %s %s\n' % (v, k))
    config_h.close()
    if ('configure' in COMMAND_LINE_TARGETS):
        print "Configuration written to config.h and config.py, run:"
        print ""
        print "  scons"
        print ""
        print "To start the compile"
    else:
        print "Configuration written to config.h and config.py"
    ARGUMENTS = {}

if not ('configure' in COMMAND_LINE_TARGETS):
    if ARGUMENTS != {}:
        print "Error: You must not supply arguments to the compile step."
        print "Use:"
        print ""
        print "  scons configure [ARGUMENTS]..."
        print ""
        print "If you want to change the build configuration."
        os.sys.exit(1)
        
    opts = DefineOptions("config.py", {})
    env = Environment(options = opts)
    Help(opts.GenerateHelpText(env))

    opts.Update(env)
    env['CPPPATH'] += ['.', 'src/']
    Default(env.Program('pingus', pingus_sources + env['optional_sources']))
    Clean('pingus', ['config.py', 'config.h'])

    
## EOF ##
