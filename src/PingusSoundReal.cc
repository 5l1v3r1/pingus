//  $Id: PingusSoundReal.cc,v 1.1 2000/09/29 16:21:17 grumbel Exp $
//
//  Pingus - A free Lemmings clone
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
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

#ifdef HAVE_LIBSDL_MIXER

#include <string>
#include <cstdio>
#include <config.h>

#include "algo.hh"
#include "globals.hh"
#include "PingusMusicProvider.hh"
#include "PingusWavProvider.hh"
#include "PingusSoundReal.hh"

PingusSoundReal::PingusSoundReal ()
{
  init(pingus_audio_rate, pingus_audio_format,
       pingus_audio_channels, pingus_audio_buffers);
}

void
PingusSoundReal::init(int audio_rate, Uint16 audio_format,
		      int audio_channels, int audio_buffers)
{
  music = 0;
  is_init = true;

  printf("Initint music\n");
  printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
	 (audio_format&0xFF),
	 (audio_channels > 1) ? "stereo" : "mono", 
	 audio_buffers );
  
  if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) 
    {
      fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
      exit(255);
    }
  printf("SDL init...\n");

  /* Open the audio device */
  if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    exit(2);
  } else {
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
    printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
	   (audio_format&0xFF),
	   (audio_channels > 1) ? "stereo" : "mono", 
	   audio_buffers );
    atexit(clean_up);
  }
  audio_open = 1;

  Mix_SetMusicCMD(getenv("MUSIC_CMD"));

  printf("SDL init... done\n");
}

void
PingusSoundReal::clean_up()
{
  assert (is_init);

  if( Mix_PlayingMusic() ) 
    {
      Mix_FadeOutMusic(1500);
      SDL_Delay(1500);
    }
  
  if ( music ) 
    {
      Mix_FreeMusic(music);
      music = NULL;
    }
  
  if ( audio_open ) 
    {
      Mix_CloseAudio();
      audio_open = 0;
    }
  SDL_Quit();
}

void
PingusSoundReal::play_wav(std::string arg_str)
{
  std::string str = find_file(pingus_datadir, arg_str);
  
  if (!is_init)
    {
      init(pingus_audio_rate, pingus_audio_format,
	   pingus_audio_channels, pingus_audio_buffers);
    }
  
  //cout << "PlayingWAV: " << str << endl;
  Mix_PlayChannel(-1, PingusWavProvider::load(str), 0);
}

void
PingusSoundReal::play_mod(std::string filename)
{
  if (music)
    {
      Mix_FadeOutMusic(1000);
      Mix_FreeMusic(music);
    }
  
  printf("Playing...\n");
  music = PingusMusicProvider::load(filename);
  
  Mix_FadeInMusic(music,-1,2000);
  printf("Playing...now\n");
}

#endif /* HAVE_LIBSDL_MIXER */

/* EOF */
