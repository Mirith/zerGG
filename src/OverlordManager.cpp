// Manages behavior of Overlords aka moomoos
#include "OverlordManager.h"
#include "Util.h"
#include "CCBot.h"
#include "Common.h"
#include "sc2api/sc2_api.h"
#include "sc2api/sc2_action.h"


// Moves Overlord to point specified
// @moomoo		Overlord
// @destination	Coordinates of destination
// @bot			Bot thing, necessary thing
void OverlordManager::OverlordMove(const sc2::Unit & moomoo, const sc2::Point2D & destination, CCBot & bot)
{
	// move overlord to a given position
	bot.Actions()->UnitCommand(bot.GetUnit(moomoo.tag), sc2::ABILITY_ID::MOVE, destination, false);
}

// Moves Overlord to points specified
// @moomoo			Overlord
// @destinations	Coordinates of destinations to travel to
// @bot				Bot thing, necessary thing
void OverlordManager::OverlordMove(const sc2::Unit & moomoo, const std::vector<sc2::Point2D> & destinations, CCBot & bot)
{
	// queues move commands from destinations for moomoo
	for (auto point : destinations)
	{
		bot.Actions()->UnitCommand(bot.GetUnit(moomoo.tag), sc2::ABILITY_ID::MOVE, point, true);
	}
}

// Tells Overlord to generate creep
// @moomoo	Overlord
// @bot		Bot thing
void OverlordManager::GenerateCreep(const UnitTag & moomoo, CCBot & bot)
{
	bot.Actions()->UnitCommand(bot.GetUnit(moomoo), sc2::ABILITY_ID::BEHAVIOR_GENERATECREEPON);
}

// takes overlord functions and executes them, called in CCBot.cpp
// @bot		bot thing, necessary thing
void OverlordManager::Execute(CCBot & bot)
{
	// loops through player's units
	for (auto & unit : bot.UnitInfo().getUnits(Players::Self))
	{
		// checks if they are overlords
		if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD)
		{
			OverlordManager::GenerateCreep(unit->tag, bot);
			
			// finds enemy base location
			const BaseLocation * enemyBaseLocation = bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);

			// returns if enemy base is null, aka unscouted
			if (enemyBaseLocation == nullptr)
			{
				return;
			}
			
			// points for testing
		    const sc2::Point2D & point = sc2::Point2D(50, 50);
			const sc2::Point2D & point2 = sc2::Point2D(enemyBaseLocation->getPosition().x, enemyBaseLocation->getPosition().y);

			const std::vector<sc2::Point2D> places = { point, point2 };
			
			OverlordMove(*unit, places, bot);
		}
	}
}