#include <iostream>

#include "SettingsReader.h"

namespace Altair
{
	SettingsReader::SettingsReader(const std::string& file_contents, uint32_t start_position)
	{
		m_final_position = 0;
		parse_to_settings(file_contents, start_position);
	}

	SettingsReader::SettingsReader(const std::string& file_name, const std::string& directory, bool use_default,
	                               uint32_t start_position) : FileReader(file_name, directory)
	{
		m_file_name = file_name;
		m_final_position = 0;
		m_directory = directory;

		std::string default_file;
		if (!directory.empty()) { default_file = directory + "\\Defaults\\" + file_name; }
		else { default_file = "Defaults\\" + file_name; }

		std::string file;
		if (!directory.empty()) { file = directory + "\\" + file_name; }
		else { file = file_name; }

		if (use_default) { parse_to_settings(read_from_file(default_file), start_position); }
		parse_to_settings(read_from_file(file), start_position);
	}

	void SettingsReader::parse_to_settings(std::string file_contents, uint32_t start_position)
	{
		enum class ParseState
		{
			Begin,
			StartFound,
			EqualsFound
		};

		ParseState state = ParseState::Begin;

		uint32_t start = 0;
		uint32_t equals = 0;

		for (uint32_t i = start_position; i < file_contents.size(); i++)
		{
			const uint8_t c = file_contents.at(i);
			if (c == '[' && state == ParseState::Begin)
			{
				start = i + 1;
				state = ParseState::StartFound;
			}

			if (c == '=' && state == ParseState::StartFound)
			{
				equals = i;
				state = ParseState::EqualsFound;
			}

			if (c == ']')
			{
				const uint32_t end = i;

				if (state == ParseState::StartFound)
				{
					// If there was not an equals.
					std::string value = file_contents.substr(start, end - start);
					if (value == "BEGIN")
					{
						SettingsReader f(file_contents, end + 1);
						m_subsettings.push_back(f);
						i = f.get_final_position();
					}
					else if (value == "END")
					{
						m_final_position = i;
						return;
					}
					else { m_tags.add_tag(value); }
				}
				else
				{
					std::string key = file_contents.substr(start, equals - start);
					const std::string value = file_contents.substr(equals + 1, end - equals - 1);
					m_settings[key] = value;
				}

				state = ParseState::Begin;
			}
		}
	}

	uint32_t SettingsReader::get_final_position() const { return m_final_position; }

	std::string SettingsReader::get(const std::string& key) { return m_settings[key]; }

	template <typename T>
	T SettingsReader::to_int(const std::string& setting, T max)
	{
		T ret_val;
		try { ret_val = static_cast<T>(std::stoll(setting)); }
		catch (std::invalid_argument&) { ret_val = 0; }
		catch (std::out_of_range&) { ret_val = max; }
		return ret_val;
	}

	uint16_t SettingsReader::get_ushort(const std::string& key) { return to_int<uint16_t>(m_settings[key], USHRT_MAX); }

	int16_t SettingsReader::get_short(const std::string& key) { return to_int<int16_t>(m_settings[key], SHRT_MAX); }

	uint32_t SettingsReader::get_uint(const std::string& key) { return to_int<uint32_t>(m_settings[key], UINT_MAX); }

	int32_t SettingsReader::get_int(const std::string& key) { return to_int<int32_t>(m_settings[key], INT_MAX); }

	uint64_t SettingsReader::get_ulong(const std::string& key) { return to_int<uint64_t>(m_settings[key], ULONG_MAX); }

	int64_t SettingsReader::get_long(const std::string& key) { return to_int<int64_t>(m_settings[key], LONG_MAX); }

	double SettingsReader::get_double(const std::string& key)
	{
		double ret_val;
		try { ret_val = std::stod(m_settings[key]); }
		catch (std::invalid_argument&) { ret_val = 0; }
		catch (std::out_of_range&) { ret_val = DBL_MAX; }
		return ret_val;
	}

	bool SettingsReader::get_bool(const std::string& key)
	{
		const uint8_t c = m_settings[key][0];
		return c == 't' || c == 'T';
	}

	std::vector<SettingsReader> SettingsReader::get_sub_settings() const { return m_subsettings; }

	std::string SettingsReader::get_file_name() const { return m_file_name; }

	std::string SettingsReader::get_directory() const { return m_directory; }

	Tags SettingsReader::get_tags() const { return m_tags; }
}
