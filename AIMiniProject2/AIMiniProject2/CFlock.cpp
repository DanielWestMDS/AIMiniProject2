#include "CFlock.h"

CFlock::CFlock()
{
	for (int i = 0; i < 20; i++)
	{
		CFish* Fish = new CFish("Sprites/FishBlock.bmp");
		//	= new CFish("Sprites/FishBlock.bmp");
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
		// flocking code here
		Fish->Update(_dt, m_Members, _Player);
	}
}

void CFlock::Draw(sf::RenderWindow* _Window)
{
	for (int i = 0; i < m_Members.size(); i++)
	{
		_Window->draw(m_Members[i]->Draw());
	}
}
