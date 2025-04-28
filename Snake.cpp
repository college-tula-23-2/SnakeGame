#include <iostream>
#include "Console.h"
#include "SnakeGame.h"

int main()
{
    Console console;
    WindowConsole wc{ &console, 0, 0, 20, 40 };
    SnakeGame sg{ &console, &wc };
    sg.Run();
}