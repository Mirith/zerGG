// Manages behavior of Overlords aka moomoos
#include "OverlordManager.h"
#include "BaseLocationManager.h"
#include "Util.h"
#include "CCBot.h"
#include "Common.h"
#include "sc2api/sc2_api.h"
#include "sc2api/sc2_action.h"


// change to scoutNeeded later? triggered at x supply?  why not global?
bool scout = false;

// is called in CCBot's (inherited) OnUnitCreated function
// supposed to scout
// @unit		unit created
// @bot			bot thing
void OverlordManager::OnUnitCreated(const sc2::Unit* unit, CCBot & bot)
{
	// checks if unit is overlord, and if there is a scout or not
	if (unit->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD && scout == false)
	{
		// finds enemy base location
		const BaseLocation * enemyBaseLocation = bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);

		// returns if enemy base is null, aka unscouted
		if (enemyBaseLocation == nullptr)
		{
			return;
		}

		//BaseLocationManager obj(bot);

		// does not like this line here
		//sc2::Point2D & temp = obj.getNextExpansion(Players::Self);

		
		sc2::Point2D & temp = bot.Bases().getNextExpansion(Players::Enemy);

		// points for testing
		const sc2::Point2D & point = sc2::Point2D(50, 50);
		//const sc2::Point2D & point2 = sc2::Point2D(50, 50);
		//const sc2::Point2D & point2 = sc2::Point2D(enemyBaseLocation->getPosition().x, enemyBaseLocation->getPosition().y);

		const std::vector<sc2::Point2D> places = { point, temp };

		OverlordManager::OverlordMove(*unit, places, bot);
		GenerateCreep(unit->tag, bot);

		// scout = true;
	}
}


// Moves Overlord to point specified
// @moomoo		Overlord
// @destination	Coordinates of destination
// @bot			Bot thing, necessary thing
void OverlordManager::OverlordMove(const sc2::Unit & moomoo, const sc2::Point2D & destination, CCBot & bot)
{
	// has overlord been issued a move command? 
	bool moved = false;

	// looks through each order in unit's queue
	for (sc2::UnitOrder order : moomoo.orders)
	{
		// if has a move command or reached destination already
		if (order.ability_id == sc2::ABILITY_ID::MOVE && moomoo.pos.x == destination.x && moomoo.pos.y == destination.y)
		{
			moved = true;
		}
	}

	// ie has no active move commands and is not at destination
	if (!moved)
	{
		// move overlord to a given position
		bot.Actions()->UnitCommand(bot.GetUnit(moomoo.tag), sc2::ABILITY_ID::MOVE, destination, false);
	}
}

// Moves Overlord to points specified
// @moomoo			Overlord
// @destinations	Coordinates of destinations to travel to
// @bot				Bot thing, necessary thing
void OverlordManager::OverlordMove(const sc2::Unit & moomoo, const std::vector<sc2::Point2D> & destinations, CCBot & bot)
{
	std::cout << destinations.size() << std::endl;

	// has overlord been issued a move command? 
	bool moved = false;

	// looks through each order in unit's queue
	for (sc2::UnitOrder order : moomoo.orders)
	{
		// if has a move command or reached last destination in vector already
		if (order.ability_id == sc2::ABILITY_ID::MOVE
			|| (moomoo.pos.x == destinations[destinations.size() - 1].x
				&& moomoo.pos.y == destinations[destinations.size() - 1].y))
		{
			// no need to keep looping
			return;
		}
	}

	// ie has no active move commands and is not at last destination
	if (moved == false)
	{
		// queues move commands from destinations for moomoo
		for (auto point : destinations)
		{
			bot.Actions()->UnitCommand(bot.GetUnit(moomoo.tag), sc2::ABILITY_ID::MOVE, point, true);
		}
	}


}

// Tells Overlord to generate creep
// @moomoo	Overlord
// @bot		Bot thing
void OverlordManager::GenerateCreep(const UnitTag & moomoo, CCBot & bot)
{
	bot.Actions()->UnitCommand(bot.GetUnit(moomoo), sc2::ABILITY_ID::BEHAVIOR_GENERATECREEPON);
}

// uneccesary with OnUnitCreated?
// or needed for creep generation? 

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

		//	// finds enemy base location
		//	const BaseLocation * enemyBaseLocation = bot.Bases().getPlayerStartingBaseLocation(Players::Enemy);

		//	// returns if enemy base is null, aka unscouted
		//	if (enemyBaseLocation == nullptr)
		//	{
		//		return;
		//	}

		//	BaseLocationManager obj(bot);

		//	sc2::Point2D & temp = obj.getNextExpansion(Players::Enemy);
		//	
		//	// points for testing
		//	const sc2::Point2D & point = sc2::Point2D(20, 20);
		//	const sc2::Point2D & point2 = sc2::Point2D(50, 50);
		//	//const sc2::Point2D & point2 = sc2::Point2D(enemyBaseLocation->getPosition().x, enemyBaseLocation->getPosition().y);

		//	const std::vector<sc2::Point2D> places = { point, temp };
		//	
		//	OverlordMove(*unit, places, bot);
		//
		}
	}
}