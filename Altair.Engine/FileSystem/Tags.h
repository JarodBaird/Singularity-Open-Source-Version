#ifndef __TAGS_H
#define __TAGS_H
#include <vector>
#include <string>

namespace Altair
{
	class Tags
	{
	private:
		std::vector<std::string> m_tags;
	public:
		bool has_tag(const std::string& tag) const;
		void add_tag(std::string tag);
		std::vector<std::string> get_all_tags() const;
	};
}
#endif // !__TAGS_H
