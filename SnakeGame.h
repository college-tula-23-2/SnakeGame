#pragma once
#include "Console.h"
#include <vector>

class SnakeGame
{
private:
	Console* console;
	WindowConsole* gameWindow;

	struct Point
	{
		int x{};
		int y{};
		Point(int x, int y) : x{ x }, y{ y } {}
		Point() = default;
		bool operator==(const Point& other) const
		{
			return x == other.x && y == other.y;
		}
	};

	enum Direction { Up, Down, Left, Right };
	std::vector<Point> snake;
	Direction currentDirection;
	Point food;
	int score;
	int gameOver;

public:
	SnakeGame(Console* cons, WindowConsole* gameWin) :
		console{ cons }, gameWindow{ gameWin }
	{

	}
};