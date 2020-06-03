#include "SurveyRequest.h"
#include "../../Entities/Entity.h"

namespace Singularity
{
	SurveyRequest::SurveyRequest(int x, int y) : Request({ActionType::Move}, 0)
	{
		m_x = x;
		m_y = y;
	}

	void SurveyRequest::update(Entity* entity)
	{
		entity->move_towards(m_x, m_y);
		if (entity->get_x() == m_x && entity->get_y() == m_y) { mark_complete(); }
	}
}
