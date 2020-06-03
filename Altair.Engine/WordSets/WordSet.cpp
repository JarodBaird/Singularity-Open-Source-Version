#include "WordSet.h"

namespace Altair
{
	size_t WordSet::get_count() const { return m_words.size(); }

	void WordSet::add_word(std::string word) { m_words.push_back(std::move(word)); }

	std::string WordSet::get_random_word(bool remove_word)
	{
		if (get_count() == 0) { return ""; }

		const size_t index = m_random.next_int(static_cast<uint32_t>(m_words.size()));

		std::string word = m_words.at(index);

		if (remove_word) { m_words.erase(m_words.begin() + index); }
		return word;
	}
}
