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
        DrawFood();
    }

    void ChangeDirectory()
    {
        currentDirection = nextDirection;

        Point newHead = snake.front();
        switch (currentDirection)
        {
        case Direction::Up: newHead.y--; break;
        case Direction::Down: newHead.y++; break;
        case Direction::Right: newHead.x++; break;
        case Direction::Left: newHead.x--; break;
        }
        snake.insert(snake.begin(), newHead);
        snake.pop_back();
    }

    void DrawSnake()
    {
        system("cls");
        for (const Point& p : snake)
            gameWindow->WriteGoto(p.y, p.x, 'o');

        gameWindow->WriteGoto(snake.front().y, snake.front().x, '@');
    }

    bool CheckCollision()
    {
        Point head = snake.front();
        if (head.x <= gameWindow->Column() || head.x >= gameWindow->Column() +
            gameWindow->Width() - 1  || head.y <= gameWindow->Row() || 
            head.y >= gameWindow->Row() + gameWindow->Height() - 1)
        {
            return true;
        }

        for (int i{ 1 }; i < snake.size(); ++i)
            if (head == snake[i])
                return true;
        return false;
    }

    void DrawFood()
    {
        gameWindow->WriteGoto(food.y, food.x, '$');
    }

    void Input()
    {
        if (_kbhit())
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
    }

    void Run()
    {
        while (!gameOver)
        {
            Input();
            ChangeDirectory();
            DrawSnake();
            if (CheckCollision())
            {
                gameOver = false;
                return;
            }
            DrawFood();
            Sleep(200);
        }
    }
};