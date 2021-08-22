#pragma once

#include <SFML/Audio.hpp>
#include "IOFile.h"

class AudioGame
{
	private:
		//SFX Variables
		sf::SoundBuffer bufferSfx;
		sf::Sound soundHit;

		//BGM Variables
		sf::Music musicBG;

		IOFile* ioFile = new IOFile();

		//Audio initializer
		void initAudio();
		void initIOFiles();

	public:
		AudioGame();
		virtual ~AudioGame();

		//SFX Functions
		void playSFX();
		void stopSFX();
	
		//BGM Functions
		void playBGM();
		void stopBGM();
};