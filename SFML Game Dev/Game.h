#pragma once

#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

//Mini game engine class (Wrapper class)

#ifndef GAME_H
#define GAME_H

class Game
{
	private :
		//Variables for the window and events
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		//Game objects
		sf::RectangleShape enemy;
		std::vector<sf::RectangleShape> enemies;

		//Res
		sf::Font font;

		//Text
		sf::Text uiText;

		//Game logic
		unsigned points;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;
		bool mouseHeld;
		int health;
		bool endGame;

		//Mouse Positions 
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		//Functions to initialize the window
		void initializeVariables();
		void initWindow();
		void initEnemies();
		void initFont();
		void initText();

	public :
		//Constructors / Destructors
		Game();
		virtual ~Game();
	
		//Accessors
		const bool running() const;
		const bool getEndGame() const;
	
		//Functions
		void pollEvents();

		void update();
		void updateMousePos();
		void spawnEnemy();
		void updateEnemies();
		void updateText();

		void render();
		void renderEnemies(sf::RenderTarget& target);
		void renderText(sf::RenderTarget& target);
};

#endif