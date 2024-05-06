#include "CPlayer.h"

CPlayer::CPlayer(sf::String _ImagePath)
{
	m_CharacterTexture.loadFromFile(_ImagePath);
	m_CharacterSprite.setTexture(m_CharacterTexture);
	m_CharacterSprite.setOrigin(m_CharacterTexture.getSize().x / 2, m_CharacterTexture.getSize().y / 2);
	m_CharacterPosition = sf::Vector2f(400, 300);
	m_CharacterSprite.setPosition(m_CharacterPosition);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Input(float _dt)
{
	m_CharacterVelocity = sf::Vector2f(0, 0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_CharacterVelocity.y = -m_fPlayerSpeed;
		//std::cout << "up";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_CharacterVelocity.y = m_fPlayerSpeed;
		//std::cout << "Down";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_CharacterVelocity.x = -m_fPlayerSpeed;
		//std::cout << "left";

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_CharacterVelocity.x = m_fPlayerSpeed;
		//std::cout << "right";
	}
}

void CPlayer::Update(float _dt)
{
	// position character based on velocity and speed
	m_CharacterSprite.move(m_CharacterVelocity.x * m_fCharacterSpeedScalar * _dt, m_CharacterVelocity.y * m_fCharacterSpeedScalar * _dt);
}

sf::Sprite CPlayer::Draw()
{
	return m_CharacterSprite;
}