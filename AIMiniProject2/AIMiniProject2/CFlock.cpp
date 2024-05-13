// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CFlock.cpp
// Description : Functionality for CFlock class. Handles the CFish class as a group. 
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#include "CFlock.h"

CFlock::CFlock()
{
	// loop for 20 fish initially.
	for (int i = 0; i < 20; i++)
	{
		// create a fish object reference
		CFish* Fish = new CFish("Sprites/FishBlock.bmp");
		// add fish reference to a vector containing all fish
		m_Members.push_back(Fish);
	}
}

CFlock::~CFlock()
{
}

void CFlock::Update(float _dt, CPlayer _Player)
{
	for (CFish* Fish : m_Members)
	{
		// update individual member of flock
		Fish->Update(_dt, m_Members, _Player);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// add a fish to the flock if mouse button pressed
		AddFish();
	}
}

void CFlock::Draw(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Members.size(); i++)
	{
		_Window->draw(m_Members[i]->Draw());
	}
}

void CFlock::AddFish()
{
	// create fish object reference
	CFish* Fish = new CFish("Sprites/FishBlock.bmp");
	// add fish to flock vector
	m_Members.push_back(Fish);

	// cout flock count
	std::cout << "Flock size: " << m_Members.size() << std::endl;
}
