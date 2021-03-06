/*
 * SoundManager.cpp
 *
 *  Created on: Jan 17, 2013
 *      Author: nathan
 */

#include "SoundManager.h"
#include <iostream>

namespace TileEngine
{

SoundManager::SoundManager()
{
	int audio_rate = 22050;
	Uint16 audio_format = MIX_DEFAULT_FORMAT;
	int audio_channels = 2;
	int audio_buffers = 4096;

    if(SDL_Init(SDL_INIT_AUDIO) == -1)
    {
        std::cout << "Unable to initialize audio in SoundManager" << std::endl;
        SDL_Quit();
    }

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers))
	{
		std::cout << "Unable to open audio" << std::endl;
		SDL_Quit();
	}
	soundVolume = 60;
	musicVolume = 60;
	setMusicVolume(musicVolume);
	setSoundVolume(soundVolume);
}

SoundManager::~SoundManager()
{
	deleteAllSounds();
	deleteAllMusic();
	Mix_CloseAudio();
}

void SoundManager::deleteAllMusic()
{
	stopMusic();
	MusicIterator it;
	musicLookup.clear();
	for (it = musics.begin(); it != musics.end(); ++it)
	{
		Mix_FreeMusic(it->second);
		musics.erase(it);
	}
}

void SoundManager::deleteAllSounds()
{
	SoundIterator it;
	soundLookup.clear();
	for (it = sounds.begin(); it != sounds.end(); ++it)
	{
		Mix_FreeChunk(it->second);
		sounds.erase(it);
	}
}

void SoundManager::setMusicVolume(int volume)
{
	if (volume > 128)
	{
		volume = 128;
	}
	if (volume < 0)
	{
		volume = 0;
	}

	Mix_VolumeMusic(volume);
	musicVolume = volume;
}

void SoundManager::setSoundVolume(int volume)
{
	if (volume > 128)
	{
		volume = 128;
	}
	if (volume < 0)
	{
		volume = 0;
	}

	Mix_Volume(-1, volume);
	musicVolume = volume;
}

int SoundManager::getMusicVolume() const
{
	return musicVolume;
}

int SoundManager::getSoundVolume() const
{
	return soundVolume;
}

void SoundManager::playMusic(std::string name)
{
	LookUpIterator it = musicLookup.find(name);
	if (it != musicLookup.end())
	{
		name = it->second;
	}

	Mix_Music* music = acquireMusic(name);

	stopMusic();

	if (Mix_PlayMusic(music, -1) == -1)
	{
		std::cout << "Couldn't play " << name << std::endl;
	}
}

void SoundManager::pauseMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_PauseMusic();
	}
}

void SoundManager::resumeMusic()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
	}
}

void SoundManager::stopMusic()
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void SoundManager::playSound(std::string name)
{
	LookUpIterator it = soundLookup.find(name);
	if (it != soundLookup.end())
	{
		name = it->second;
	}

	Mix_Chunk* sound = acquireSound(name);
	if (Mix_PlayChannel( -1, sound, 0 ) == -1)
	{
		std::cout << "Couldn't play " << name << std::endl;
	}
}

Mix_Music* const SoundManager::acquireMusic(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + AUDIO_DIR + fileName;
	MusicIterator musicElement = musics.find(absFileName);

	// If we've already loaded this resource, simply increment the counter
	// in the tracker and return the surface
	//
	// Otherwise, load it and add it to the tracker with an initial count of 1
	if (musicElement != musics.end())
	{
		return musicElement->second;
	}
	else
	{
		Mix_Music* music = Mix_LoadMUS(absFileName.c_str());
		if (music != NULL)
		{
			musics.insert(std::make_pair(absFileName, music));
			return music;
		}
		else
		{
            std::cout << Mix_GetError() << std::endl;
			throw Exception("Failed to load file: " + absFileName);
		}
	}
}

void SoundManager::releaseMusic(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + AUDIO_DIR + fileName;
	// If the resource already exists, check its tracker count.
	// If it is currently 1, we are removing the last handle to it
	// so we need to free the resource and remove it from our map.
	//
	// Otherwise, just decrease the count in the tracker
	MusicIterator musicElement = musics.find(absFileName);
	if (musicElement != musics.end())
	{
		Mix_FreeMusic(musicElement->second);
		musics.erase(musicElement);
	}

}

Mix_Chunk* const SoundManager::acquireSound(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + AUDIO_DIR + fileName;
	SoundIterator soundElement = sounds.find(absFileName);

	// If we've already loaded this resource, simply increment the counter
	// in the tracker and return the surface
	//
	// Otherwise, load it and add it to the tracker with an initial count of 1
	if (soundElement != sounds.end())
	{
		return soundElement->second;
	}
	else
	{
		Mix_Chunk* sfxChunk = Mix_LoadWAV(absFileName.c_str());
		if (sfxChunk != NULL)
		{
			sounds.insert(std::make_pair(absFileName, sfxChunk));
			return sfxChunk;
		}
		else
		{
			throw Exception("Failed to load file: " + absFileName);
		}
	}
}

void SoundManager::releaseSound(const std::string& fileName)
{
	std::string absFileName = RESOURCE_DIR + AUDIO_DIR + fileName;
	// If the resource already exists, check its tracker count.
	// If it is currently 1, we are removing the last handle to it
	// so we need to free the resource and remove it from our map.
	//
	// Otherwise, just decrease the count in the tracker
	SoundIterator soundElement = sounds.find(absFileName);
	if (soundElement != sounds.end())
	{
		Mix_FreeChunk(soundElement->second);
		sounds.erase(soundElement);
	}
}

void SoundManager::addSound(std::string filename, std::string lookupStr)
{
	if (lookupStr != "")
	{
		LookUpIterator soundIt;
		for (soundIt = soundLookup.begin(); soundIt != soundLookup.end();
				++soundIt)
		{
			if (soundIt->second == lookupStr)
			{
				throw std::runtime_error(
						"Masking filename " + lookupStr + " with lookup "
								+ lookupStr);
			}
		}
		LookUpIterator it = soundLookup.find(lookupStr);
		if (it == soundLookup.end())
		{
			soundLookup.insert(std::make_pair(lookupStr, filename));
		}
	}
	acquireSound(filename);
}

void SoundManager::removeSound(std::string name)
{
	LookUpIterator it = soundLookup.find(name);
	if (it != soundLookup.end())
	{
		name = it->second;
		soundLookup.erase(it);
	}
	releaseSound(name);
}

void SoundManager::addMusic(std::string filename, std::string lookupStr)
{
	if (lookupStr != "")
	{
		LookUpIterator musicIt;
		for (musicIt = musicLookup.begin(); musicIt != musicLookup.end();
				++musicIt)
		{
			if (musicIt->second == lookupStr)
			{
				throw std::runtime_error(
						"Masking filename " + lookupStr + " with lookup "
								+ lookupStr);
			}
		}

		LookUpIterator it = musicLookup.find(lookupStr);
		if (it == musicLookup.end())
		{
			musicLookup.insert(std::make_pair(lookupStr, filename));
		}
	}
	acquireMusic(filename);
}

void SoundManager::removeMusic(std::string name)
{
	LookUpIterator it = musicLookup.find(name);
	if (it != musicLookup.end())
	{
		name = it->second;
		musicLookup.erase(it);
	}
	releaseMusic(name);
}
}

