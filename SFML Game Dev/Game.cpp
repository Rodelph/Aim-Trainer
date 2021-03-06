#include "Game.h"

/// 
/// Initialization functions that will initialize everything for the game
/// 

void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 200;

	this->enemySpawnTimerMaxCirc = 1.f;
	this->enemySpawnTimerCirc = this->enemySpawnTimerMaxCirc;
	this->maxEnemiesCirc = 1;

	this->mouseHeld = false;
	this->endGame = false;
	this->pauseGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, this->ioFile->getTitle(), sf::Style::Titlebar | sf::Style::Close);
	this->window->setVerticalSyncEnabled(false);
	this->window->setFramerateLimit(61);
}

void Game::initEnemiesCirc()
{
	this->enemyCircle.setPosition(100.f, 100.f);
	this->enemyCircle.setRadius(20.f);
	this->enemyCircle.setOutlineColor(sf::Color::Black);
	this->enemyCircle.setOutlineThickness(10.f);
	this->enemyCircle.setScale(0.5f, 0.5f);
}

void Game::initFont()
{
	if (!this->font.loadFromFile(this->ioFile->getFontDir())) 
	{ 
		std::cout << this->ioFile->getFontError() << std::endl; 
	}
	else 
	{ 
		this->font.loadFromFile(this->ioFile->getFontDir());
	}
}

void Game::initPointStats()
{
	this->uiPointStats.setFont(this->font);
	this->uiPointStats.setCharacterSize(24);
	this->uiPointStats.setFillColor(sf::Color::Black);
	this->uiPointStats.setPosition(0, 30);
}

void Game::initLevelStats()
{
	this->uiLevelStats.setFont(this->font);
	this->uiLevelStats.setCharacterSize(24);
	this->uiLevelStats.setFillColor(sf::Color::Black);
	this->uiLevelStats.setPosition(0, 60);
}

void Game::initFpsStats()
{
	this->uiFpsStats.setFont(this->font);
	this->uiFpsStats.setCharacterSize(18);
	this->uiFpsStats.setFillColor(sf::Color::Black);
	this->uiFpsStats.setPosition(735, 0);
}

void Game::initHpBar()
{
	this->hpBar.setPosition(2, 5);
	this->hpBar.setSize(sf::Vector2f(200.f, 20.f));
	this->hpBar.setFillColor(sf::Color::Red);
	
	this->hpBorder.setPosition(2, 5);
	this->hpBorder.setSize(sf::Vector2f(200.f, 20.f));
	this->hpBorder.setOutlineColor(sf::Color::Black);
	this->hpBorder.setOutlineThickness(1.f);
}

void Game::initRestart()
{
	this->uiRestart.setFont(this->font);
	this->uiRestart.setPosition(250, 350);
	this->uiRestart.setCharacterSize(24);
	this->uiRestart.setFillColor(sf::Color::Black);
}

void Game::initScore()
{
	this->uiScore.setFont(this->font);
	this->uiScore.setPosition(280, 200);
	this->uiScore.setCharacterSize(24);
	this->uiScore.setFillColor(sf::Color::Black);
}

void Game::initAudio() { this->audGame = new AudioGame(); }

/// 
/// Update functions that will be used to update the game
///  

void Game::updateEnemyCircle()
{
	this->enemyCircle.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemyCircle.getRadius())),
		0.f
	);

	int type = rand() % 5;

	switch (type)
	{
		case 0:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(50.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 1:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(40.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 2:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(30.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f); 
			break;
	
		case 3:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(20.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 4:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(15.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;

		case 5:
			this->enemyCircle.setFillColor(sf::Color(255, 207, 158));
			this->enemyCircle.setRadius(10.f);
			this->enemyCircle.setOutlineThickness(10.f);
			this->enemyCircle.setScale(0.5f, 0.5f);
			break;
	}

	this->enemiesCirc.push_back(this->enemyCircle);
}

void Game::updateHpBar() { this->hpBar.setSize(sf::Vector2f(this->health, 20)); }

void Game::updateEnemies()
{
	if (this->enemiesCirc.size() < this->maxEnemiesCirc)
	{
		if (this->enemySpawnTimerCirc >= this->enemySpawnTimerMaxCirc)
		{
			this->updateEnemyCircle();
			this->enemySpawnTimerCirc = 10.f;
		}
		else
			this->enemySpawnTimerCirc += 1.f;
	}

	for (int i = 0; i < this->enemiesCirc.size(); i++)
	{
		bool deleted = false;
		this->enemiesCirc[i].move(0.f, 5.f);

		if (this->enemiesCirc[i].getPosition().y > this->window->getSize().y)
		{
			this->enemiesCirc.erase(this->enemiesCirc.begin() + i);

			if (this->enemyCircle.getRadius() == 50.f) { this->health -= 5; }

			if (this->enemyCircle.getRadius() == 40.f) { this->health -= 10; }

			if (this->enemyCircle.getRadius() == 30.f) { this->health -= 20; }

			if (this->enemyCircle.getRadius() == 20.f) { this->health -= 30; }

			if (this->enemyCircle.getRadius() == 15.f) { this->health -= 50; }

			if (this->enemyCircle.getRadius() == 10.f) { this->health -= 70; }
		}
	}

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
					if (this->enemyCircle.getRadius() == 50.f)      
					{ 
						this->points += 5; this->health += 2.f;     
					}
					else if (this->enemyCircle.getRadius() == 40.f) 
					{ 
						this->points += 10; this->health += 5.f;    
					}
					else if (this->enemyCircle.getRadius() == 30.f) 
					{ 
						this->health += 10; this->points += 20.f;   
					}
					else if (this->enemyCircle.getRadius() == 20.f) 
					{ 
						this->health += 20; this->points += 30.f;   
					}
					else if (this->enemyCircle.getRadius() == 15.f) 
					{ 
						this->health += 30; this->points += 50.f;   
					}
					else if (this->enemyCircle.getRadius() == 10.f) 
					{ 
						this->hpBar.setSize(sf::Vector2f(200, 20)); 
					}
					 
					if (this->health >= 200.f) this->health = 200.f;  this->points += 100;

					deleted = true;
					
					this->enemiesCirc.erase(this->enemiesCirc.begin() + i);

					this->audGame->playSFX();
				}
			}
		}
	}
	else { this->mouseHeld = false; }
}

