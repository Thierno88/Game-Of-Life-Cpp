#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

int main() {
	const int height = 600;
	const int width = 800;
	sf::RenderWindow window(sf::VideoMode(width, height), "Conway's Game of Life");

	const int cellSize = 10;
	const int spacing = 2;

	int numCols = width / (cellSize + spacing);
	int numRows = height / (cellSize + spacing);

	std::vector<std::vector<sf::RectangleShape>> grid(numRows, std::vector<sf::RectangleShape>(numCols));

	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			grid[i][j] = sf::RectangleShape(sf::Vector2f(cellSize, cellSize));
			float posX = j * (cellSize + spacing);
			float posY = i * (cellSize + spacing);
			grid[i][j].setPosition(posX, posY);
			grid[i][j].setFillColor(sf::Color(128, 128, 128));
		}
	}

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

		grid[2][10].setFillColor(sf::Color::White);
		
		bool painting = true;
		if (painting) {
			static int currentRow = 2;
			static int currentCol = 10;


			if (currentRow < numRows) {
				grid[currentRow][currentCol].setFillColor(sf::Color::White);
				currentCol++;
				if (currentCol >= numCols) {
					currentCol = 0;
					currentRow++;
				}
				sf::sleep(sf::microseconds(100)); // Pausa de 1 segundo entre cada célula pintada
			}
			else {
				painting = false;
			}
		}

		window.display();
	}

	return 0;
}
