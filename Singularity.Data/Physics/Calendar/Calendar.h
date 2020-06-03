#ifndef __CALENDAR_H
#define __CALENDAR_H
#include <string>

namespace Singularity
{
	struct CalendarSettings
	{
		uint32_t ticks_per_day = 128;
		uint32_t days_per_month = 30;
		uint32_t months_per_year = 12;
	};

	class Calendar
	{
	private:
		CalendarSettings m_settings;
		uint16_t m_year = 0;
		uint8_t m_month = 0;
		uint8_t m_day = 0;
		uint8_t m_hour = 0;
	public:
		Calendar();
		Calendar(CalendarSettings settings);
		void tick();
		std::string get_star_date() const;
	};
}
#endif // !__CALENDAR_H
