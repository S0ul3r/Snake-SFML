//#include "Platform/Platform.hpp"
#include "Core/Game.h"

int main()
{

    // for(int i=0; i<99;i++)
	//     gameBoard.placeFood();

	// gameBoard.debug_display();


	// sf::RenderWindow window;
	// sf::Event event;

	// while (window.isOpen())
	// {
	// 	while (window.pollEvent(event))
	// 	{
	// 		if (event.type == sf::Event::Closed)
	// 			window.close();
	// 	}
	// 	window.clear();
	// 	window.display();
	// }
	Game game = Game(10, 10);
	game.run();
	return 0;
}
