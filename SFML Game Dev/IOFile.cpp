#include "IOFile.h"


const std::string IOFile::getFontDir() const { return this->dosisFont; }

const std::string IOFile::getError() const { return this->gmErrorInitFont; }

const std::string IOFile::getSfxError() const { return this->gmErrorInitSFX; }

const std::string IOFile::getBgmError() const { return this->gmErrorInitBGM; }

const std::string IOFile::getBGMFile() const { return this->bgmFile; }

const std::string IOFile::getSFXFile() const { return this->sfxFile; }

const std::string IOFile::getTitle() const { return this->titleGame; }
