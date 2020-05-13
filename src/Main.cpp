#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include "Platform/Platform.hpp"
#include "Core/Game.h"

//Locals:
int width 					= 15;
int height 					= 15;
int cellSize 				= 32;
bool dirFlag 				= false;
sf::Time sleepTime 			= sf::seconds(0.25f);
sf::Color cellColor 		= sf::Color::Black;
sf::Color snakeColor 		= sf::Color::Green;
sf::Color borderColor 		= sf::Color::Magenta;
sf::Color foodColor 		= sf::Color::Yellow;
sf::Font font;
sf::Text text;
sf::Text scoreText;

//Sort best scores
void sortFile(std::string& fileLocation);
void sortFile(std::string& fileLocation)
{
	std::fstream myFile(fileLocation);
	std::string s;
	std::vector<int> v;
	while(myFile >> s){
		v.push_back(std::stoi(s));
	}
	std::sort(v.begin(),v.end(), std::greater<int>());
	std::fstream newFile(fileLocation, std::ios::out | std::ios::trunc);
	for(auto it = v.begin();it!=v.end();it++){
		newFile << std::to_string(*it)+"\n";
	}
}
//Getting best scores
std::string getScores(std::string& fileLocation);
std::string getScores(std::string& fileLocation){
	std::ifstream myFile(fileLocation);
	std::string s;
	std::string outputString = "";
	int i =0;
	while(myFile >> s && i < 10){
		outputString += s;
		outputString += "\n";
		i++;
	}
	return outputString;
}

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
	std:: fstream scores;
	scores.open("src/Media/Scores.txt", std::ios::app );
	sf::RenderWindow window (sf::VideoMode(cellSize*width, cellSize*height), "SNAKE");
	Game game(width, height);
	//Settings for the text
	font.loadFromFile("src/Media/Font.ttf");
	text.setFont(font);
	text.setCharacterSize(45);
	text.setFillColor(sf::Color::White);
	scoreText.setFont(font);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	bool scoreSaved = false;

	while(true){
		sf::Event event;
		//Flag for fixing a bug where you can change direction two times
		dirFlag = false;
		//Get gamestate
		gameState state = game.getGamestate();

		while(window.pollEvent(event)){
			if(event.type == sf::Event::Closed){
				window.close();
				scores.close();
				return 0;
			}

			//Event Handling
			gameState currState = game.getGamestate();
			if(event.type == sf::Event::KeyPressed  &&  dirFlag == false){
				if(event.key.code == sf::Keyboard::Escape){
					if (currState == RUNNING) {
						game.setGamestate(PAUSE);
					}
					if (currState == PAUSE) {
						game.setGamestate(RUNNING);
					}
				}
				if(event.key.code == sf::Keyboard::Space && state == LOSE){
					scoreSaved = false;
					game = Game(width, height);
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

		//Checks if the game is running, lost or paused
		if (state == RUNNING) {
			game.update();
			//Clear and draw board again
			window.clear();
			for(int i =0; i<height;i++){
				for(int j =0 ;j<width;j++){
					draw(window, j, i, game.getType(i,j));
				}
			}
			scoreText.setString("Score: " + std::to_string(game.getScore()));
			scoreText.setPosition(5, 5);
			window.draw(scoreText);
		}
		else if (state == LOSE) {
			if(!scoreSaved){
				scores << std::to_string(game.getScore())+"\n";
				scoreSaved = true;
				std::string scores = "src/Media/Scores.txt";
				sortFile(scores);
			}
			std::string path = "src/Media/Scores.txt";
			std::string scores = getScores(path);
			text.setCharacterSize(25);
			text.setString("You Lost, press Space\nto try agian\nBest scores:\n" + scores);
			text.setPosition(50, 30);
			window.draw(text);
		}
		else if (state == PAUSE) {
			text.setString("Game paused, \n resume with escape");
			text.setPosition(10, cellSize*height/3);
			window.draw(text);
		}
		window.display();
		sf::sleep(sleepTime);
	}
	return 0;
}