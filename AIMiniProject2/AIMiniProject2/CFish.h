#pragma once
#include "SFML/Graphics.hpp"
#include <random>

class CFish
{
protected:
	// visual elements
	sf::Sprite m_FishSprite;
	sf::Texture m_FishTexture;

	sf::Vector2f m_FishPosition;
	sf::Vector2f m_FishVelocity = { 0, 0 };
	float m_fFishSpeedScalar = 30.0f;

public:
	CFish(sf::String _ImagePath);
	~CFish();

	void Update(float _dt);

	sf::Sprite Draw();
};

