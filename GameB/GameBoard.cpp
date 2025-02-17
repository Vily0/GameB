#include "GameBoard.h"

void GameBoard::createBoard(const int board_width, const int board_height)
{
	float x = 0.f;
	float y = 0.f;
	for (size_t i = 0; i < board_height; i++)
	{
		for (size_t j = 0; j < board_width; j++)
		{
			this->tilesVec.push_back(new Tile(sf::Vector2f(x, y), this->tileSize, false));
			x += tileSize;
		}
		y += tileSize;
		x = 0.f;
	}

}

void GameBoard::randomizeBoard()
{
	this->activeTilesVec.clear();
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		this->tilesVec[i]->setActive(false);
		this->tilesVec[i]->setColorInactive();
	}
	std::vector<int> index_vector;
	for (size_t i = 0; i < tilesVec.size(); i++)
	{
		index_vector.push_back(i);
	}
	int tiles_added = 0;
	int index = -1;
	while (tiles_added != this->nrOfActiveTiles)
	{

		index = rand() % index_vector.size();
		this->tilesVec[index_vector[index]]->setActive(true);
		this->tilesVec[index_vector[index]]->setColorInactive();
		this->activeTilesVec.push_back(index_vector[index]);
		index_vector.erase(index_vector.begin() + index);
		tiles_added++;


	}
}

void GameBoard::displayOrder()
{
	if (this->displayTimer < 50.f)
	{
		for (size_t i = 0; i < this->tilesVec.size(); i++)
		{
			this->tilesVec[i]->setColorInactive();
		}
	}
	else if (this->displayTimer >= 50.f && this->displayTimer < 100.f)
	{
		for (size_t i = 0; i < this->tilesVec.size(); i++)
		{
			if (this->tilesVec[i]->isActive())
			{
				this->tilesVec[i]->setColorActive();

			}
		}
	}
	else if (this->displayTimer >= 100.f && this->displayTimer < 150.f)
	{
		for (size_t i = 0; i < this->tilesVec.size(); i++)
		{
			this->tilesVec[i]->setColorInactive();
		}
	}

	else
	{
		this->restarting = false;
	}

	this->displayTimer += 1.f;

}

const bool GameBoard::checkSelection()
{
	std::sort(this->activeTilesVec.begin(), this->activeTilesVec.end());
	std::sort(this->selectionVec.begin(), this->selectionVec.end());

	return this->activeTilesVec == this->selectionVec;
}

void GameBoard::updateKeyTime()
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 1.f;
}

void GameBoard::updateBoard()
{

	if (this->restarting)
	{
		this->displayOrder();
	}
	else
	{
		float elapsedTime = this->gameClock.getElapsedTime().asSeconds();
		float timeLeft = this->timerDuration - elapsedTime;

		this->timerText.setString("Time: " + std::to_string((int)timeLeft));

		if (timeLeft <= 0)
		{
			std::cout << "Time's up! You lost this round." << std::endl;
			this->incorrect++;
			this->restart();
			return;
		}

		if (this->tilesSelected < this->nrOfActiveTiles)
		{
			for (size_t i = 0; i < this->tilesVec.size(); i++)
			{
				this->tilesVec[i]->update(this->mousePosView, sf::Mouse::isButtonPressed(sf::Mouse::Left));
				if (this->tilesVec[i]->isPressed() && this->checkKeyTime())
				{
					this->selectionVec.push_back(i);
					this->tilesVec[i]->setColorActive();
					this->tilesSelected++;
					this->resetKeyTime();
				}
			}
		}
		else
		{
			if (this->checkSelection())
			{
				std::cout << "CORRECT!" << std::endl;
				this->correct++;
			}
			else
			{
				std::cout << "INCORRECT!" << std::endl;
				this->incorrect++;
			}
			std::cout << "CORRECT/INCORRECT: " << this->correct << "/" << this->incorrect << std::endl;
			this->restart();
		}
	}
}

GameBoard::GameBoard()
{
	this->window = nullptr;
	this->tileSize = 0.f;
	this->exitGame = false;
	this->keyTimeMax = 0.f;
	this->keyTime = 0.f;
	this->nrOfActiveTiles = 0;
	this->tilesSelected = 0;
	this->restarting = false;
	this->displayTimer = 0.f;
	this->correct = 0;
	this->incorrect = 0;
	this->difficultyLevel = 0;
	this->timerDuration = 0.f;
}

GameBoard::GameBoard(sf::RenderWindow* window, float tile_size, int board_width, int board_height, int difficulty)
	: window(window), difficultyLevel(difficulty)
{
	this->tileSize = tile_size;
	this->exitGame = false;
	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;
	this->tilesSelected = 0;
	this->restarting = true;
	this->displayTimer = 0.f;
	this->correct = 0;
	this->incorrect = 0;


	switch (difficultyLevel) {
	case 1:
		this->nrOfActiveTiles = 4;
		this->timerDuration = 10.f;
		break;
	case 2:
		this->nrOfActiveTiles = 6;
		this->timerDuration = 8.f;
		break;
	case 3:
		this->nrOfActiveTiles = 7;
		this->timerDuration = 6.f;
		break;
	default:
		this->nrOfActiveTiles = 6;
		this->timerDuration = 8.f;
		break;
	}

	this->createBoard(board_width, board_height);
	this->randomizeBoard();

	if (!this->font.loadFromFile("D:\\PROJECT\\MemoryGame\\font\\HomeVideo-BLG6G.ttf")) {
		std::cerr << "Failed to load font!" << std::endl;
	}

	this->timerText.setFont(this->font);
	this->timerText.setCharacterSize(30);
	this->timerText.setFillColor(sf::Color::White);
	this->timerText.setPosition(20, 20);

	this->gameClock.restart();

}


GameBoard::~GameBoard()
{
	for (size_t j = 0; j < this->tilesVec.size(); j++)
	{
		delete this->tilesVec[j];
	}

}

void GameBoard::restart()
{
	this->tilesSelected = 0;
	this->restarting = true;
	this->displayTimer = 0.f;
	this->selectionVec.clear();
	this->randomizeBoard();

	this->gameClock.restart();
}

void GameBoard::update(sf::RenderWindow& window)
{
	this->mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	this->updateKeyTime();
	this->updateBoard();
}

void GameBoard::render(sf::RenderTarget& target)
{
	for (size_t i = 0; i < this->tilesVec.size(); i++)
	{
		this->tilesVec[i]->render(target);
	}
	target.draw(this->timerText);
}
