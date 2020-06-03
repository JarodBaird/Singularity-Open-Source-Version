#include "Model.h"

namespace Singularity
{
	Model::Model()
	{
		seed = 0;
		calendar = new Calendar();
		player = nullptr;
		is_paused = true;
		game_type = GameType::None;
		word_bank = new Altair::WordBank();
	}

	Model::~Model()
	{
		delete calendar;

		delete word_bank;

		for (Compound* c : compounds) { delete c; }
		compounds.clear();

		for (Element* e : elements) { delete e; }
		elements.clear();

		for (Civilization* civ : aliens) { delete civ; }
		aliens.clear();

		for (Entity* f : entities) { delete f; }
		entities.clear();

		for (StarchartObject* obj : starchart) { delete obj; }
		starchart.clear();
	}

	void Model::reset()
	{
		galaxy_name = "";

		delete calendar;

		delete word_bank;

		for (Compound* c : compounds) { delete c; }
		compounds.clear();

		for (Element* e : elements) { delete e; }
		elements.clear();

		for (Civilization* civ : aliens) { delete civ; }
		aliens.clear();

		for (Entity* f : entities) { delete f; }
		entities.clear();

		for (StarchartObject* obj : starchart) { delete obj; }
		starchart.clear();
	}
}
