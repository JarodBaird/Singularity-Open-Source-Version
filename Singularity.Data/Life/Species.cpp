#include "Species.h"

namespace Singularity
{
	Species::Species()
	{
		m_type = Type::Plant;
		m_base = nullptr;
		m_solvent = nullptr;
	}

	Species::Species(std::string genus_name, std::string species_name, std::string common_name, Type type,
	                 Chemical* solvent, Chemical* base)
	{
		m_genus_name = std::move(genus_name);
		m_species_name = std::move(species_name);
		m_common_name = std::move(common_name);
		m_solvent = solvent;
		m_base = base;
		m_type = type;
	}

	std::string Species::get_scientific_name() const { return m_genus_name + " " + m_species_name; }

	std::string Species::get_common_name() const { return m_common_name; }

	std::string Species::get_description() const
	{
		std::string ret_val = get_scientific_name() + ", more commonly known as " + m_common_name + ", is a";
		switch (m_type)
		{
		case Type::Plant:
			ret_val += " plant. ";
			break;
		case Type::Animal:
			ret_val += "n animal. ";
			break;
		case Type::Sentient:
			ret_val += "n intelligent creature. ";
			break;
		}
		ret_val += "It is " + m_base->get_name() + "-based and consumes " + m_solvent->get_name() +
			" for use as a solvent.";

		return ret_val;
	}
}
