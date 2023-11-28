#include <iomanip>
#include "CustomerOrder.h"

namespace Assembly_line_Simulation {
	// Initialize "m_widthField"
	size_t CustomerOrder::m_widthField = 0;

	// Constructor with one argument. Add item informations to "m_lstItem"
	CustomerOrder::CustomerOrder(const std::string& str)
	{
		Utilities util{};
		bool more = true;
		size_t next_pos = 0;

		// Extract the token for "m_name" and "m_product"
		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);

		// set start position of the item list
		size_t start_itemPos = next_pos;

		// Loop to count number if items
		while (more) {

			util.extractToken(str, next_pos, more);

			// Increase number of item
			++m_cntItem;
		}

		// Reset to start position of the item list
		next_pos = start_itemPos;
		more = true;

		// Loop to extract the item in the list and Dynamically allocating memory for the array of pointers
		m_lstItem = new Item * [m_cntItem];
		for (size_t i = 0; i < m_cntItem; i++) {
			m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
		}

		// Update "m_widthField" of CustomerOrder object
		if(m_widthField < m_product.length())
			m_widthField = m_product.length();
	}

	// Destructor.
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}

	// Throw an exception from copy constructor
	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		// Throw an exception
		throw std::string("Copy operations are not allowed.");
	}

	// Move onstrutor
	CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept
	{
		*this = std::move(other);
	}

	// Move assignment operator
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept
	{
		// Chek self assignment
		if (this != &other) {

			// Cleanup dynamic array
			for (size_t i = 0; i < m_cntItem; ++i)
				delete m_lstItem[i];
			delete[] m_lstItem;

			// Move the resource
			m_name = other.m_name;
			m_product = other.m_product;
			m_cntItem = other.m_cntItem;
			m_lstItem = other.m_lstItem;

			other.m_name = "";
			other.m_product = "";
			other.m_cntItem = 0;
			other.m_lstItem = nullptr;
		}
		return *this;
	}

	// Returns true if all the items in the order have been filled.
	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	// Returns true if all items specified by itemName have been filled. If the item doesn't exist in the order, this query returns true.
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) {
				return false;
			}
		}
		return true;
	}

	// Modifier fills one item in the current order that the Station specified in the first parameter handles.
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool isFilled{ false };
		// Loop all item in the station that not filled yet
		for (size_t i = 0; i < m_cntItem && !isFilled; ++i) {

			// Check if item name is matches and is not filled yet
			if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled) {

				// Check if the quantity of item still remaining
				if (station.getQuantity() > 0 ) {

					// Generate serial number
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

					// Set to filled
					m_lstItem[i]->m_isFilled = true;

					// Update quantity
					station.updateQuantity();

					// Set current item as filled
					isFilled = true;

					// Display filling information
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				// If the quantity is no more, then display the message
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}
	}

	// Displays the state of the current object in the format
	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << std:: right << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
			os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName;
			os << (m_lstItem[i]->m_isFilled ? " - FILLED" : " - TO BE FILLED") << std::endl;
		}
	}
}

