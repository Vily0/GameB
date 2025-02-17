#include "GameBoard.h"
#include "Difficulty.h"

int main()
{
	const int BOARD_WIDTH = 6;
	const int BOARD_HEIGHT = 6;
	const float TILE_SIZE = 100.f;

	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(BOARD_WIDTH * (int)TILE_SIZE, BOARD_HEIGHT * (int)TILE_SIZE), "MEMORY GAME");
	window.setFramerateLimit(60);
	int difficulty = selectDifficulty();
	std::cout << "Selected Difficulty: " << difficulty << std::endl;

	GameBoard gameBoard(&window, TILE_SIZE, BOARD_WIDTH, BOARD_HEIGHT, difficulty);

	while (window.isOpen() && !gameBoard.checkExit())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		gameBoard.update(window);

		window.clear();
		gameBoard.render(window);
		window.display();

	}

	window.close();

	return 0;
}