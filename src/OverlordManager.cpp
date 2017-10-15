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
	// move overlord to given position
	bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::MOVE, destination);
}

// Moves Overlord to points specified
// @moomoo			Overlord
// @destinations	Coordinates of destination
// @bot				Bot thing, necessary thing
// how to queue up unit move commands?
void OverlordManager::OverlordMove(const UnitTag & moomoo, const std::vector<sc2::Point2D> & destinations, CCBot & bot)
{
	// CURRENT STRUCTURE DOES NOT WORK
	// WILL RESET INDEX TO 0 EVERY TIME IT IT CALLED, AKA EACH FRAME
	int index = 0;

	// queue up points from destinations for overlord passed

	while (index < destinations.size())
	{
		if (!(bot.GetUnit(moomoo)->pos.x == destinations[index].x && bot.GetUnit(moomoo)->pos.y == destinations[index].y))
		{
			bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::MOVE, destinations[index]);
			return;
		}
		else
		{
			index++;
		}
	}


	//
	//// first in int vector is unit tag
	//std::vector<std::vector> temp = { int(moomoo) };

	//// second and on is another vector with coordinates of point2d to move to
	//// separated by a negative one in first vector
	//int index = 1;

	//for (auto & point : destinations)
	//{
	//	temp.insert(temp.end(), { int(point.x), int(point.y) });
	//	temp.insert(temp.end(), -1);
	//}

	//if (bot.GetUnit(temp[0])->pos.x == temp[index][0] && bot.GetUnit(temp[0])->pos.y == temp[index][1])
	//{
	//	bot.Actions->UnitCommand(moomoo, sc2::ABILITY_ID::MOVE, temp);
	//}
	//else
	//{
	//	index++;
	//	if (index > destinations.end())
	//	{
	//		return;
	//	}
	//}

	
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
		if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD)
		{
			// testing generate creep function
			// works! as long as bot is not moving
			OverlordManager::GenerateCreep(unit->tag, bot);

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
			if (unit->pos.x == enemyBaseLocation->getPosition().x && unit->pos.y && enemyBaseLocation->getPosition().x)
			{
				return;
			}

			// call function, move overlord to enemyBaseLocation
			//OverlordManager::OverlordMove(unit, enemyBaseLocation->getPosition(), bot);
		/*	const sc2::Point2D & point = sc2::Point2D(50, 50);
			const sc2::Point2D & point2 = sc2::Point2D(enemyBaseLocation->getPosition().x, enemyBaseLocation->getPosition().y);

			std::vector<sc2::Point2D> places = { point, point2 };*/

			OverlordMove(&unit, sc2::Point2D(50, 50), bot);
		}
	}
}