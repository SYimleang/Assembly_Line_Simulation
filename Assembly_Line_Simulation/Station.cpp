#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"

// Initialize "m"m_widthField" and "id_generator"
size_t Station::m_widthField = 0;
int Station::id_generator = 0;

// Constructor populates the Station object accordingly
Station::Station(const std::string str)
{
	Utilities util;
	bool more = true;
	size_t next_pos = 0;

	// Generate new "m_id"
	m_id = ++id_generator;

	// Extract "m_itemName", "m_serialNum" and "m_qty"
	m_itemName = util.extractToken(str, next_pos, more);
	m_serialNum = std::stoul(util.extractToken(str, next_pos, more));
	m_qty = std::stoul(util.extractToken(str, next_pos, more));

	// Update "m_widthField" of Station and Utilities objects
	util.setFieldWidth(m_itemName.length());
	if (m_itemName.length() > m_widthField)
		m_widthField = m_itemName.length();

	// Extract "m_itemName", "m_serialNum" and "m_qty"
	m_desc = util.extractToken(str, next_pos, more);
}

// Returns m_itemName
const std::string& Station::getItemName() const
{
	return m_itemName;
}

// Returns "m_serialNum"
size_t Station::getNextSerialNumber()
{
	return m_serialNum;
}

// Returns "m_qty"
size_t Station::getQuantity() const
{
	return m_qty;
}

// Update "m_qty"
void Station::updateQuantity()
{
	if (m_qty > 0)
		--m_qty;
}

// Inserts all data of the object to ostream as the format. Second parameter indicate the type of format (full or abbreviated)
void Station::display(std::ostream& os, bool full) const
{
	os << std::right << std::setw(3) << std::setfill('0') << m_id << " | " 
		<< std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << " | " 
		<< std::right << std::setw(6) << std::setfill('0') << m_serialNum << " | ";

	// Check if "full" is true, then print as full format
	if (full) {
		os << std::setw(4) << std::setfill(' ') << m_qty << " | " 
			<< std::left << m_desc;
	}
	os << std::endl;
}


