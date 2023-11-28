#ifndef ASSEMBLY_SIM_CUSTOMERORDER_H
#define ASSEMBLY_SIM_CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace Assembly_line_Simulation {
	class CustomerOrder {
		struct Item
		{
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };

			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name;				// The name of the customer
		std::string m_product;			// The name of the product being assembled
		size_t m_cntItem { 0 };			// A count of the number of items in the customer's order
		Item** m_lstItem { nullptr };	// A dynamically allocated Item array of pointers.
		static size_t m_widthField;		// The maximum width of a field, used for display purposes

	public:
		// Default Constructor
		CustomerOrder() = default;

		// Constructor with one argument that takes a reference to an unmodifiable string.
		CustomerOrder(const std::string&);

		// Rules of five
		~CustomerOrder();										// Destructor
		CustomerOrder(const CustomerOrder&);					// Copy constructor
		CustomerOrder& operator=(const CustomerOrder&) = delete;// Prevent copy assignment operator
		CustomerOrder(CustomerOrder&&) noexcept;				// Move constructor
		CustomerOrder& operator=(CustomerOrder&&) noexcept;		// Move assignment operator

		// Check order is filled function.
		bool isOrderFilled() const;

		// Check item is filled function
		bool isItemFilled(const std::string& itemName) const;

		// Fill item function
		void fillItem(Station& station, std::ostream& os);

		// Display fuction
		void display(std::ostream& os) const;
	};
}
#endif //!ASSEMBLY_SIM_CUSTOMERORDER_H
