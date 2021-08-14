#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AudioGame.h"

class Game
{
	private :
		//Variables for the window and events
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		//Game objects
		sf::CircleShape enemyCircle;
		sf::RectangleShape hpBar, hpBorder;

		std::vector<sf::CircleShape> enemiesCirc;
		
		//Fonts
		sf::Font font;

		//Text
		sf::Text uiPointStats;
		sf::Text uiLevelStats;
		sf::Text uiFpsStats;

		//AduioGame object pointer
		AudioGame* audGame;

		//Game logic
		unsigned points;
		float enemySpawnTimerCirc;
		float enemySpawnTimerMaxCirc;
		int maxEnemiesCirc;
		bool mouseHeld;
		float health;
		bool endGame;

		//Timers
		sf::Clock clock;
		sf::Time time;

		//Mouse Positions 
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		//Functions to initialize the window
		void initializeVariables();
		void initWindow();
		void initAudio();
		void initEnemiesCirc();
		void initFont();
		void initPointStats();
		void initLevelStats();
		void initFpsStats();
		void initHpBar();

	public :
		//Constructors / Destructors
		Game();
		virtual ~Game();
	
		//Accessors
		const bool running() const;
		const bool getEndGame() const;
		void pollEvents();

		//Functions
		void updateEnemyCircle();
		void update();
		void updateMousePos();
		void updateHpBar();
		void updateEnemies();
		void updatePointStats();
		void updateFpsStats();
		void updateLevelStats();
		void updateSpawn();

		void render();
		void rednderHpBar(sf::RenderTarget& target);
		void renderEnemeiesCirc(sf::RenderTarget& target);
		void renderLevelStats(sf::RenderTarget& target);
		void renderPointStats(sf::RenderTarget& target);
		void renderFpsStats(sf::RenderTarget& target);
};

#endif