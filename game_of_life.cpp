#include <SFML/Graphics.hpp>
#include <iostream>

std::vector<std::vector<sf::RectangleShape>> createGrid(int numRows, int numCols, int cellSize, int spacing);
void paintGrid(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>grid, int numRows, int numCols);
void paintClick(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, int numRows, int numCols, int cellSize, int spacing);
void drawMenu(sf::RenderWindow& menu);
void startGame(sf::RenderWindow& window, sf::RenderWindow& menu);

int main() {

	// Main window configs
	const int height1 = 600;
	const int width1 = 800;
	sf::RenderWindow window(sf::VideoMode(width1, height1), "Conway's Game of Life");

	const int cellSize = 10;
	const int spacing = 2;

	int numCols = width1 / (cellSize + spacing);
	int numRows = height1 / (cellSize + spacing);

	std::vector<std::vector<sf::RectangleShape>> grid = createGrid(numRows, numCols, cellSize, spacing);

	//Menu Window configs
	const int height2 = 100;
	const int width2 = 200;
	sf::RenderWindow menu(sf::VideoMode(width2, height2), "Menu");
	drawMenu(menu);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		paintGrid(window, grid, numRows, numCols);						//Paint Grid - all cells
		paintClick(window, grid, numRows, numCols, cellSize, spacing);	//Get mouse click and paint the right cell
		startGame(window, menu);

		window.display();
	}

	return 0;
}

std::vector<std::vector<sf::RectangleShape>> createGrid(int numRows, int numCols, int cellSize, int spacing) {

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

void paintGrid(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>grid, int numRows, int numCols) {
	// Draw the rectangle
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			window.draw(grid[i][j]);
		}
	}
}

void paintClick(sf::RenderWindow& window, std::vector<std::vector<sf::RectangleShape>>& grid, int numRows, int numCols, int cellSize, int spacing) {
	static bool mouseClicked = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseClicked) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		int row = mousePosition.y / (cellSize + spacing);
		int col = mousePosition.x / (cellSize + spacing);

		if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
			if (grid[row][col].getFillColor() != sf::Color::White) {
				grid[row][col].setFillColor(sf::Color::White);
			}
			else {
				grid[row][col].setFillColor(sf::Color(128, 128, 128));
			}
		}
		mouseClicked = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseClicked = false;
	}
}

void drawMenu(sf::RenderWindow& menu) {
	menu.clear();

	// Criando botão
	sf::RectangleShape button(sf::Vector2f(100, 50));
	button.setPosition(50, 25);
	button.setFillColor(sf::Color::Green);

	// Desenhando o botão 
	menu.draw(button);

	menu.display();
}

void startGame(sf::RenderWindow& window, sf::RenderWindow& menu) {
	static bool mouseClicked = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseClicked) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(menu);
		// Verifica se o clique ocorreu dentro das coordenadas do botão
		if (mousePosition.x >= 50 && mousePosition.x <= 150 &&
			mousePosition.y >= 25 && mousePosition.y <= 75) {
			std::cout << "Botão clicado!\n";
		}
		mouseClicked = true;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		mouseClicked = false;
	}
}
