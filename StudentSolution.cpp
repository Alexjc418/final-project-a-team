#include "acequia_manager.h"
#include <iostream>

/*Instructions for this problem:

	The intend of this project is to simulate water management conservation principles in the context of New Mexico

	In this simulation, there exists several Regions (North, South, etc.). Each region class includes both:
	- a given water level
	- a given water need
	- a indicator boolean for if the region is flooded
	- an indicator boolean for if the region is in drought

	With each region, there are given waterSources provided (perhaps a .dat file list each waterSource to  a region) 
	and certain waterSources have canals connected to them to deliver water across regions.

	Given the current state of the region, students wil be asked to utlize the canals that connect regions to
	develop the logic and algorithm for finding a solution. The simulation has a fixed time



	The student solution will be evaluated on the criteria that each region meets the following:
	- a given region is NOT flooded
	- a given region is NOT in drought
	- the region waterNeed does not exceed the region waterLevel 
*/


/* My code is here */

void solveProblems(AcequiaManager& manager) {
    std::vector<Canal*>& canals = manager.getCanals();
    std::vector<Region*>& regions = manager.getRegions();
    int maxTime = manager.getSimulationMax();

    std::cout << "-Commencing Simulation-\n";

    int hour = 0;
    while (!manager.getIsSolved() && hour < maxTime) {
        std::cout << "Hour " << hour << ": Checking region status\n";

        for (Region* region : regions) {
            std::cout << "Region: " << region->getName() << "\n"
                      << "Water Level: " << region->getWaterLevel() << "\n"
                      << "Water Need: " << region->getWaterNeed() << "\n"
                      << "In Drought: " << region->isInDroughtStatus() << "\n"
                      << "Flooded: " << region->isFloodedStatus() << "\n";
        }

        for (Canal* canal : canals) {
            Region* source = canal->getSourceRegion();
            Region* dest = canal->getDestinationRegion();

            if (!canal->getIsOpen()) {
                double surplus = source->getWaterLevel() - source->getWaterNeed();
                double deficit = dest->getWaterNeed() - dest->getWaterLevel();

                if (surplus > 10 && deficit > 10) {
                    canal->setFlowRate(0.5);
                    canal->toggleOpen(true);
                    std::cout << "Opened canal: " << canal->getName() << "\n"
                              << "From: " << source->getName() << "\n"
                              << "To: " << dest->getName() << "\n"
                              << "Flow rate: 0.5\n";
                }
            }
        }

        manager.nextHour();
        hour++;
    }

    if (manager.getIsSolved()) {
        std::cout << "Simulation completed successfully at hour " << hour - 1 << ".\n";
    } else {
        std::cout << "Simulation ended after reaching total time (" << maxTime << " hours).\n";
    }

    std::cout << "-Simulation complete-\n";
}

/* My Documentation of the solution*/       
/*My solution starts with solveProblems function which starts the simulation and lets the user know.
 *The simulation runs every hour to check if the region is flooded or in a drought then uses the canals
 *to transfer water into its necessary regions at a flow rate of 0.5. Once the simulation has been completed
 * or the time is up the simulation is finished. manager.nextHour function advances time to the next hour
 * and gives the user an update on what is happening. 
 * manager.getIsSolved function completes simulation when a region meets its conditions. 
 *manager.getCanals, manager.getRegions, & manager.getSimulationMax obtains the information on all canals, regions, and 
 * 			 			 			 			 			 			 * the amount of time the simulation should run for. */






/*This will be how the solveProblems function is set up. The student may enter their on  */
/*
void solveProblems(AcequiaManager& manager)
{
	//the student can call the members of the canals object such as name of canal. sourceRegion, and destinationRegion
	//This could be helpful in informing the students strategy to solve the problem
	auto canals = manager.getCanals();
	//students may call to get Region and WaterSource objects to inform decisions 


	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{	
		//enter student code here


		manager.nexthour();
	}
}
*/


/*example 2 format*/

void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==0)
		{
			canals[0]->setFlowRate(1);
			canals[0]->toggleOpen(true);
		}
		else if(manager.hour==1)
		{
			canals[1]->setFlowRate(0.5);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==82)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}


/*example 2*/
/*
void solveProblems(AcequiaManager& manager)
{
	auto canals = manager.getCanals();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
	//Students will implement this function to solve the probelms
	//Example: Adjust canal flow rates and directions
		if(manager.hour==1)
		{
			canals[0]->setFlowRate(0.1);
			canals[0]->toggleOpen(true);
			canals[1]->setFlowRate(0.2);
			canals[1]->toggleOpen(true);
		}
		else if(manager.hour==3)
		{
			canals[0]->toggleOpen(false);
			canals[1]->toggleOpen(false);
		}
	//student may add any necessary functions or check on the progress of each region as the simulation moves forward. 
	//The manager takes care of updating the waterLevels of each region and waterSource while the student is just expected
	//to solve how to address the state of each region

		
		manager.nexthour();
	}
}
*/


//In this solution, students can make functions that aid in identifying the best course of action for moving
//water resources. They can set conditions that then work on the canal vectors based on the information reported

//This can help in optimizing solutions for dynamic constraints such as weather (rain, or dried up waterSources) and
//make the solution to the problem more abstract, allowing the logic and algorithm to be the sole priority of the student
//while the computation is left for the Acequia Manager

//This would be the perfect opportunity to identify the tools learned from ECE 231L such as:
//data structures (stacks, queues, trees(?)), templates, vector class functions, etc... to aid in the algorithm solution

/*
int findCanal(std::vector<Canal *> canals, std::string region)
{
	int match;
	for(int i = 0; i< canals.size();i++)
	{
		if(canals[i]->sourceRegion->name == region)
		{
			match = i;
		}
	}
	return match;
}

void release(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(true);
	canals[match]->setFlowRate(1);
	return;
}

void close(std::vector<Canal *> canals, std::string region)
{
	int match = findCanal(canals, region);
	canals[match]->toggleOpen(false);
}


void solveProblems(AcequiaManager& manager)
{

	bool check = false;
	auto canals = manager.getCanals();
	auto regions = manager.getRegions();
	while(!manager.isSolved && manager.hour!=manager.SimulationMax)
	{
		
		if(manager.hour == 0)
		{
			for(int i = 0; i<canals.size(); i++)
			{
				canals[i]->toggleOpen(true);
				canals[i]->setFlowRate(1);
			}
		}

		for(int i =0 ; i<regions.size(); i++)
		{
			if(regions[i]->isFlooded == true)
			{
				//release water from that region by a canal
				release(canals, regions[i]->name);
			}
			else if(regions[i]->isInDrought = true)
			{
				//find canal to move water
				close
			}

			else if(regions[i]->isFlooded == true && regions[i]->isInDrought == true)
			{
				close(canals, regions[i]->name);
			}
		}
		
		manager.nexthour();
	}
}
*/
