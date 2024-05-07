#include "CFish.h"

CFish::CFish(sf::String _ImagePath)
{
	m_FishTexture.loadFromFile(_ImagePath);
	m_FishSprite.setTexture(m_FishTexture);
	m_FishSprite.setOrigin(m_FishTexture.getSize().x / 2, m_FishTexture.getSize().y / 2);
	m_FishPosition = sf::Vector2f(rand() % 1000, rand() % 1000); // maybe make this random
	m_FishSprite.setPosition(m_FishPosition);
}

CFish::~CFish()
{
}

void CFish::Update(float _dt)
{
}

sf::Sprite CFish::Draw()
{
	return m_FishSprite;
}
