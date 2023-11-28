#include <iostream>
#include <deque>
#include "Workstation.h"

namespace Assembly_line_Simulation {

	// Global variables
	std::deque<CustomerOrder> g_pending;
	std::deque<CustomerOrder> g_completed;
	std::deque<CustomerOrder> g_incomplete;

	// Passes the received string (station) to the base class (Station)
	Workstation::Workstation(const std::string station) : Station(station) { }

	// Fills the order to the front of the queue (m_orders)
	void Workstation::fill(std::ostream& os)
	{
		// Check if "m_orders" is not empty
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);
	}

	// Attempt to move order to next station if still has the items in the inventory. If no more item then retrun false.
	bool Workstation::attemptToMoveOrder()
	{
		bool moved{ false };
		// Checks if orders are not empty
		if (!m_orders.empty()) {

			// Checks if order cannot be filled from out of inventory or the item is already filled
			if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {

				// Checks if there are no next station
				if (!m_pNextStation) {

					// If order is filled, then move the order to "g_completed"
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(std::move(m_orders.front()));
					// If order is not filled, then move the order to "g_incomplete"
					else
						g_incomplete.push_back(std::move(m_orders.front()));
				}
				// If still has the next station, then move the order to the front of the queue to the next station
				else
					*m_pNextStation += std::move(m_orders.front());

				// Pop the completed order
				m_orders.pop_front();

				// Set move status to true (Completed)
				moved = true;
			}
		}
		return moved;
	}

	// Set "m_pNextStation" points to the address of received parameter 
	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	// Return "m_pNextStation"
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	// Insert the Ostream as the format: ITEM_NAME --> NEXT_ITEM_NAME
	void Workstation::display(std::ostream& os) const
	{
		os << this->getItemName() << " --> ";
		// Check if not the last item, then insert the next item's name
		if (m_pNextStation)
			os << m_pNextStation->getItemName();
		// Otherwise insert "End of Line"
		else
			os << "End of Line";
		os << std::endl;
	}

	// Push received order to an "m_orders"
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}
