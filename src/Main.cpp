#include "Platform/Platform.hpp"
#include "Core/Game.h"

//Locals:
int width 					= 15;
int height 					= 15;
int cellSize 				= 32;
bool dirFlag 				= false;
sf::Time sleepTime 			= sf::seconds(0.05f);
sf::Color cellColor 		= sf::Color::Black;
sf::Color snakeColor 		= sf::Color::Green;
sf::Color borderColor 		= sf::Color::Magenta;
sf::Color foodColor 		= sf::Color::Yellow;

//SFML draw board
void draw(sf::RenderWindow& win, int i, int j, cellType);
void draw(sf::RenderWindow& win, int i, int j, cellType t){
	sf::RectangleShape r(sf::Vector2f(cellSize, cellSize));
	r.setPosition(i*cellSize, j*cellSize);
	if(t == cellType::EMPTY){
		r.setFillColor(cellColor);
	}else if(t == cellType::SNAKE){
		r.setFillColor(snakeColor);
	}else if(t == cellType::FOOD){
		r.setFillColor(foodColor);
	}
	r.setOutlineColor(borderColor);
	r.setOutlineThickness(3);
	win.draw(r);
}


int main()
{
	sf::RenderWindow window (sf::VideoMode(cellSize*width, cellSize*height), "SNAKE");
	Game game(width, height);

	while(true){
		sf::Event event;

		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
				return 0;
			}

			//Setting directions depending on snake movement and key pressed
			if(event.type == sf::Event::KeyPressed  &&  dirFlag == false){
				if(event.key.code == sf::Keyboard::Escape){
					game.snake.setGamestate(PAUSE);
				}
				if(event.key.code == sf::Keyboard::PageUp){
					sleepTime = sleepTime - sf::seconds(0.01f);
				}
				if(event.key.code == sf::Keyboard::PageDown){
					sleepTime = sleepTime + sf::seconds(0.01f);
				}
				if(event.key.code == sf::Keyboard::Up){
					direction x = game.getDirection();
					if(x == direction::DIR_LEFT || x == direction::DIR_RIGHT){
						game.setDirection(direction::DIR_UP);
						dirFlag = true;
					}
				}
				if(event.key.code == sf::Keyboard::Down){
					direction x = game.getDirection();
					if(x == direction::DIR_LEFT || x == direction::DIR_RIGHT){
						game.setDirection(direction::DIR_DOWN);
						dirFlag = true;
					}
				}
				if(event.key.code == sf::Keyboard::Left ){
					direction x = game.getDirection();
					if(x == direction::DIR_UP || x == direction::DIR_DOWN){
						game.setDirection(direction::DIR_LEFT);
						dirFlag = true;
					}
				}
				if(event.key.code == sf::Keyboard::Right){
					direction x = game.getDirection();
					if(x == direction::DIR_UP || x == direction::DIR_DOWN){
						game.setDirection(direction::DIR_RIGHT);
						dirFlag = true;
					}
				}
			}
		}

		//Flag for fixing a bug where you can change direction two times
		dirFlag = false;
		gameState state = game.snake.getGamestate();

		//Check if user lost the game
		if (state != PAUSE || state != LOSE) {
			game.update();
		}
		game.display();

		//Clear and draw board again
		window.clear();
		for(int i =0; i<height;i++){
			for(int j =0 ;j<width;j++){
				draw(window, j, i, game.getType(i,j));
			}
		}
		window.display();
		sf::sleep(sleepTime);
	}
	return 0;
}
