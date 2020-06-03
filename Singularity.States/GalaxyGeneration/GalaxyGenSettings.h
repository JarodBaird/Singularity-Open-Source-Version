#ifndef __GALAXY_GEN_SETTINGS_H
#define __GALAXY_GEN_SETTINGS_H
#include <string>

namespace Singularity
{
	enum class GalaxySize
	{
		Dwarf,
		Small,
		Medium,
		Large,
		ExtraLarge
	};

	enum class HistoryLength
	{
		VeryShort = 5,
		Short = 25,
		Medium = 50,
		Long = 75,
		VeryLong = 100
	};

	struct GalaxyGenSettings
	{
	public:
		GalaxyGenSettings();
		std::string galaxy_name;
		uint32_t seed;
		GalaxySize size;
		HistoryLength history_length;
	};
}
#endif // !__GALAXY_GEN_SETTINGS_H
