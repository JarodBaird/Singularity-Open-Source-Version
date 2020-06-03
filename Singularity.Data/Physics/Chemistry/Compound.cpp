#include "Compound.h"

#include <utility>

namespace Singularity
{
	void Compound::add_component(const std::string& element_name, std::string number_of_atoms,
	                             const std::vector<Element*>& elements)
	{
		if (number_of_atoms.empty()) { number_of_atoms = "1"; }
		CompoundPart component{
			nullptr, 0
		};
		for (Element* element : elements)
		{
			if (element->get_atomic_symbol() == element_name)
			{
				component.element = element;
				break;
			}
		}
		if (component.element != nullptr)
		{
			component.number_of_atoms = std::stoi(number_of_atoms);
			m_components.push_back(component);
		}
	}

	Compound::Compound()
	{
		m_atomic_weight = 0;
		m_complexity = 0;
	}

	Compound::Compound(std::string name, std::string formula, std::vector<Element*> elements) :
		Compound(std::move(name), "", std::move(formula), std::move(elements)) { }

	Compound::Compound(std::string name, std::string common_name, std::string formula,
	                   std::vector<Element*> elements) : m_elements(std::move(elements))
	{
		m_name = std::move(name);
		m_common_name = std::move(common_name);
		m_formula = std::move(formula);
		m_complexity = 0;
		m_atomic_weight = 0;

		std::string element_name;
		std::string number;

		for (char letter : m_formula)
		{
			if (letter >= 'A' && letter <= 'Z')
			{
				// If letter is capitalized.
				if (!element_name.empty())
				{
					add_component(element_name, number, elements);
					number = "";
				}
				element_name = letter;
			}

			if (letter >= 'a' && letter <= 'z')
			{
				// If letter is lowercased.
				element_name += letter;
			}

			if (letter >= '0' && letter <= '9')
			{
				// If character is a number.
				number += letter;
			}
		}

		add_component(element_name, number, elements);
		for (CompoundPart part : m_components)
		{
			m_complexity += part.element->get_atomic_number() * part.number_of_atoms;
			m_atomic_weight += part.element->get_atomic_weight() * part.number_of_atoms;
		}
	}

	Compound::Compound(Altair::SettingsReader file, std::vector<Element*> elements)
		: Compound(file.get("Name"), file.get("CommonName"), file.get("Formula"),
		           std::move(elements)) { m_tags = file.get_tags(); }

	std::string Compound::get_common_name() const { return m_common_name; }

	std::string Compound::serialize()
	{
		begin_file();
		add_to_file("Name", m_name);
		add_to_file("CommonName", m_common_name);
		add_to_file("Formula", m_formula);
		return end_file();
	}

	uint32_t Compound::get_complexity() const { return m_complexity; }
}
