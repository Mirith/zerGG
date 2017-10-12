#pragma once
#include "Common.h"
#include "sc2api/sc2_api.h"

class CCBot;

namespace OverlordManager
{
	//void OverlordSpread(const UnitTag & moomoo, const sc2::Point2D & place, CCBot & bot);
	void OverlordSpread(const UnitTag & moomoo, const sc2::Point2D & place, CCBot & bot);
	void GenerateCreep(const UnitTag & moomoo, CCBot & bot);
	void Scout(const UnitTag & scout, const sc2::Point2D & place, CCBot & bot);
	void Execute(CCBot & bot);
}