void Game::updateMousePos()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updatePointStats()
{
	std::stringstream ssStats;
	ssStats << "Points : " << this->points << "\n";
	this->uiPointStats.setString(ssStats.str());
}

void Game::updateFpsStats()
{
	std::stringstream ssFps;
	this->time = this->clock.getElapsedTime();
	ssFps << "FPS : " << (int)(1.0f / this->time.asSeconds()) << "\n";
	this->uiFpsStats.setString(ssFps.str());
	this->clock.restart().asSeconds();
}

void Game::updateLevelStats()
{
	if (this->points < 400) 
	{ 
		std::stringstream ssLevel;
		ssLevel << "Level : " << 1 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 400)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 2 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 800)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 3 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 1200)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 4 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 1600)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 5 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2000)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 6 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2400)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 7 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
	
	if (this->points >= 2800)
	{
		std::stringstream ssLevel;
		ssLevel << "Level : " << 8 << "\n";
		this->uiLevelStats.setString(ssLevel.str());
	}
}

void Game::updateScore()
{
	std::stringstream score;
	score << "You final score is : " << this->points << "\n";
	this->uiScore.setString(score.str());
}

void Game::updateSpawn()
{
	if (this->points >=  400) this->maxEnemiesCirc = 2;
	if (this->points >=  800) this->maxEnemiesCirc = 3;
	if (this->points >= 1200) this->maxEnemiesCirc = 4;
	if (this->points >= 1600) this->maxEnemiesCirc = 5;
	if (this->points >= 2000) this->maxEnemiesCirc = 6;
	if (this->points >= 2400) this->maxEnemiesCirc = 7;
	if (this->points >= 2800) this->maxEnemiesCirc = 8;
}

void Game::update()
{
	this->pollEvents();

	if (!this->pauseGame && !this->endGame)
	{
		this->updateMousePos();
		this->updateEnemies();
		this->updateHpBar();
		this->updateSpawn();
		this->updatePointStats();
		this->updateFpsStats();
		this->updateLevelStats();
	}

	if (this->pauseGame) { this->audGame->stopBGM(); this->updateScore(); }

	if (this->hpBar.getSize().x <= 0) { this->pauseGame = true; this->hpBar.setSize(sf::Vector2f(0.f, 200.f)); }
}

/// 
/// Render functions that will be used to render the game
/// 


void Game::renderPointStats(sf::RenderTarget& target)   { target.draw(this->uiPointStats); }

void Game::renderFpsStats(sf::RenderTarget& target)     { target.draw(this->uiFpsStats); }

void Game::renderLevelStats(sf::RenderTarget& target)   { target.draw(this->uiLevelStats); }

void Game::renderScore(sf::RenderTarget& target)        { target.draw(this->uiScore); }

void Game::renderHpBar(sf::RenderTarget& target)		{ target.draw(this->hpBorder); target.draw(this->hpBar); }

void Game::renderEnemeiesCirc(sf::RenderTarget& target) { for (auto& e : this->enemiesCirc) { target.draw(e); } }

void Game::render()
{
	this->window->clear(sf::Color(115, 147, 161, 255));
	this->renderEnemeiesCirc(*this->window);
	this->renderHpBar(*this->window);
	this->renderFpsStats(*this->window);
	this->renderPointStats(*this->window);
	this->renderLevelStats(*this->window);
	this->renderScore(*this->window);
	this->window->display();
}

/// 
/// Game States, poll events, constructor and destructor
/// 

const bool Game::running() const { return this->window->isOpen(); }

const bool Game::getEndGame() const { return this->endGame; }

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape) { this->window->close(); }
				break;
		}
	}
}

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFont();
	this->initRestart();
	this->initScore();
	this->initPointStats();
	this->initFpsStats();
	this->initLevelStats();
	this->initAudio();
	this->initHpBar();
	this->initEnemiesCirc();
}

Game::~Game() 
{ 
	delete this->window; 
	this->audGame->~AudioGame(); 
}