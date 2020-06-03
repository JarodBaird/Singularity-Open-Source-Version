#ifndef __RANDOM_H
#define __RANDOM_H
#include <vector>
#include <random>

namespace Altair
{
	class Random
	{
	private:
		uint32_t m_seed = 0;
		int64_t m_numbers_generated = 0;
		std::default_random_engine m_engine;
	public:
		Random();
		Random(const std::string& seed);
		Random(uint32_t seed);
		Random(const std::string& seed, uint64_t numbers_generated);
		Random(uint32_t seed, uint64_t numbers_generated);

		static uint32_t get_random_seed();

		template <class T>
		T pick(std::vector<T> vect) { return vect.at(next_int(vect.size())); }

		uint32_t next_int();
		uint32_t next_int(uint32_t max);
		uint32_t next_int(uint32_t min, uint32_t max);

		bool next_bool();

		uint64_t get_gen_count() const;
	};
}
#endif // !__RANDOM_H
