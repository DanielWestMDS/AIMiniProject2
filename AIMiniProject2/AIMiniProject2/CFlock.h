#pragma once
#include <vector>
#include "CFish.h"

class CFlock
{
private:
	// vector containing all members of the flock
	std::vector<CFish> m_Members;

public:

	void Update();
};

