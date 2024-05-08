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

	void Update(float _dt, CPlayer _Player);
	void Draw(sf::RenderWindow* _Window);
};

