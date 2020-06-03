#ifndef __SETTINGS_FILE_READER_H
#define __SETTINGS_FILE_READER_H
#include "FileReader.h"
#include "../Tags.h"
#include <unordered_map>

namespace Altair
{
	class SettingsReader final : public FileReader
	{
	private:
		std::unordered_map<std::string, std::string> m_settings;
		std::vector<SettingsReader> m_subsettings;
		uint32_t m_final_position;
		std::string m_file_name;
		std::string m_directory;
		Tags m_tags;

		template <typename T>
		T to_int(const std::string& setting, T max);

	public:
		SettingsReader(const std::string& file_contents, uint32_t start_position);
		SettingsReader(const std::string& file_name, const std::string& directory = "GameData\\Settings",
		               bool use_default = true,
		               uint32_t start_position = 0);
		void parse_to_settings(std::string file_contents, uint32_t start_position);
		uint32_t get_final_position() const;
		std::string get(const std::string& key);
		uint16_t get_ushort(const std::string& key);
		int16_t get_short(const std::string& key);
		uint32_t get_uint(const std::string& key);
		int32_t get_int(const std::string& key);
		uint64_t get_ulong(const std::string& key);
		int64_t get_long(const std::string& key);
		double get_double(const std::string& key);
		bool get_bool(const std::string& key);
		std::vector<SettingsReader> get_sub_settings() const;
		std::string get_file_name() const;
		std::string get_directory() const;
		Tags get_tags() const;
	};
}
#endif // !__SETTINGS_FILE_READER_H
