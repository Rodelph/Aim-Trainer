#pragma once

#ifndef AUDIOGAME_H
#define AUDIOGAME_H

#include <SFML/Audio.hpp>
#include <iostream>

class AudioGame
{
	private:
		//SFX Variables
		sf::SoundBuffer bufferSfx;
		sf::Sound soundHit;

		//BGM Variables
		sf::Music musicBG;

		//Audio initializer
		void initAudio();

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
#endif