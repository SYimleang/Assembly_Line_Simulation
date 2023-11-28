#ifndef ASSEMBLY_SIM_STATION_H
#define ASSEMBLY_SIM_STATION_H

#include <iostream>
#include "Utilities.h"

namespace Assembly_line_Simulation {
	class Station {
		int m_id;					// The id of the station
		std::string m_itemName;		// The name of the item handled by the station
		std::string m_desc;			// The description of the station
		size_t m_serialNum;			// The next serial number to be assigned to an item at this station
		size_t m_qty;				// The number of items currently in stock
		static size_t m_widthField;	// The maximum number of characters required to print the item name to the screen for any object of type Station
		static int id_generator;	// A variable used to generate IDs for new instances of type Station
	public:
		// Constructor with one argument.
		Station(const std::string);

		// Returns the name of the current Station object
		const std::string& getItemName() const;

		// Returns the next serial number to be used on the assembly line and increments m_serialNumber.
		size_t getNextSerialNumber();

		// Returns the remaining quantity of items in the Station object
		size_t getQuantity() const;

		// Subtracts 1 from the available quantity (not drop below 0)
		void updateQuantity();

		// Inserts information about the current object into stream os.
		void display(std::ostream& os, bool full) const;
	};
}
#endif //!ASSEMBLY_SIM_STATION_H
