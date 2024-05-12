// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : CFish.h
// Description : Header for CFish class. Includes an enum for behaviour type and values for behaviour such as forces and speed. 
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>
#include "CPlayer.h"
#include <iostream>

// enums for all behaviours
enum BehaviourType {
	StillType,
	FlockType,
	SeekType,
	FleeType,
	ArriveType,
	EvadeType,
	PursuitType,
	FollowLeaderType,
	WanderType,
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
	float m_fAcceleration = 10.0f;
	float m_fFishSpeedScalar = 0.5f;
	float m_fSeparationSpeed = 4.0f;
	float m_fMaxSpeed = 8.0f;
	float m_fSeparationForce = 4.0f;
	float m_fSteerForce = 0.1f;
	float m_fMaxForce = 8.0f;
	float m_fMaxDistance = 100.0f;
	float m_fSlowingRadius = 1000.0f;
	float m_fCohereSpeed = 6.0f;
	float m_fCohereForce = 2.5f;
	float m_fAlignSpeed = 6.0f;
	float m_fAlignForce = 2.0f;
	float m_fWanderDistance = 10.0f;
	float m_fWanderRadius = 5.0f;
	float m_fWanderAngle = 0.0f;

	// desired cohesion
	sf::Vector2f m_dCohesion;
	// desired Alignment
	sf::Vector2f m_dAlignment;

	// bools
	bool m_bSeparation = false;
	bool m_bCohesion = false;
	bool m_bAlignment = false;
	bool m_bBorderWrap = true;

	// normalize a vector
	sf::Vector2f Normalize(sf::Vector2f _vec);
	// find the absolute value of a vector
	float Magnitude(sf::Vector2f _vec);
	// find the distance between two coordinates
	float Distance(const sf::Vector2f& v1, const sf::Vector2f& v2);
	// normalise a vector if it's bigger than a value
	sf::Vector2f Truncate(sf::Vector2f _vec, float _max);

	// avoid fish in radius
	void Seperate(const std::vector<CFish*> m_Members, float deltaTime);
	// stay close to fish in radius
	void Cohere(const std::vector<CFish*> _Members, float _dt);
	// align with fish in radius
	void Align(const std::vector<CFish*> _Members, float _dt);

	// wrap around the screen
	void BorderWrap();

	// Movement behaviours
	// Steer towards the player
	void Seek(sf::Vector2f _PlayerPos, float _dt);
	// steer away from the player
	void Flee(sf::Vector2f _PlayerPos, float _dt);
	// go to a point and decelerate 
	void Arrive(sf::Vector2f _PlayerPos);
	// predict player position and avoid it
	void Evade(CPlayer _Player, float _dt);
	// predict player position and move towards it
	void Pursuit(CPlayer _Player, float _dt);
	// natural wander movement
	void Wander(sf::Vector2f _PlayerPos, float _dt);

	// special movement
	// 
	void FollowLeader(CPlayer _Player, float _dt);
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

