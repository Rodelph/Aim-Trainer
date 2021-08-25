#pragma once

#include <SFML/Audio.hpp>
#include "IOFile.h"

class AudioGame
{
	private:
		//SFX Variables
		sf::SoundBuffer bufferSfx, bufferBGM;
		sf::Sound soundHit;

		//BGM var
		sf::Music bgm;

		//IO object
		IOFile* ioFile = new IOFile();

		//Audio initializer
		void initAudioBGM();
		void initAudioSFX();

	public:
		AudioGame();
		virtual ~AudioGame();

		//SFX Functions
		void playSFX();
	
		//BGM Functions
		void playBGM();
		void stopBGM();
};