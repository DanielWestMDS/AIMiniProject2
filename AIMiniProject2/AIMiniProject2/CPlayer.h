#include "SFML/Graphics.hpp"

//#include <iostream>

class CPlayer
{
private:
	void BorderWrap();

public:

	// visual elements
	sf::Sprite m_CharacterSprite;
	sf::Texture m_CharacterTexture;

	//movement elements
	sf::Vector2f m_CharacterPosition;
	sf::Vector2f m_CharacterVelocity = { 0, 0 };
	float m_fCharacterSpeedScalar = 30.0f;

	float m_fPlayerSpeed = 3.0f;

	//window 
	sf::RenderWindow* m_WindowRef;

	CPlayer(sf::String _ImagePath);
	~CPlayer();

	void Input(float _dt);
	void SetWindowRef(sf::RenderWindow* _Window) { m_WindowRef = _Window; }
	void SetPosition(sf::Vector2f _Pos) { m_CharacterSprite.setPosition(_Pos); m_CharacterPosition = _Pos; }

	void Update(float _dt);

	sf::Sprite Draw();
};