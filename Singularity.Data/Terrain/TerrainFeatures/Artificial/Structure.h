#ifndef __STRUCTURE_H
#define __STRUCTURE_H
#include "../TerrainFeature.h"
#include "../../../Civilization/Civilization.h"

namespace Singularity
{
	class Structure : public TerrainFeature
	{
	protected:
		Civilization* m_owner;
		double m_build_progress;
		bool is_built() const;
	public:
		Structure(CelestialBody* parent_body, Civilization* owner);
		virtual ~Structure() = default;
		Structure(const Structure&) = default;
		Structure(Structure&&) = default;
		Structure& operator =(const Structure&) = delete;
		Structure& operator =(Structure&&) = default;
		Altair::Color get_color() override;
		unsigned char get_sprite() override;
	};
}
#endif // !__STRUCTURE_H
