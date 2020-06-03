#ifndef __WORD_BANK_H
#define __WORD_BANK_H
#include <map>
#include "WordSet.h"

namespace Altair
{
	class WordBank
	{
	private:
		std::map<std::string, WordSet> m_word_sets;
	public:
		WordBank() = default;
		~WordBank();
		WordBank(const WordBank&) = default;
		WordBank(WordBank&&) = default;
		WordBank& operator =(const WordBank&) = default;
		WordBank& operator =(WordBank&&) = default;
		void add_word_to_set(const std::string& set, std::string word);
		std::string generate_string(const std::string& pattern);
	};
}
#endif // !__WORD_BANK_H
