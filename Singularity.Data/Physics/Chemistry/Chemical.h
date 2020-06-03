#ifndef __CHEMICAL_H
#define __CHEMICAL_H
#include <string>
#include "../../../Altair.Engine/FileSystem/Tags.h"

namespace Singularity
{
	class Chemical
	{
	protected:
		std::string m_name;
		Altair::Tags m_tags;
	public:
		Chemical();
		virtual ~Chemical() = default;
		Chemical(const Chemical&) = default;
		Chemical(Chemical&&) = default;
		Chemical& operator =(const Chemical&) = delete;
		Chemical& operator =(Chemical&&) = default;
		std::string get_name() const;
		bool has_tag(const std::string& tag) const;
	};
}
#endif // !__CHEMICAL_H
