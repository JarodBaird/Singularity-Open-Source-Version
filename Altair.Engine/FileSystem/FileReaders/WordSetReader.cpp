#include "WordSetReader.h"
#include <string>
#include <sstream>

namespace Altair
{
	WordSetReader::WordSetReader(const std::string& file_name) { parse_words(read_from_file(file_name)); }

	WordSetReader::WordSetReader(const std::string& file_name, const std::string& directory) : FileReader(
		file_name, directory)
	{
		std::string file;

		if (!directory.empty()) { file = directory + "\\" + file_name; }
		else { file = file_name; }
		parse_words(read_from_file(file));
	}

	void WordSetReader::parse_words(const std::string& file_contents)
	{
		std::istringstream iss(file_contents);
		std::string token;
		while (std::getline(iss, token, '\n')) { m_data.emplace_back(token); }
	}

	std::vector<std::string> WordSetReader::get_words() const { return m_data; }
}
