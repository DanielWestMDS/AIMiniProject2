// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CFlock.h
// Description : Header for CFlock class. Handles the CFish through a vector of all flock members. 
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#pragma once
#include <vector>
#include "CFish.h"

class CFlock
{
private:
	// vector containing all members of the flock
	std::vector<CFish*> m_Members;

public:
	CFlock();
	~CFlock();

	// run behaviour code for all fish in relation to the player
	void Update(float _dt, CPlayer _Player);
	// render all fish sprites
	void Draw(sf::RenderWindow* _Window);

	void AddFish();
};

