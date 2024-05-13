// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CPlayer.cpp
// Description : Functionality for player. Includes input, render updates, and border wrapping. 
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#include "CPlayer.h"

void CPlayer::BorderWrap()
{
	if (m_CharacterPosition.x > 800)
	{
		m_CharacterSprite.setPosition(0, m_CharacterPosition.y);
	}
	if (m_CharacterPosition.x < 0)
	{
		m_CharacterSprite.setPosition(799, m_CharacterPosition.y);
	}
	if (m_CharacterPosition.y > 800)
	{
		m_CharacterSprite.setPosition(m_CharacterPosition.x, 0);
	}
	if (m_CharacterPosition.y < 0)
	{
		m_CharacterSprite.setPosition(m_CharacterPosition.x, 799);
	}
}

CPlayer::CPlayer(sf::String _ImagePath)
{
	// get textture
	m_CharacterTexture.loadFromFile(_ImagePath);
	// set sprite texture
	m_CharacterSprite.setTexture(m_CharacterTexture);
	// set sprite origin
	m_CharacterSprite.setOrigin(m_CharacterTexture.getSize().x / 2, m_CharacterTexture.getSize().y / 2);
	// set character starting position
	m_CharacterPosition = sf::Vector2f(400, 300);
	// link sprite position to character position
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
	m_CharacterPosition = m_CharacterSprite.getPosition();

	// wrap around
	BorderWrap();
}

sf::Sprite CPlayer::Draw()
{
	return m_CharacterSprite;
}
