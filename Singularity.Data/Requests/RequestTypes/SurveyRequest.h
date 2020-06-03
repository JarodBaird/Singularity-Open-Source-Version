#ifndef __SURVEY_REQUEST_H
#define __SURVEY_REQUEST_H
#include "../Request.h"

namespace Singularity
{
	class SurveyRequest final : public Request
	{
	private:
		int m_x, m_y;
	public:
		SurveyRequest(int x, int y);
		void update(Entity* entity) override;
	};
}
#endif // !__SURVEY_REQUEST_H
