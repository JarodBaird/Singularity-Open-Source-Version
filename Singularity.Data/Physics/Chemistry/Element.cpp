#include "Element.h"

namespace Singularity
{
	Element::Element()
	{
		m_atomic_number = 0;
		m_atomic_symbol = "";
		m_name = "";
		m_atomic_weight = 0;
	}

	Element::Element(uint16_t atomic_number, std::string atomic_symbol, std::string name, double atomic_weight)
	{
		m_atomic_number = atomic_number;
		m_atomic_symbol = std::move(atomic_symbol);
		m_name = std::move(name);
		m_atomic_weight = atomic_weight;
	}

	Element::Element(Altair::SettingsReader file)
	{
		m_atomic_number = file.get_short("AtomicNumber");
		m_atomic_symbol = file.get("AtomicSymbol");
		m_name = file.get("Name");
		m_atomic_weight = file.get_double("AtomicWeight");
		m_tags = file.get_tags();
	}

	std::string Element::serialize()
	{
		begin_file();
		add_to_file("AtomicNumber", m_atomic_number);
		add_to_file("AtomicSymbol", m_atomic_symbol);
		add_to_file("Name", m_name);
		add_to_file("AtomicWeight", m_atomic_weight);
		return end_file();
	}

	uint16_t Element::get_atomic_number() const { return m_atomic_number; }

	std::string Element::get_atomic_symbol() const { return m_atomic_symbol; }

	double Element::get_atomic_weight() const { return m_atomic_weight; }
}
