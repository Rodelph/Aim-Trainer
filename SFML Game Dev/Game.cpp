#include "Game.h"

//
//
//
//
//		Audio stuff
//
//
//
//

void Game::initAudio()
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

void Game::playSFX()
{
	this->soundHit.play();
}

void Game::stopSFX()
{
	this->soundHit.stop();
}

void Game::pauseSFX()
{
	this->soundHit.pause();
}

void Game::setVolumeSFX(int vol)
{
	this->soundHit.setVolume(vol);
}

void Game::setPitchSFX(int pitch)
{
	this->soundHit.setPitch(pitch);
}

void Game::playBGM()
{
	this->musicBG.play();
}

void Game::pauseBGM()
{
	this->musicBG.pause();
}

void Game::stopBGM()
{
	this->musicBG.stop();
}

void Game::setVolumeBGM(int vol)
{
	this->musicBG.setVolume(vol);
}

void Game::setPitchBGM(int pitch)
{
	this->musicBG.setPitch(pitch);
}

//
// 
// 
// 
//		Game Stuff
// 
// 
//

void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 500;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->mouseHeld = false;
	this->endGame = false;
	this->clock;
	this->uiTextStats;
	this->uiFpsStats;
	this->time;
	this->clock;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}


void Game::initEnemies()
{
	this->enemy.setPosition(100.f, 100.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);
	this->enemy.setScale(0.5f, 0.5f);
}

void Game::initFont()
{
	if (!this->font.loadFromFile("src/Fonts/Dosis-Light.ttf"))
		std::cout << "Info::GAME::InitFonts:: Font not loaded !" << std::endl;
	else
		this->font.loadFromFile("src/Fonts/Dosis-Light.ttf");
}

void Game::initTextStats()
{
	this->uiTextStats.setFont(this->font);
	this->uiTextStats.setCharacterSize(24);
	this->uiTextStats.setFillColor(sf::Color::Black);
	this->uiTextStats.setPosition(0, 0);
	this->uiTextStats.setString("NONE");
}

void Game::initTextFps()
{
	this->uiFpsStats.setFont(this->font);
	this->uiFpsStats.setCharacterSize(18);
	this->uiFpsStats.setFillColor(sf::Color::Black);
	this->uiFpsStats.setPosition(700, 0);
	this->uiFpsStats.setString("NONE");
}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initTextStats();
	this->initTextFps();
	this->initEnemies();
	this->initAudio();
}

Game::~Game()
{
	delete this->window;
}

void Game::spawnEnemy()
{
	//Spawns enemies and sets their color and positions 
	//	   Sets a random position
	// 	   Sets a random color
	// 	   Adds enemy to the vector
	//	   Moves the enemies
	//	   Removes the edge of the enemies from the screen

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Spaw, the enemies
	this->enemies.push_back(this->enemy);

	//Remove the enemies
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Public functions
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
		}
	}
}

void Game::updateEnemies()
{
	//Update the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 5.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			//Hp loss
			this->health -= 1;
		}
	}
	//Check if clicked on
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Sfx
					this->playSFX();
					//Gain points
					this->points += 1;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateMousePos()
{
	/*
	Updates the mouse positions :
		Mouse position relateve to window (Vector2i)
	*/
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateTextStats()
{
	std::stringstream ssStats;
	ssStats << "Points : " << this->points << "\n"
		<< "Health : " << this->health << "\n";
	this->uiTextStats.setString(ssStats.str());
}

void Game::updateTextFps()
{
	std::stringstream ssFps;
	this->time = this->clock.getElapsedTime();
	ssFps << "FPS : " << (int)(1.0f / this->time.asSeconds()) << "\n";
	this->uiFpsStats.setString(ssFps.str());
	this->clock.restart().asSeconds();
}

void Game::update()
{
	this->pollEvents();
	if(!this->endGame)
	{
		this->updateMousePos();
		this->updateEnemies();
		this->updateTextStats();
		this->updateTextFps();
	}

	if (this->health == 0)
	{
		std::cout << "You lost !!" << std::endl;
		this->endGame = true;
	}
}

void Game::renderTextStats(sf::RenderTarget& target)
{
	target.draw(this->uiTextStats);
}

void Game::renderTextFps(sf::RenderTarget& target)
{
	target.draw(this->uiFpsStats);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	/*Renders the game object by : 
		Clearing the old frame
		Rendering objects
		Displaying them
	*/
	this->window->clear(sf::Color(245, 245, 220, 255));
	this->renderEnemies(*this->window);
	this->renderTextFps(*this->window);
	this->renderTextStats(*this->window);
	this->window->display();
}