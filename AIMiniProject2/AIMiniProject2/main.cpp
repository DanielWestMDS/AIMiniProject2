//#include "CPlayer.h"
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
            Player->Input(g_DeltaTime);
			Player->Update(g_DeltaTime);
        }

		// update flock
		Flock->Update(g_DeltaTime, *Player);

		// drawing
		window.draw(Player->Draw());

		//for (CFish Fish : FishVec)
		//{
		//	window.draw(Fish.Draw());
		//}

		Flock->Draw(&window);

		window.display();

	}
	return 0;
}