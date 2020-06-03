#ifndef	__WORD_SET_READER_H
#define __WORD_SET_READER_H
#include "FileReader.h"
#include <vector>
#include <string>

namespace Altair
{
	class WordSetReader final : public FileReader
	{
	private:
		std::vector<std::string> m_data;
		void parse_words(const std::string& file_contents);
	public:
		WordSetReader(const std::string& file_name);
		WordSetReader(const std::string& file_name, const std::string& directory);
		std::vector<std::string> get_words() const;
	};
}
#endif //__WORD_SET_READER_H
