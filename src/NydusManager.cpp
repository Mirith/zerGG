#include "NydusManager.h"
#include "Util.h"
#include "Common.h"
#include "CCBot.h"

bool NydusBuilt = false;

void NydusManager::OnUnitCreated(const sc2::Unit* unit, CCBot & bot)
{
	// set rally point for all attacking units
	// roach warren, hatch/lair

	sc2::Point2D temp;

	if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK)
	{
		temp = sc2::Point2D(unit->pos.x, unit->pos.y);
	}

	if (!NydusBuilt)
	{
		sc2::Point2D & temp = bot.Bases().getNextExpansion(Players::Self);
		MakeNydusNetwork(sc2::Point2D(temp.y, temp.x), bot);
	}

	//for (auto & unitTag : bot.UnitInfo().getUnits(Players::Self))
	//{
	//	// if it is a building that makes offensive units, rally them to nydus
	//	if (unitTag->unit_type == sc2::UNIT_TYPEID::ZERG_HATCHERY
	//		|| unitTag->unit_type == sc2::UNIT_TYPEID::ZERG_ROACHWARREN
	//		|| unitTag->unit_type == sc2::UNIT_TYPEID::ZERG_LAIR)
	//	{
	//		bot.Actions()->UnitCommand(unitTag, sc2::ABILITY_ID::RALLY_UNITS, temp);
	//	}
	//}
}


// makes a nydus network point in enemy base
// @nydus			the existing network in your base
// @enemyBaseCoord	where in the enemy base to build the new network
// @bot				bot thing, necessary thing
// does this happen bc botconfig file or because of programming? check timing in game
void NydusManager::MakeNydusNetwork(sc2::Point2D & enemyBaseCoord, CCBot & bot)
{
	for (auto & unit : bot.UnitInfo().getUnits(Players::Self))
	{
		// check if there is a nydus worm already
		if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_NYDUSCANAL)
		{
			// unloads all in nydus
			bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::UNLOADALL_NYDUSWORM);
			NydusBuilt = true;
		}

		if (NydusBuilt)
		{
			return;
		}

		// if no worm already, builds one
		if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK)
		{
			bot.Actions()->UnitCommand(unit, sc2::ABILITY_ID::BUILD_NYDUSWORM, enemyBaseCoord);
		}
	}

}
