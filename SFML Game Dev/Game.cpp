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
	this->health = 200;
	this->enemySpawnTimerMax = 1.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 3;
	this->mouseHeld = false;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Hit me Up !", sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(true);
}


void Game::initEnemiesRect()
{
	this->enemyRect.setPosition(100.f, 100.f);
	this->enemyRect.setSize(sf::Vector2f(100.f, 100.f));
	this->enemyRect.setOutlineColor(sf::Color::Green);
	this->enemyRect.setOutlineThickness(1.f);
	this->enemyRect.setScale(0.5f, 0.5f);
}

void Game::initEnemiesCirc()
{
	this->enemyCircle.setPosition(100.f, 100.f);
	this->enemyCircle.setRadius(20.f);
	this->enemyCircle.setOutlineColor(sf::Color::Black);
	this->enemyCircle.setOutlineThickness(1.f);
	this->enemyCircle.setScale(0.5f, 0.5f);
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
	this->uiFpsStats.setPosition(735, 0);
	this->uiFpsStats.setString("NONE");
}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initTextStats();
	this->initTextFps();
	this->initEnemiesRect();
	this->initEnemiesCirc();
	this->initAudio();
}

Game::~Game()
{
	delete this->window;
}

void Game::spawnEnemyRect()
{
	//Spawns enemies and sets their color and positions 
	//	   Sets a random position
	// 	   Sets a random color
	// 	   Adds enemy to the vector
	//	   Moves the enemies
	//	   Removes the edge of the enemies from the screen

	this->enemyRect.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyRect.getSize().x)),
		0.f
	);
	int type = rand() % 5;
	switch (type)
	{
		case 0:
			this->enemyRect.setFillColor(sf::Color::Green);
			this->enemyRect.setSize(sf::Vector2f(100.f, 100.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyRect.setFillColor(sf::Color::Red);
			this->enemyRect.setSize(sf::Vector2f(50.f, 50.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyRect.setFillColor(sf::Color::Cyan);
			this->enemyRect.setSize(sf::Vector2f(30.f, 30.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;
		case 3:
			this->enemyRect.setFillColor(sf::Color::Blue);
			this->enemyRect.setSize(sf::Vector2f(20.f, 20.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyRect.setFillColor(sf::Color::Magenta);
			this->enemyRect.setSize(sf::Vector2f(15.f, 15.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyRect.setFillColor(sf::Color::White);
			this->enemyRect.setSize(sf::Vector2f(10.f, 10.f));
			this->enemyRect.setOutlineThickness(1.f);
			this->enemyRect.setScale(0.5f, 0.5f);
			break;
	}

	//Spaw, the enemies
	this->enemiesRect.push_back(this->enemyRect);
}

void Game::spawnEnemyCircle()
{
	//Spawns enemies and sets their color and positions 
//	   Sets a random position
// 	   Sets a random color
// 	   Adds enemy to the vector
//	   Moves the enemies
//	   Removes the edge of the enemies from the screen

	this->enemyCircle.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyCircle.getRadius())),
		0.f
	);
	int type = rand() % 5;
	switch (type)
	{
		case 0:
			this->enemyCircle.setFillColor(sf::Color::Green);
			this->enemyCircle.setRadius(10.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyCircle.setFillColor(sf::Color::Red);
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyCircle.setFillColor(sf::Color::Cyan);
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f); 
			break;
	
		case 3:
			this->enemyCircle.setFillColor(sf::Color::Blue);
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyCircle.setFillColor(sf::Color::Magenta);
			this->enemyCircle.setRadius(40.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyCircle.setFillColor(sf::Color::White);
			this->enemyCircle.setRadius(50.f);
			this->enemyCircle.setOutlineThickness(1.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;
	}
	//Spaw, the enemies
	this->enemiesCirc.push_back(this->enemyCircle);
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

void Game::updateEnemiesRect()
{
	//Update the timer for enemy spawning
	if (this->enemiesRect.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemyRect();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemiesRect.size(); i++)
	{
		bool deleted = false;
		this->enemiesRect[i].move(0.f, 5.f);
		if (this->enemiesRect[i].getPosition().y > this->window->getSize().y)
		{
			this->enemiesRect.erase(this->enemiesRect.begin() + i);
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
			for (size_t i = 0; i < this->enemiesRect.size() && deleted == false; i++)
			{
				if (this->enemiesRect[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Deleting enemies and point system
					if (this->enemiesRect[i].getFillColor() == sf::Color::Green)
						this->points += 10;
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Red)
						this->points += 20;
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Blue)
						this->points += 50;
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Cyan)
						this->points += 100;
					else if (this->enemiesRect[i].getFillColor() == sf::Color::Magenta)
						this->points += 200;
					else if (this->enemiesRect[i].getFillColor() == sf::Color::White)
						this->points += 500;

					deleted = true;

					this->enemiesRect.erase(this->enemiesRect.begin() + i);

					//Sfx when u hit a target
					this->playSFX();
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateEnemiesCirc()
{
	//Update the timer for enemy spawning
	if (this->enemiesCirc.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemyCircle();
			this->enemySpawnTimer = 10.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//Move the enemies
	for (int i = 0; i < this->enemiesCirc.size(); i++)
	{
		bool deleted = false;
		this->enemiesCirc[i].move(0.f, 5.f);
		if (this->enemiesCirc[i].getPosition().y > this->window->getSize().y)
		{
			this->enemiesCirc.erase(this->enemiesCirc.begin() + i);
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
			for (size_t i = 0; i < this->enemiesCirc.size() && deleted == false; i++)
			{
				if (this->enemiesCirc[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Deleting enemies and point system
					if (this->enemiesCirc[i].getFillColor() == sf::Color::Green)
						this->points += 10;
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Red)
						this->points += 20;
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Blue)
						this->points += 50;
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Cyan)
						this->points += 100;
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::Magenta)
						this->points += 200;
					else if (this->enemiesCirc[i].getFillColor() == sf::Color::White)
						this->points += 500;

					deleted = true;

					this->enemiesCirc.erase(this->enemiesCirc.begin() + i);

					//Sfx when u hit a target
					this->playSFX();
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
		this->updateEnemiesRect();
		this->updateEnemiesCirc();
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

void Game::renderEnemiesRect(sf::RenderTarget& target)
{
	for (auto& e : this->enemiesRect)
	{
		target.draw(e);
	}
}

void Game::renderEnemeiesCirc(sf::RenderTarget& target)
{
	for (auto& e : this->enemiesCirc)
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
	this->renderEnemiesRect(*this->window);
	this->renderEnemeiesCirc(*this->window);
	this->renderTextFps(*this->window);
	this->renderTextStats(*this->window);
	this->window->display();
}