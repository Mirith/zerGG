#pragma once
#include "Common.h"
#include "sc2api/sc2_api.h"
#include "BaseLocation.h"

class CCBot;

namespace OverlordManager
{
	void OnUnitCreated(const sc2::Unit* unit, CCBot & bot);
	void OverlordMove(const sc2::Unit & moomoo, const sc2::Point2D & destination, CCBot & bot);
	void OverlordMove(const sc2::Unit & moomoo, const std::vector<sc2::Point2D> & destinations, CCBot & bot);
	void GenerateCreep(const UnitTag & moomoo, CCBot & bot);
	void Execute(CCBot & bot);
}

