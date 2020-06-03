#include "Worker.h"

namespace Singularity
{
	Worker::Worker(Civilization* owner, CelestialBody* body)
	{
		m_color = Altair::Color::purple;
		m_tile = 0x62;
		m_owner = owner;
		m_body = body;
	}

	void Worker::update() { }
}
