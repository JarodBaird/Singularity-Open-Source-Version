#include "WordBank.h"

namespace Altair
{
	WordBank::~WordBank() { m_word_sets.clear(); }

	void WordBank::add_word_to_set(const std::string& set, std::string word)
	{
		m_word_sets[set].add_word(std::move(word));
	}

	std::string WordBank::generate_string(const std::string& pattern)
	{
		enum class SearchState
		{
			ReadingRawInput,
			ReadingWordSet
		};

		SearchState state = SearchState::ReadingRawInput;
		std::string ret_val;
		std::string word_set;

		for (char c : pattern)
		{
			if (c == '{') { state = SearchState::ReadingWordSet; }
			else if (c == '}')
			{
				state = SearchState::ReadingRawInput;
				if (m_word_sets.count(word_set))
				{
					const std::string word = m_word_sets[word_set].get_random_word();
					ret_val += word;
				}
				word_set = "";
			}
			else
			{
				if (state == SearchState::ReadingWordSet) { word_set += c; }
				else { ret_val += c; }
			}
		}

		return ret_val;
	}
}
