#ifndef __COMPOUND_H
#define __COMPOUND_H
#include "../../../Altair.Engine/FileSystem/FileReaders/SettingsReader.h"
#include "Element.h"
#include "Chemical.h"
#include <vector>

namespace Singularity
{
	struct CompoundPart
	{
	public:
		Element* element;
		uint32_t number_of_atoms;
	};

	class Compound final : public Chemical, public Altair::Serializable
	{
	private:
		std::string m_common_name;
		std::string m_formula;
		std::vector<CompoundPart> m_components;
		double m_atomic_weight;
		uint32_t m_complexity;
		std::vector<Element*> m_elements;
		void add_component(const std::string& element_name, std::string number_of_atoms,
		                   const std::vector<Element*>& elements);
	public:
		Compound();
		Compound(std::string name, std::string formula, std::vector<Element*> elements);
		Compound(std::string name, std::string common_name, std::string formula, std::vector<Element*> elements);
		Compound(Altair::SettingsReader file, std::vector<Element*> elements);
		std::string get_common_name() const;
		uint32_t get_complexity() const;
		std::string serialize() override;
	};
}
#endif // !__COMPOUND_H
