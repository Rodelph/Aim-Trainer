#pragma once

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include <ctime>

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

		//Game logic
		int points;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;

		//Mouse Positions 
		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		//Functions to initialize the window
		void initializeVariables();
		void initWindow();
		void initEnemies();

	public :
		//Constructors / Destructors
		Game();
		virtual ~Game();
	
		//Accessors
		const bool running() const;
	
		//Functions
		void update();
		void updateMousePos();
		void render();
		void pollEvents();
		void spawnEnemy();
		void updateEnemies();
		void renderEnemies();
};

#endif
