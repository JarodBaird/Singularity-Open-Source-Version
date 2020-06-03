#ifndef __MODEL_H
#define __MODEL_H
#include <vector>
#include <string>

#include "Physics/Calendar/Calendar.h"
#include "Entities/Entity.h"
#include "Civilization/Civilization.h"
#include "Physics/Chemistry/Element.h"
#include "Physics/Chemistry/Compound.h"
#include "Altair.Engine/WordSets/WordBank.h"
#include "Space/StarchartObject.h"

namespace Singularity
{
	enum class GameType
	{
		None = 0,
		Singularity = 1,
		Civilian = 2
	};

	struct Model
	{
	public:
		Model();
		~Model();
		Model(const Model&) = default;
		Model(Model&&) = default;
		Model& operator =(const Model&) = delete;
		Model& operator =(Model&&) = default;

		void reset();

		std::string galaxy_name;

		bool is_paused;

		int seed;

		GameType game_type;

		Altair::WordBank* word_bank;

		Calendar* calendar;

		std::vector<StarchartObject*> starchart;
		std::vector<Entity*> entities;

		std::vector<Element*> elements;
		std::vector<Compound*> compounds;

		Civilization* player;
		std::vector<Civilization*> aliens;
	};
}
#endif // !__MODEL_H
