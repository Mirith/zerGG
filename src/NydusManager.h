#pragma once
#include "Common.h"
#include "BaseLocation.h"

namespace NydusManager
{
	void OnUnitCreated(const sc2::Unit * unit, CCBot & bot);
	void MakeNydusNetwork(sc2::Point2D & enemyBaseCoord, CCBot & bot);
}