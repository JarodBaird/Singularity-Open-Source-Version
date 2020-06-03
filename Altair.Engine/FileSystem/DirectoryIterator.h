#ifndef __DIRECTORY_ITERATOR_H
#define __DIRECTORY_ITERATOR_H
#include <vector>
#include <string>

namespace Altair
{
	class DirectoryIterator
	{
	private:
		std::vector<std::string> m_subdirectories;
		std::vector<std::string> m_files;
	public:
		DirectoryIterator(const std::string& parent_directory);
		size_t get_subdirectory_count() const;
		size_t get_file_count() const;
		std::vector<std::string> get_subdirectories() const;
		std::vector<std::string> get_files() const;
	};
}
#endif // !__DIRECTORY_ITERATOR_H
