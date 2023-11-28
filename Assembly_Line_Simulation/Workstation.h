#ifndef ASSEMBLY_SIM_WORKSTATION_H
#define ASSEMBLY_SIM_WORKSTATION_H

#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace Assembly_line_Simulation {

	// Global variables. The queues hold the orders at either end of the assembly line.
	extern std::deque<CustomerOrder> g_pending;		// Holds the orders to be placed onto the assembly line at the first station.
	extern std::deque<CustomerOrder> g_completed;	// Holds the orders that have been removed from the last station and have been completely filled.
	extern std::deque<CustomerOrder> g_incomplete;	// Holds the orders that have been removed from the last station and could not be filled completely.

	// Workstation class
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};	/*	A double-ended-queue with CustomerOrders entering the back and exiting the front.
													These are orders that have been placed on this station to receive service */
		Workstation* m_pNextStation{};			// A pointer to the next Workstation on the assembly line.
	public:
		// Constructor with one argument
		Workstation(const std::string);

		// Modifier fills the order at the front of the queue if there are CustomerOrders in the queue; otherwise, does nothing.
		void fill(std::ostream& os);

		// Attempts to move the order order at the front of the queue to the next station in the assembly line.
		bool attemptToMoveOrder();

		// Modifier stores the address of the referenced.
		void setNextStation(Workstation* station = nullptr);

		// Query returns the address of next Workstation.
		Workstation* getNextStation() const;

		// Query inserts the name of the Item for which the current object is responsible into stream os.
		void display(std::ostream& os) const;

		// Moves the CustomerOrder referenced in parameter newOrder to the back of the queue.
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif //!ASSEMBLY_SIM_WORKSTATION_H