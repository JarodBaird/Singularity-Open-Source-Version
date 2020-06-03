#ifndef __ELEMENT_H
#define __ELEMENT_H
#include <string>
#include "../../../Altair.Engine/FileSystem/FileReaders/SettingsReader.h"
#include "Chemical.h"

namespace Singularity
{
	class Element final : public Chemical, public Altair::Serializable
	{
	private:
		uint16_t m_atomic_number;
		std::string m_atomic_symbol;
		double m_atomic_weight;
	public:
		Element();
		Element(uint16_t atomic_number, std::string atomic_symbol, std::string name, double atomic_weight);
		Element(Altair::SettingsReader file);
		uint16_t get_atomic_number() const;
		std::string get_atomic_symbol() const;
		double get_atomic_weight() const;
		std::string serialize() override;
	};
}
#endif // !__ELEMENT_H
