#include "DirectoryIterator.h"

#include <filesystem>

namespace Altair
{
	DirectoryIterator::DirectoryIterator(const std::string& parent_directory)
	{
		try
		{
			for (const std::filesystem::directory_entry& p : std::filesystem::directory_iterator(parent_directory))
			{
				if (p.is_directory()) { m_subdirectories.emplace_back(p.path().filename().string()); }
				else if (p.is_regular_file()) { m_files.emplace_back(p.path().filename().string()); }
			}
		}
		catch (std::filesystem::filesystem_error&) {}
	}

	size_t DirectoryIterator::get_subdirectory_count() const { return static_cast<uint32_t>(m_subdirectories.size()); }

	size_t DirectoryIterator::get_file_count() const { return static_cast<uint32_t>(m_files.size()); }

	std::vector<std::string> DirectoryIterator::get_subdirectories() const { return m_subdirectories; }

	std::vector<std::string> DirectoryIterator::get_files() const { return m_files; }
}
