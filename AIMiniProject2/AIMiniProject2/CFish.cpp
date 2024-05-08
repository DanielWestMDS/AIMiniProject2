#include "CFish.h"

sf::Vector2f CFish::Normalize(sf::Vector2f _vec)
{
    float length = std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y);

    // To avoid division by zero, we only normalize if the length is not zero
    if (length > 0) {
        _vec.x /= length;
        _vec.y /= length;
    }

    return _vec;
}

float CFish::Magnitude(sf::Vector2f _vec)
{
    return std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y);
}

float CFish::Distance(const sf::Vector2f& v1, const sf::Vector2f& v2)
{
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    return std::sqrt(dx * dx + dy * dy);
}

sf::Vector2f CFish::Truncate(sf::Vector2f _vec, float _max)
{
    if (Magnitude(_vec) > _max)
    {
        _vec = Normalize(_vec) * _max;
        return _vec;
    }

    return _vec;

}

void CFish::Seperate(const std::vector<CFish*> _Members, float deltaTime)
{
    sf::Vector2f sum = sf::Vector2f(0.0f, 0.0f);

    for (const CFish* other : _Members)
    {
        if (other == this)
            continue;

        //float distance = std::sqrt(
        //    std::pow(other->m_FishPosition.x - m_FishPosition.x, 2) +
        //    std::pow(other->m_FishPosition.y - m_FishPosition.y, 2));

        float fDistance = Distance(other->m_FishPosition, m_FishPosition);

        if (fDistance > m_fMaxDistance)
            continue;

        sf::Vector2f offset = m_FishPosition - other->m_FishPosition;
        float magnitude = std::sqrt(offset.x * offset.x + offset.y * offset.y);
        offset /= magnitude;

        sum += offset;
    }

    if (!_Members.empty())
    {
        sum /= static_cast<float>(_Members.size() - 1);
    }

    sum = sum / std::sqrt(sum.x * sum.x + sum.y * sum.y);
    sum *= m_fSeparationSpeed;

    sf::Vector2f steer = sf::Vector2f(sum.x, sum.y) - m_FishVelocity;
    m_FishVelocity += steer * m_fSeparationForce * m_fSteerForce * deltaTime;
}

sf::Vector2f CFish::Cohere(const std::vector<CFish*> _Members)
{
    sf::Vector2f sum = sf::Vector2f(0.0f, 0.0f);
    int iCount = 0;

    // For every character in the system, check if it's a neighbor
    for (const CFish* other : _Members) 
    {
        // skip if comparing to self
        if (other == this)
            continue;

        float fDistance = Distance(m_FishPosition, other->m_FishPosition);

        // If the other character is in range
        if ((fDistance > 0) && (fDistance < m_fMaxDistance))
        {
            sum += other->m_FishPosition;  // Add the position
            iCount++;
        }
    }

    // If there are neighbors, calculate the average position
    if (iCount > 0) 
    {
        sum /= (float)iCount;
        return sf::Vector2f(0, 0);//Seek(sum, m_fMaxSpeed, m_fMaxForce);  // Steer towards the position
    }
    else 
    {
        return sf::Vector2f(0, 0);  // Return a null steering force
    }
}

//sf::Vector2f CFish::Seek(sf::Vector2f target, float maxSpeed, float maxForce)
//{
//    sf::Vector2f desired = target - m_FishPosition;  // A vector pointing from the character to the target
//
//    // Normalize desired and scale with maxSpeed
//    Normalize(desired);
//    desired *= maxSpeed;
//
//    // Steering = Desired minus velocity
//    sf::Vector2f steer = desired - m_FishVelocity;
//
//    if (Magnitude(steer) > maxForce) 
//    { 
//        Normalize(steer);
//        steer *= maxForce;
//    }
//
//    return steer;
//}

void CFish::Align()
{
}

void CFish::BorderWrap()
{
    if (m_FishPosition.x > 800)
    {
        m_FishPosition.x = 0;
    }
    if (m_FishPosition.x < 0)
    {
        m_FishPosition.x = 799;
    }
    if (m_FishPosition.y > 800)
    {
        m_FishPosition.y = 0;
    }
    if (m_FishPosition.y < 0)
    {
        m_FishPosition.y = 799;
    }
}

CFish::CFish()
{
}

CFish::CFish(sf::String _ImagePath)
{
    // add sprite
	m_FishTexture.loadFromFile(_ImagePath);
	m_FishSprite.setTexture(m_FishTexture);
	m_FishSprite.setOrigin(m_FishTexture.getSize().x / 2, m_FishTexture.getSize().y / 2);
	m_FishPosition = sf::Vector2f(rand() % 1000, rand() % 1000); // maybe make this random
	m_FishSprite.setPosition(m_FishPosition);

    m_fMaxSpeed = 10.0f;
    m_fMaxForce = 5.0f;
}

CFish::~CFish()
{
}

