#ifndef __WORD_SET_H
#define __WORD_SET_H
#include "../Util/Random.h"

namespace Altair
{
	class WordSet
	{
	private:
		Random m_random;
		std::vector<std::string> m_words;
	public:
		size_t get_count() const;
		void add_word(std::string word);
		std::string get_random_word(bool remove_word = false);
	};
}
#endif // !__WORD_SET_H
