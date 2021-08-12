#pragma once

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

	public:
		AudioGame();
		virtual ~AudioGame();

		//SFX Functions
		void initAudio();
		void playSFX();
		void stopSFX();
		void pauseSFX();
		void setVolumeSFX(int vol);
		void setPitchSFX(int pitch);

		//BGM Functions
		void playBGM();
		void pauseBGM();
		void stopBGM();
		void setVolumeBGM(int vol);
		void setPitchBGM(int pitch);
};

