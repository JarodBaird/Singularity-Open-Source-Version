#include "Random.h"
#include <ctime>

namespace Altair
{
	Random::Random() : Random(get_random_seed(), 0) {}

	Random::Random(const std::string& seed) : Random(static_cast<uint32_t>(std::hash<std::string>{}(seed))) {}

	Random::Random(const std::string& seed, uint64_t numbers_generated) : Random(
		static_cast<uint32_t>(std::hash<std::string>{}(seed)), numbers_generated) {}

	Random::Random(uint32_t seed) : Random(seed, 0) {}

	Random::Random(uint32_t seed, uint64_t numbers_generated) // NOLINT(cert-msc51-cpp)
	{
		m_engine.seed(seed);
		m_engine.discard(numbers_generated);
		m_numbers_generated = numbers_generated;
	}

	uint32_t Random::get_random_seed() { return static_cast<uint32_t>(time(nullptr)); }

	uint32_t Random::next_int()
	{
		const int num = m_engine();
		m_numbers_generated++;
		return num;
	}

	uint32_t Random::next_int(uint32_t max)
	{
		const uint32_t num = m_engine() % max;
		m_numbers_generated++;
		return num;
	}

	uint32_t Random::next_int(uint32_t min, uint32_t max)
	{
		const uint32_t num = m_engine() % (max - min) + min;
		m_numbers_generated++;
		return num;
	}

	bool Random::next_bool()
	{
		if (m_engine() % 2 == 0) { return true; }
		return false;
	}

	uint64_t Random::get_gen_count() const { return m_numbers_generated; }
}
