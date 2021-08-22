#pragma once
#include <iostream>

class IOFile
{
	private:
		//Title
		const std::string& titleGame = "Hit me Up !";

		//Music fonts etc
		const std::string& dosisFont = "src/Fonts/Dosis-Light.ttf";
		const std::string& bgmFile = "src/Music/music.wav";
		const std::string& sfxFile = "src/Music/hit.wav";
		
		//Error handling
		const std::string& gmErrorInitFont = "Info::GAME::InitFonts:: Font not loaded !";
		const std::string& gmErrorInitSFX = "INFO::GAME::SFX::SFX files not loaded !!";
		const std::string& gmErrorInitBGM = "INFO::GAME::Music:: Music files not loaded !!";

	public:
		const std::string getFontDir() const;
		const std::string getTitle() const;
		const std::string getFontError() const;
		const std::string getSfxError() const;
		const std::string getBgmError() const;
		const std::string getBGMFile() const;
		const std::string getSFXFile() const;
};