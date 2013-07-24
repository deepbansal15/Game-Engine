/*
 * SoundManager.h
 *
 *  Created on: Jan 17, 2013
 *      Author: nathan
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_
#include "Globals.h"
#include "Singleton.h"
#include "ResourceManager.h"
#include <stdexcept>

namespace TileEngine
{

//play music by filename, check if filename in map, else acquire and add to map. stop music and play new music
//delete should release music instances
class SoundManager
{
	friend class Singleton<SoundManager>;

	typedef std::map<std::string, Mix_Music*>::iterator MusicIterator;
	typedef std::map<std::string, Mix_Chunk*>::iterator SoundIterator;
	typedef std::map<std::string, std::string>::iterator LookUpIterator;

public:

	void setSoundVolume(int Volume);
	int getSoundVolume() const;

	void setMusicVolume(int Volume);
	int getMusicVolume() const;

	void playMusic(std::string filename);
	void pauseMusic();
	void resumeMusic();
	void stopMusic();

	void playSound(std::string filename);

	void addSound(std::string filename, std::string lookUpName = "");
	void removeSound(std::string filename);
	void addMusic(std::string filename, std::string lookUpName = "");
	void removeMusic(std::string filename);

	void deleteAllMusic();
	void deleteAllSounds();

private:
	SoundManager();
	virtual ~SoundManager();
	SoundManager( const SoundManager&);
	SoundManager& operator=(const SoundManager&);

	Mix_Music* const acquireMusic(const std::string& filename);
	Mix_Chunk* const acquireSound(const std::string& filename);
	void releaseMusic(const std::string& filename);
	void releaseSound(const std::string& filename);

	std::map<std::string, Mix_Music*> musics;
	std::map<std::string, Mix_Chunk*> sounds;
	std::map<std::string, std::string> musicLookup;
	std::map<std::string, std::string> soundLookup;

	int soundVolume;
	int musicVolume;
};

#define SoundMgr TileEngine::Singleton<SoundManager>()
}
#endif /* SOUNDMANAGER_H_ */
