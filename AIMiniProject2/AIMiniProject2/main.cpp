#include "CPlayer.h"
#include "CFish.h"

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
	std::vector<CFish> FishVec;
	for (int i = 0; i < 20; i++)
	{
		CPlayer* Fish = new CPlayer("Sprites/FishBlock.bmp");
		FishVec.emplace_back(Fish);
	}

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

        // prevent game running when window moved
        if (true/*g_DeltaTime < 0.1f*/)
        {
            // input
            if (g_bGameRunning)
            {
                Player->Input(g_DeltaTime);
				Player->Update(g_DeltaTime);
            }
        }

		// drawing
		window.draw(Player->Draw());
		window.display();

	}
	return 0;
}