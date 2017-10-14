// Manages behavior of Overlords aka moomoos
#include "OverlordManager.h"
#include "Util.h"
#include "CCBot.h"
#include "Common.h"
#include "sc2api/sc2_api.h"

// Spreads Overlord out across the map after they spawn, makes them patrol
// @moomoo	Overlord
// @place	Coordinates of destination
// @bot		Bot thing, necessary thing
// maybe pass in vector of points to scout if possible
// std::vector<sc2::Point2D> & blah ?
void OverlordManager::OverlordMove(const sc2::Unit & moomoo, const sc2::Point2D & destination, CCBot & bot)
{
	// how to access map information? 

	// move overlord to given position
	bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::MOVE, destination);
}

// makes and enforces overlord personal space bubble
// @moomoos		list of overlords
// @bot			bot thing, good thing
void OverlordManager::PersonalSpace(const std::vector<sc2::Unit> & moomoos, CCBot & bot)
{
	// stuff
}

// Tells Overlord to generate creep
// @moomoo	Overlord
// @bot		Bot thing
void OverlordManager::GenerateCreep(const UnitTag & moomoo, CCBot & bot)
{
	bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::BEHAVIOR_GENERATECREEPON);
}

// takes overlord functions and executes them, called in CCBot.cpp
// @bot		bot thing, necessary thing
void OverlordManager::Execute(CCBot & bot)
{
	// makes list of all your units
	for (auto & unit : bot.UnitInfo().getUnits(Players::Self))
	{
		// looks through list of units, checks if they are overlords
		if (bot.GetUnit(unit)->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD)
		{
			// testing generate creep function
			// works! as long as bot is not moving
			OverlordManager::GenerateCreep(unit, bot);

			// if they are overlords, move them to the point specified
			// move and then stop issuing move command?  
			// above logic added in overlord spread function
			// gets the pointer for enemy base location
			const BaseLocation * enemyBaseLocation = bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);

			// returns if enemy base is null, aka unscouted
			if (enemyBaseLocation == nullptr)
			{
				return;
			}

			// if overlord is already at base location, stop moving
			if (unit.pos.x == enemyBaseLocation->getPosition().x && unit.pos.y && enemyBaseLocation->getPosition().x)
			{
				return;
			}

			// call function, move overlord to enemyBaseLocation
			OverlordManager::OverlordMove(unit, enemyBaseLocation->getPosition(), bot);
		}
	}
}