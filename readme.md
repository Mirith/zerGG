**Last updated on 10-9-17** by [Mirith](https://github.com/Mirith)

# Overview

Modified version of David Churchill's CommandCenter, also on [github](https://github.com/davechurchill/commandcenter).  He has a much better readme, please look at that too.  



For Zerg though.  Overall strategy is two-base all-in with Roaches, Queens, and Nydus network into enemy's main base.  

# Usage

FUN.  And healthy competition.  

Download everything, build it, and then run it.  Command prompt should open, then a small Starcraft window.  Bot wins against easy AI every time!  Well, it should... 



# Files

There's a lot.  Adding more as they become relevant.  

## bin/BotConfig.txt

This is where you pick your strategy and race and lots of other stuff.  

Make step size bigger to make games run faster (tells bot to only run code every _ seconds).  

Set your race to whatever you want it to be.  And add/pick strategies at the very bottom.  

## src/OverlordManager.cpp

Manages Overlord behavior, separately from MicroManager.  

Functions for spreading them out across the map, generating creep, and scouting a location

## src/BuildingManager.cpp

Manages building placement and upgrades.  

I added functions to create a Nydus worm from a network (not working currently...) and to upgrade a hatch to a lair.  

Later, I'll make it more generic to accomodate all upgrades for all buildings depending on parameters passed.  

