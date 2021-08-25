#include "AudioGame.h"

AudioGame::AudioGame() { this->initAudioBGM(); this->initAudioSFX(); }

AudioGame::~AudioGame() { this->stopBGM(); }

void AudioGame::initAudioSFX()
{
	if (!this->bufferSfx.loadFromFile(this->ioFile->getSFXFile())) { std::cout << this->ioFile->getSfxError() << std::endl; }
	else { this->soundHit.setBuffer(this->bufferSfx); }
}

void AudioGame::initAudioBGM()
{
	if (!this->bgm.openFromFile(this->ioFile->getBGMFile())) { std::cout << this->ioFile->getBgmError() << std::endl; }
	else { this->playBGM(); }
}

void AudioGame::playSFX() { this->soundHit.play(); }

void AudioGame::playBGM() { this->bgm.play(); this->bgm.setLoop(true); }

void AudioGame::stopBGM() { this->bgm.stop(); }