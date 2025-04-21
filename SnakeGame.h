#pragma once
#include "Console.h"
#include <iostream>
#include <vector>
#include <conio.h>

class SnakeGame
{
private:
    Console* console{};
    WindowConsole* gameWindow{};

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
    std::vector<Point> snake{};
    Direction currentDirection{};
    Direction nextDirection{};
    Point food{};
    int score{};
    bool gameOver{};

public:
    SnakeGame(Console* cons, WindowConsole* gameWin) :
        console{ cons }, gameWindow{ gameWin }, gameOver{ false }, score{ 0 }
    {
        srand(time(NULL));
        int centerX = gameWindow->Column() + gameWindow->Width() / 2;
        int centerY = gameWindow->Row() + gameWindow->Height() / 2;
        snake.push_back(Point{ centerX, centerY });
        snake.push_back(Point{ centerX - 1, centerY });
        snake.push_back(Point{ centerX - 2, centerY });

        currentDirection = Direction::Right;
        nextDirection = Direction::Right;
    }

    void DrawSnake()
    {
        for (const Point& p : snake)
            gameWindow->WriteGoto(p.y, p.x, 'o');

        gameWindow->WriteGoto(snake.front().y, snake.front().x, '@');
    }

    void DrawFood()
    {
        gameWindow->WriteGoto(food.y, food.x, '$');
    }

    void Input()
    {
        switch (_getch())
        {
        case 72: case 'w': case 'W':
            if (currentDirection != Direction::Down)
                nextDirection = Direction::Up;
            break;
        case 80: case 's': case 'S':
            if (currentDirection != Direction::Up)
                nextDirection = Direction::Down;
            break;
        case 75: case 'a': case 'A':
            if (currentDirection != Direction::Right)
                nextDirection = Direction::Left;
            break;
        case 77: case 'd': case 'D':
            if (currentDirection != Direction::Left)
                nextDirection = Direction::Right;
            break;
        }
    }
};