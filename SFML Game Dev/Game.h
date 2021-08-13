#pragma once

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "AudioGame.h"
#include "Texture.h"


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

		//Texture game obj
		Texture* textureObj;
		
		//Fonts
		sf::Font font;

		//Text
		sf::Text uiTextStats;
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
		void initTextStats();
		void initTextFps();
		void initTexture();
		void initHpBar();

	public :
		//Constructors / Destructors
		Game();
		virtual ~Game();
	
		//Accessors
		const bool running() const;
		const bool getEndGame() const;
	
		//Functions
		void pollEvents();
		void spawnEnemyCircle();
		
		void update();
		void updateMousePos();
		void updateHpBar();
		void updateEnemies();
		void updateTextStats();
		void updateTextFps();
		void updateSpawn();

		void render();
		void rednderHpBar(sf::RenderTarget& target);
		void renderEnemeiesCirc(sf::RenderTarget& target);
		void renderTextStats(sf::RenderTarget& target);
		void renderTextFps(sf::RenderTarget& target);
};

#endif