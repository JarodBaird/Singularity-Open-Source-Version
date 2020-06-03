#ifndef SPECIES_H
#define SPECIES_H
#include <string>
#include "../Physics/Chemistry/Chemical.h"

namespace Singularity
{
	class Species
	{
	public:
		enum class Type
		{
			Plant,
			Animal,
			Sentient
		};

	private:
		std::string m_genus_name;
		std::string m_species_name;
		std::string m_common_name;
		Chemical* m_solvent;
		Chemical* m_base;
		Type m_type;
	public:
		Species();
		Species(std::string genus_name, std::string species_name, std::string common_name, Type type, Chemical* solvent,
		        Chemical* base);
		std::string get_scientific_name() const;
		std::string get_common_name() const;
		std::string get_description() const;
	};
}
#endif //SPECIES_H
