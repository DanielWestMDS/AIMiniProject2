#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>
#include "CPlayer.h"
#include <iostream>

// enums for all behaviours
enum BehaviourType {
	StillType,
	WanderType,
	SeekType,
	FleeType,
	ArriveType,
	EvadeType,
	FlockType,
	FollowLeaderType,
};

class CFish
{
protected:
	// visual elements
	sf::Sprite m_FishSprite;
	sf::Texture m_FishTexture;

	BehaviourType m_CurrentBehaviour;

	sf::Vector2f m_FishPosition;
	sf::Vector2f m_FishVelocity = { 0, 0 };
	//sf::Vector2f m_MaxVelocity = { 20.0f, 20.0f };
	sf::Vector2f m_cVelocity = { 0, 0 };
	sf::Vector2f steer = { 0, 0 };
	float m_fAcceleration = 2;
	float m_fFishSpeedScalar = 1.0f;
	float m_fSeparationSpeed;
	float m_fMaxSpeed;
	float m_fSeparationForce;
	float m_fSteerForce;
	float m_fMaxForce;
	float m_fMaxDistance = 1000;
	float m_fSlowingRadius = 1000;

	// bools
	bool m_bSeparation = false;
	bool m_bCohesion = false;
	bool m_bAlignment;
	bool m_bBorderWrap;

	sf::Vector2f Normalize(sf::Vector2f _vec);
	float Magnitude(sf::Vector2f _vec);
	float Distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	sf::Vector2f Truncate(sf::Vector2f _vec, float _max);

	void Seperate(const std::vector<CFish*> m_Members, float deltaTime);
	sf::Vector2f Cohere(const std::vector<CFish*> _Members);
	void Align();
	void BorderWrap();

	// Movement behaviours
	void Seek(CPlayer _Player, float _dt);
	void Flee(CPlayer _Player, float _dt);
	void Arrive(CPlayer _Player);
	void Evade();
	void Wander();
	//sf::Vector2f Seek(sf::Vector2f target, float maxSpeed, float maxForce);

public:

	//sf::Vector2f transform;

	// not sure why two constrcutors but it fixes an issue
	CFish();
	CFish(sf::String _ImagePath);
	~CFish();

	void Input();



	void Update(float _dt, const std::vector<CFish*> _Members, CPlayer _Player);

	sf::Sprite Draw();
};

