#include "MusicPlayer.h"

#include "../FileSystem/DirectoryIterator.h"

namespace Altair
{
	MusicPlayer::MusicPlayer()
	{
		const std::string music_directory = "GameData\\Assets\\Music";
		const DirectoryIterator directory_iterator(music_directory);
		std::vector<std::string> files = directory_iterator.get_files();

		if (!files.empty()) { m_song.openFromFile(music_directory + "\\" + files.front()); }
	}

	void MusicPlayer::play() { m_song.play(); }

	void MusicPlayer::set_volume(int32_t volume) { set_volume(static_cast<float>(volume)); }

	void MusicPlayer::set_volume(float volume) { m_song.setVolume(volume); }
}
