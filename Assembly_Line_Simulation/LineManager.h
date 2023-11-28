#ifndef ASSEMBLY_SIM_LINEMANAGER_H
#define ASSEMBLY_SIM_LINEMANAGER_H

#include <iostream>
#include <vector>
#include "Workstation.h"
#include "CustomerOrder.h"

namespace Assembly_line_Simulation {

	class LineManager {
		std::vector<Workstation*> m_activeLine{};	// The collection of workstations for the current assembly line
		size_t m_cntCustomerOrder{};				// The total number of CustomerOrder objects
		Workstation* m_firstStation{};				// Points to the first active station on the current line
	public:
		// Constructor with two arguments. Receives the name of the file that identifies the active stations on the assembly line 
		// and the collection of workstations available for configuring the assembly line.
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		// Modifier reorders the workstations present in the instance variable m_activeLine (loaded by the constructor) and stores the reordered collection in the same instance variable. 
		// The elements in the reordered collection start with the first station, proceeds to the next, and so forth until the end of the line.
		void reorderStations();

		// Modifier performs one iteration of operations on all of the workstations in the current assembly line.
		bool run(std::ostream& os);

		// Query displays all active stations on the assembly line in their current order.
		void display(std::ostream& os) const;
	};
}
#endif //!ASSEMBLY_SIM_LINEMANAGER_H

// Desk -> Dresser -> Armchair -> Night table -> Desk -> Office chair -> Filing Cabinet -> Bookcase