#include "FileReader.h"

#include <fstream>

namespace Altair
{
	void Serializable::begin_file() { m_serialized = ""; }

	void Serializable::begin_child(std::string child_type)
	{
		m_serialized += "[BEGIN]\n";
		add_to_file("Type", std::move(child_type));
	}

	void Serializable::add_to_file(std::string key, std::string value)
	{
		m_serialized += "[" + std::move(key) + "=" + std::move(value) + "]\n";
	}

	void Serializable::add_to_file(std::string key, bool value)
	{
		const std::string parsed_value = value ? "true" : "false";
		add_to_file(std::move(key), parsed_value);
	}

	void Serializable::add_to_file(std::string key, uint8_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, int8_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, uint16_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, int16_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, uint32_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, int32_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, uint64_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, int64_t value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::add_to_file(std::string key, float value) { add_to_file(std::move(key), std::to_string(value)); }

	void Serializable::add_to_file(std::string key, double value)
	{
		add_to_file(std::move(key), std::to_string(value));
	}

	void Serializable::end_child() { m_serialized += "[END]\n"; }

	std::string Serializable::end_file() const { return m_serialized; }

	FileReader::FileReader(std::string file_name, std::string directory)
	{
		m_full_file_name = std::move(directory) + "\\" + std::move(file_name);
	}

	std::string FileReader::read_from_file() const { return read_from_file(m_full_file_name); }

	std::string FileReader::read_from_file(const std::string& file_name) const
	{
		std::string contents;

		std::fstream fstream = std::fstream(file_name);
		if (fstream.is_open())
		{
			std::string line;
			while (std::getline(fstream, line))
			{
				contents += line;
				contents += "\n";
			}
		}
		fstream.close();

		return contents;
	}
}
