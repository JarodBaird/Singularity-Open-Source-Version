#ifndef __MUSIC_PLAYER_H
#define __MUSIC_PLAYER_H

#include <SFML/Audio.hpp>

namespace Altair
{
	class MusicPlayer
	{
	private:
		sf::Music m_song;
	public:
		MusicPlayer();
		void play();
		void set_volume(int32_t volume);
		void set_volume(float volume);
	};
}
#endif // !__MUSIC_PLAYER_H
