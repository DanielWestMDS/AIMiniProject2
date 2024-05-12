// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : main.cpp
// Description : Contains main window loop for SFML as well as delta time. Creates a player and a flock then runs their update functions every frame.
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#include "CFLock.h"

// delta time stuff
sf::Clock g_Clock;
float g_DeltaTime = 0.0f;
bool g_bGameRunning = true;

int main()
{
	// create window
	sf::RenderWindow window(sf::VideoMode(800, 800), "Test");
	sf::Event event;

	// create player
	CPlayer* Player = new CPlayer("Sprites/PlayerBlock.bmp");
	Player->SetWindowRef(&window);

	// test fish
	//std::vector<CFish> FishVec;
	//CFish* Fish = new CFish("Sprites/FishBlock.bmp");

	// Flock
	CFlock* Flock = new CFlock();

	// main window loop
	while (window.isOpen())
	{
		// delta time
		g_DeltaTime = g_Clock.getElapsedTime().asSeconds();
		g_Clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		// make background blue like sky
		window.clear(sf::Color::Cyan);


        // input
        if (g_bGameRunning)
        {
			// get player input
            Player->Input(g_DeltaTime);
			Player->Update(g_DeltaTime);

			// update flock
			Flock->Update(g_DeltaTime, *Player);

        }

		// drawing
		window.draw(Player->Draw());

		Flock->Draw(&window);

		window.display();

	}
	return 0;
}