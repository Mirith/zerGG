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
void OverlordManager::OverlordSpread(const UnitTag & moomoo, const sc2::Point2D & place, CCBot & bot)
{
	// need to figure out where to move overlords and spread them out
	// create array or list of valid points for each map?  
	// make a 5x5 grid?  
	// how to access map information? 
	bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::MOVE, place);
	// patrol from spatialunitcommand... 
	//if (moomoo.Unit().Point3D.x == 50 && moomoo.Unit().Point3D.y == 50)
	//{
		//bot.ActionsFeatureLayer()->SpatialUnitCommand(moomoo, sc2::ABILITY_ID::PATROL, sc2::Point2D(100,100), TRUE);
	//}
}

// Tells Overlord to generate creep after arriving at some spot (need to pass in later)
// need lair upgrade to generate creep... haven't done that yet
// @moomoo	Overlord
// @bot		Bot thing
void OverlordManager::GenerateCreep(const UnitTag & moomoo, CCBot & bot)
{
	sc2::Point3D moo = bot.GetUnit(moomoo)->pos;
	//std::cout << "OverlordPosition: " << moo.z;
	if (moo == sc2::Point3D(50, 50, 0))
	{
		bot.Actions()->UnitCommand(moomoo, sc2::ABILITY_ID::BEHAVIOR_GENERATECREEPON);
	}
}

// Tells a Overlord to go scout somewhere
// @moomoo	Overlord
// @place	Coordinates of destination
// @bot		Bot thing, necessary thing
void OverlordManager::Scout(const UnitTag & scout, const sc2::Point2D & place, CCBot & bot)
{
	// want to send overlord to enemy base, to a place they don't see
	// check via api? legal?
	// or find high ground and sit there, make sure creep can be spread.  
}

// takes overlord functions and executes them, called in CCBot.cpp
// @bot		bot thing, necessary thing
void OverlordManager::Execute(CCBot & bot)
{
	// makes list of all your units
	for (auto & unitTag : bot.UnitInfo().getUnits(Players::Self))
	{
		// looks through list of units, checks if they are overlords
		if (bot.GetUnit(unitTag)->unit_type == sc2::UNIT_TYPEID::ZERG_OVERLORD)
		{
			// if they are overlords, move them to the point specified.  
			OverlordManager::GenerateCreep(unitTag, bot);
			//OverlordManager::OverlordSpread(unitTag, sc2::Point2D(50, 50), bot);
		}
	}
}