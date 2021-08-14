#include "AudioGame.h"

AudioGame::AudioGame() { this->initAudio(); }

AudioGame::~AudioGame() { this->stopSFX(); this->stopBGM(); }

void AudioGame::initAudio()
{
	if (!this->bufferSfx.loadFromFile("src/Music/hit.wav")) { std::cout << "INFO::GAME::SFX:: SFX files not loaded !!" << std::endl; }
	else { this->soundHit.setBuffer(this->bufferSfx); }

	if (!this->musicBG.openFromFile("src/Music/music.wav")) { std::cout << "INFO::GAME::Music:: Music files not loaded !!" << std::endl; }
	else { this->playBGM(); }
}

void AudioGame::playSFX() { this->soundHit.play(); }

void::AudioGame::stopSFX() { this->soundHit.stop(); }

void AudioGame::playBGM() { this->musicBG.play(); this->musicBG.setLoop(true); }

void AudioGame::stopBGM() { this->musicBG.stop(); }