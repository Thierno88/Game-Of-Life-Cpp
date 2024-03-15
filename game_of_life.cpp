]#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

//std::vector<std::vector<sf::RectangleShape>> grid(numRows, std::vector<sf::RectangleShape>(numCols));
std::vector<std::vector<sf::RectangleShape>> createGrid(int numRows, int numCols, int cellSize, int spacing);
void paintClick(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, int numRows, int numCols, int cellSize, int spacing);

int main() {
	const int height = 600;
	const int width = 800;
	sf::RenderWindow window(sf::VideoMode(width, height), "Conway's Game of Life");

	const int cellSize = 10;
	const int spacing = 2;

	int numCols = width / (cellSize + spacing);
	int numRows = height / (cellSize + spacing);

	std::vector<std::vector<sf::RectangleShape>> grid = createGrid(numRows, numCols, cellSize, spacing);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Draw the rectangle
		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numCols; j++) {
				window.draw(grid[i][j]);
			}
		}
		//Get maouse click and paint the right cell
		paintClick(window,grid,numRows,numCols,cellSize,spacing);
		
		window.display();
	}

	return 0;
}

std::vector<std::vector<sf::RectangleShape>> createGrid(int numRows, int numCols, int cellSize, int spacing){

	//Creating Vector 2D
	std::vector<std::vector<sf::RectangleShape>> grid(numRows, std::vector<sf::RectangleShape>(numCols));
	
	//Craeting each cell of the grid
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			grid[i][j] = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
			float posX = j * (cellSize + spacing);
			float posY = i * (cellSize + spacing);
			grid[i][j].setPosition(posX, posY);
			grid[i][j].setFillColor(sf::Color(128, 128, 128));
		}
	}

	return grid;

}

void paintClick(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, int numRows,int numCols,int cellSize,int spacing) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		int row = mousePosition.y / (cellSize + spacing);
		int col = mousePosition.x / (cellSize + spacing);
		if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
			grid[row][col].setFillColor(sf::Color::White);
		}
	}
}
