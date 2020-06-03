#include "StarchartObject.h"
#include <algorithm>

namespace Singularity
{
	StarchartObject::StarchartObject()
	{
		m_x = 0;
		m_y = 0;
		m_name = "";
	}

	StarchartObject::StarchartObject(int x, int y, std::string name)
	{
		m_x = x;
		m_y = y;
		m_name = std::move(name);
	}

	StarchartObject::StarchartObject(Altair::SettingsReader file)
	{
		m_x = file.get_int("X");
		m_y = file.get_int("Y");
		m_name = file.get("Name");
	}

	StarchartObject::~StarchartObject()
	{
		for (CelestialBody* parent : m_parents) { delete parent; }
		m_parents.clear();

		for (CelestialBody* child : m_children) { delete child; }
		m_children.clear();
	}

	int StarchartObject::get_x() const { return m_x; }

	int StarchartObject::get_y() const { return m_y; }

	std::string StarchartObject::get_name() const { return m_name; }

	void StarchartObject::add_parent(CelestialBody* parent)
	{
		parent->set_system(this);
		m_parents.push_back(parent);

		std::sort(m_children.begin(), m_children.end(), [](CelestialBody* a, CelestialBody* b)
		{
			return a->get_name() < b->get_name();
		});
	}

	CelestialBody* StarchartObject::get_parent() { return m_parents.at(0); }

	void StarchartObject::add_child(CelestialBody* child)
	{
		child->set_system(this);
		m_children.push_back(child);
		std::sort(m_children.begin(), m_children.end(), [](CelestialBody* a, CelestialBody* b)
		{
			return a->get_name() < b->get_name();
		});
	}

	std::vector<CelestialBody*> StarchartObject::get_children() const { return m_children; }

	Altair::Sprite StarchartObject::to_sprite(int x, int y) { return get_parent()->to_sprite(x, y); }

	void StarchartObject::update()
	{
		for (CelestialBody* parent : m_parents) { parent->update(); }

		for (CelestialBody* child : m_children) { child->update(); }
	}

	std::string StarchartObject::serialize()
	{
		begin_file();
		add_to_file("Name", m_name);
		add_to_file("X", m_x);
		add_to_file("Y", m_y);
		return end_file();
	}
}