void CFish::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
    {
        m_CurrentBehaviour = StillType;
        std::cout << "Still" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        m_CurrentBehaviour = FlockType;
        std::cout << "Flock" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        m_CurrentBehaviour = SeekType;
        std::cout << "Seek" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        m_CurrentBehaviour = FleeType;
        std::cout << "Flee" << std::endl;

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        m_CurrentBehaviour = ArriveType;
        std::cout << "Arrive" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        m_CurrentBehaviour = EvadeType;
        std::cout << "Evade" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
    {
        m_CurrentBehaviour = PursuitType;
        std::cout << "Pursuit" << std::endl;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
    {
        m_CurrentBehaviour = FollowLeaderType;
        std::cout << "FollowLeader" << std::endl;
    }
}

void CFish::Seek(sf::Vector2f _PlayerPos, float _dt)
{
    sf::Vector2f dVelocity = Normalize(_PlayerPos - m_FishPosition) * m_fFishSpeedScalar;
    steer = dVelocity - m_cVelocity;
    m_cVelocity += steer * m_fAcceleration * _dt;
    //m_FishVelocity = _Player.m_CharacterPosition - m_FishPosition;
    m_FishPosition += m_cVelocity * _dt;
}

void CFish::Flee(sf::Vector2f _PlayerPos, float _dt)
{
    sf::Vector2f dVelocity = Normalize(_PlayerPos - m_FishPosition) * m_fFishSpeedScalar;
    dVelocity = dVelocity * -1.0f;
    steer = dVelocity - m_cVelocity;
    m_cVelocity += steer * m_fAcceleration * _dt;
    //m_FishVelocity = _Player.m_CharacterPosition - m_FishPosition;
    m_FishPosition += m_cVelocity * _dt;
}

void CFish::Arrive(sf::Vector2f _PlayerPos)
{
    sf::Vector2f dVelocity = _PlayerPos - m_FishPosition;
    float fDistance = Magnitude(dVelocity);

    if (fDistance < m_fSlowingRadius)
    {
        dVelocity = Normalize(dVelocity) * m_fMaxSpeed * (fDistance / m_fSlowingRadius);
    }
    else
    {
        dVelocity = Normalize(dVelocity) * m_fMaxSpeed;
    }
    steer = dVelocity - m_FishVelocity;
    m_FishVelocity = Truncate(m_FishVelocity + steer, m_fMaxSpeed);
}

void CFish::Evade(CPlayer _Player, float _dt)
{
    // prevent teleporting from infinite time to target
    if (Magnitude(m_FishVelocity) == 0.0f)
    {
        Flee(_Player.m_CharacterPosition, _dt);
    }
    else
    {
        float fTimeToTar = Distance(_Player.m_CharacterPosition, m_FishPosition) / Magnitude(m_FishVelocity);
        sf::Vector2f predictedPos = _Player.m_CharacterPosition + (_Player.m_CharacterVelocity * fTimeToTar);
        Flee(predictedPos, _dt);
    }
}

void CFish::Pursuit(CPlayer _Player, float _dt)
{
    // prevent teleporting from infinite time to target
    if (Magnitude(m_FishVelocity) == 0.0f)
    {
        Seek(_Player.m_CharacterPosition, _dt);
    }
    else
    {
        float fTimeToTar = Distance(_Player.m_CharacterPosition, m_FishPosition) / Magnitude(m_FishVelocity);
        sf::Vector2f predictedPos = _Player.m_CharacterPosition + (_Player.m_CharacterVelocity * fTimeToTar);
        Seek(predictedPos, _dt);
    }
}

void CFish::Update(float _dt, const std::vector<CFish*> _Members, CPlayer _Player)
{
    Input();

    if (m_CurrentBehaviour != StillType)
    {
        m_fFishSpeedScalar = 30.0f;
    }

    if (m_bSeparation)
    {
        Seperate(_Members, _dt);
    }
    if (m_bCohesion)
    {
        Cohere(_Members);
    }
    if (m_bAlignment)
    {
        Align();
    }
    if (m_bBorderWrap)
    {
        BorderWrap();
    }

    // movement
    // m_FishSprite.move(m_FishVelocity.x * m_fFishSpeedScalar * _dt, m_FishVelocity.y * m_fFishSpeedScalar * _dt);
    //m_FishPosition += m_FishVelocity * m_fFishSpeedScalar * _dt;
    //m_FishSprite.setPosition(m_FishPosition);
    //transform.up = velocity;  

    m_FishPosition += m_FishVelocity * m_fFishSpeedScalar * _dt;
    m_FishSprite.setPosition(m_FishPosition);

    switch (m_CurrentBehaviour)
    {
    case StillType:
        m_fFishSpeedScalar = 0.0f;
        break;
    case FlockType:
        break;
    case SeekType:
        Seek(_Player.m_CharacterPosition, _dt);
        break;
    case FleeType:
        Flee(_Player.m_CharacterPosition, _dt);
        break;
    case ArriveType:
        Arrive(_Player.m_CharacterPosition);
        break;
    case EvadeType:
        Evade(_Player, _dt);
        break;
    case PursuitType:
        Pursuit(_Player, _dt);
        break;
    case FollowLeaderType:
        break;
    default:
        break;
    }

    // Update velocity
    //m_FishVelocity += m_fAcceleration * _dt;


    //// Limit speed
    //if (Magnitude(m_FishVelocity) > m_fMaxSpeed) 
    //{
    //    m_FishVelocity = Normalize(m_FishVelocity) * m_fMaxSpeed;
    //}

    //// Update position
    //m_FishPosition += m_FishVelocity * _dt;

    //// Reset acceleration to 0 each cycle
    //m_fAcceleration = sf::Vector2f(0, 0);

    //m_FishSprite.setPosition(m_FishPosition);

}

sf::Sprite CFish::Draw()
{
	return m_FishSprite;
}
