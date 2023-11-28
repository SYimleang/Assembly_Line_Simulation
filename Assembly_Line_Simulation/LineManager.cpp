#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "LineManager.h"

namespace Assembly_line_Simulation {

	// Constructor to initialize the active line and its next station
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
        Utilities utils{};
        bool more = true;
        size_t next_pos = 0;
        std::string foundStation{};

        // Temporary vectors to hold the current station (Left-side) and its next station (Right-side)
        std::vector<std::string> currentStation;
        std::vector<std::string> nextStation;


        // Open the file from received parameter
        std::ifstream iFile(file);

        // Checking the file if open properly
        if (!iFile) {
            throw "ERROR: Unable to open the file";
        }

        std::string line{};
        size_t start_itemPos = next_pos;

        // Loop all line of the file
        while (std::getline(iFile, line)) {

            // Resetting the index
            next_pos = start_itemPos;

            // Storing the names of the current and the next stations
            std::string tempCurrStation{}, tempNextStation{};
            tempCurrStation = utils.extractToken(line, next_pos, more);

            // Check if there are no next station by checking the next position, if next position is same as before means there is no delimiter.
            if (!(next_pos == start_itemPos)) {
                tempNextStation = utils.extractToken(line, next_pos, more);

                // Adding the stations to the temporary vectors
                currentStation.push_back(tempCurrStation);
                nextStation.push_back(tempNextStation);
            }

            // Finding the current station in the collection
            auto currStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                return station->getItemName() == tempCurrStation;
                });

            // Adding the found station address to the active line
            m_activeLine.push_back(*currStation);

            // Finding the next station in the collection
            if (tempNextStation.length() > 0) {
                auto nextStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
                    return station->getItemName() == tempNextStation;
                    });

                // Setting the found next station address to its next station
                (*currStation)->setNextStation(*nextStation);
            }
        }

        // Close the file
        iFile.close();

        // Loop for_each all members in the current vector station
        std::for_each(currentStation.begin(), currentStation.end(), [&](std::string station) {

            // Reset found station to false
            bool found = false;

            // Loop for_each all members in the nextStation vector station to check if found the next station
            std::for_each(nextStation.begin(), nextStation.end(), [&](std::string nStation) {

                // Check if current station member matches next station member. Then set "found" to true
                if (station == nStation)
                    found = true;
                });

            // Check that if not found the next station
            if (!found)
                foundStation = station;
            }
        );

        // Searh for first station member and assign index to "firstStation"
        auto firstStation = std::find_if(stations.begin(), stations.end(), [&](Workstation* station) {
            return station->getItemName() == foundStation;
            });

        // Set first station ("m_firstStation") to the found first station index("firstStation")
        m_firstStation = *firstStation;

        // Setting the count of customer orders that are still pending
        m_cntCustomerOrder = g_pending.size();
	}

	// Reorder workstations
	void LineManager::reorderStations()
	{
		std::vector<Workstation*> orderedActiveLine;		// Temporary active line
		Workstation* currentWorkstation = m_firstStation;	// Temporary station to sort, Initial as first station

		// Loop for all stations until there are no next station
		while (currentWorkstation) {

			// Push temporary station to temporary active line
			orderedActiveLine.push_back(currentWorkstation);

			// Set temporary station to the next station
			currentWorkstation = currentWorkstation->getNextStation();
		}

		// Set active line to temporary active line (ordered)
		m_activeLine = orderedActiveLine;
	}

	// Performs one iteration of operations on all of the workstations in the current assembly line
	bool LineManager::run(std::ostream& os)
	{
		static size_t itCnt = 1;	// Iteration counter to keep track the current iteration number

		// Insert ostream to display the iteration number
		os << "Line Manager Iteration: " << itCnt++ << std::endl;

		// Check if "g_pending" is not empty
		if (!g_pending.empty()) {

			// Moves the order at the front of the "g_pending" queue to the "m_firstStation"
			*m_firstStation += std::move(g_pending.front());

			// Remove it from the "g_pending" queue
			g_pending.pop_front();
		}
		
		// For each station on the line, executes one fill operation.
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) {
			i->fill(os);
			});

        // For each station on the line, attempts to move an order down the line.
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto& i) {
            i->attemptToMoveOrder();
            });

		// Return true if all customer orders have been filled or cannot be filled (completed + incompleted is equal to number of orders)
		return (g_incomplete.size() + g_completed.size()) == m_cntCustomerOrder;
	}

	// Display all active stations on the assembly line
	void LineManager::display(std::ostream& os) const
	{
		// Loop all active line to display stations
		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](auto station) {station->display(os); });
	}
}
