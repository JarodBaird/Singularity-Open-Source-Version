#include "Calendar.h"

namespace Singularity
{
	Calendar::Calendar() = default;

	Calendar::Calendar(CalendarSettings settings) { m_settings = settings; }

	void Calendar::tick()
	{
		m_hour++;

		if (m_hour >= m_settings.ticks_per_day)
		{
			m_day++;
			m_hour = 0;
		}

		if (m_day >= m_settings.days_per_month)
		{
			m_month++;
			m_day = 0;
		}

		if (m_month >= m_settings.months_per_year)
		{
			m_year++;
			m_month = 0;
		}
	}

	std::string Calendar::get_star_date() const
	{
		return std::to_string(m_year) + '.' + std::to_string(m_month) + '.' + std::to_string(m_day);
	}
}
