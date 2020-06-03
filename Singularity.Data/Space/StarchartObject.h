#ifndef __STARCHART_BODY
#define __STARCHART_BODY
#include <vector>

#include "Altair.Engine/Graphics/Sprite.h"
#include "Altair.Engine/FileSystem/FileReaders/SettingsReader.h"
#include "Bodies/CelestialBody.h"

namespace Singularity
{
	class StarchartObject final : public Altair::Spriteable, public Altair::Serializable
	{
	protected:
		std::string m_name;
		int m_x;
		int m_y;
		std::vector<CelestialBody*> m_parents;
		std::vector<CelestialBody*> m_children;
		std::vector<Entity*> m_entities;
	public:
		StarchartObject();
		StarchartObject(int x, int y, std::string name);
		StarchartObject(Altair::SettingsReader file);
		virtual ~StarchartObject();
		StarchartObject(const StarchartObject&) = default;
		StarchartObject(StarchartObject&&) = default;
		StarchartObject& operator =(const StarchartObject&) = default;
		StarchartObject& operator =(StarchartObject&&) = default;

		int get_x() const;
		int get_y() const;
		std::string get_name() const;

		void add_parent(CelestialBody* parent);
		CelestialBody* get_parent();

		void add_child(CelestialBody* child);
		std::vector<CelestialBody*> get_children() const;

		Altair::Sprite to_sprite(int x, int y) override;
		std::string serialize() override;
		void update();
	};
}
#endif // !__STARCHART_BODY
