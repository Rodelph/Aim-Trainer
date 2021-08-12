#include "AudioGame.h"


AudioGame::AudioGame()
{
	this->initAudio();
}

AudioGame::~AudioGame()
{
	this->stopSFX();
	this->stopBGM();
}

void AudioGame::initAudio()
{
	if (!this->bufferSfx.loadFromFile("src/Music/hit.wav"))
		std::cout << "INFO::GAME::SFX:: SFX files not loaded !!" << std::endl;
	else
		this->soundHit.setBuffer(this->bufferSfx);

	if (!this->musicBG.openFromFile("src/Music/music.wav"))
		std::cout << "INFO::GAME::Music:: Music files not loaded !!" << std::endl;
	else
		this->playBGM();
}

void AudioGame::playSFX()
{
	this->soundHit.play();
}

void AudioGame::stopSFX()
{
	this->soundHit.stop();
}

void AudioGame::pauseSFX()
{
	this->soundHit.pause();
}

void AudioGame::setVolumeSFX(int vol)
{
	this->soundHit.setVolume(vol);
}

void AudioGame::setPitchSFX(int pitch)
{
	this->soundHit.setPitch(pitch);
}

void AudioGame::playBGM()
{
	this->musicBG.play();
}

void AudioGame::pauseBGM()
{
	this->musicBG.pause();
}

void AudioGame::stopBGM()
{
	this->musicBG.stop();
}

void AudioGame::setVolumeBGM(int vol)
{
	this->musicBG.setVolume(vol);
}

void AudioGame::setPitchBGM(int pitch)
{
	this->musicBG.setPitch(pitch);
}