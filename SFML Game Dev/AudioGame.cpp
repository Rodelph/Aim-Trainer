#include "AudioGame.h"

AudioGame::AudioGame() { this->initAudio(); }

AudioGame::~AudioGame() { this->stopSFX(); this->stopBGM(); }

void AudioGame::initAudio()
{
	if (!this->bufferSfx.loadFromFile(this->ioFile->getSFXFile())) { std::cout << this->ioFile->getSfxError() << std::endl; }
	else { this->soundHit.setBuffer(this->bufferSfx); }

	if (!this->musicBG.openFromFile(this->ioFile->getBGMFile())) { std::cout << this->ioFile->getBgmError() << std::endl; }
	else { this->playBGM(); }
}

void AudioGame::playSFX() { this->soundHit.play(); }

void::AudioGame::stopSFX() { this->soundHit.stop(); }

void AudioGame::playBGM() { this->musicBG.play(); this->musicBG.setLoop(true); }

void AudioGame::stopBGM() { this->musicBG.stop(); }