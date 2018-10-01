#pragma once
#include "Window.h"

int main()
{
	Window app = Window();

	if (!app.init())
	{
		std::cout << "fatal error :: Game is not init!!!" << std::endl;
		return(0);
	}
	
	app.createGame();

	while (app.exit())
	{
		app.mainLoop();
	}

	std::cout << "The End!!!" << std::endl;
	return(0);
}