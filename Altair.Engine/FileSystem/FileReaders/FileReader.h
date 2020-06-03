#ifndef __FILE_READER_H
#define __FILE_READER_H

#include <string>

namespace Altair
{
	class Serializable
	{
	private:
		std::string m_serialized;
	protected:
		void begin_file();
		void begin_child(std::string child_type);
		void add_to_file(std::string key, std::string value);
		void add_to_file(std::string key, bool value);
		void add_to_file(std::string key, uint8_t value);
		void add_to_file(std::string key, int8_t value);
		void add_to_file(std::string key, uint16_t value);
		void add_to_file(std::string key, int16_t value);
		void add_to_file(std::string key, uint32_t value);
		void add_to_file(std::string key, int32_t value);
		void add_to_file(std::string key, uint64_t value);
		void add_to_file(std::string key, int64_t value);
		void add_to_file(std::string key, float value);
		void add_to_file(std::string key, double value);
		void end_child();
		[[nodiscard]] std::string end_file() const;

	public:
		Serializable() = default;
		virtual ~Serializable() = default;
		Serializable(const Serializable&) = default;
		Serializable(Serializable&&) = default;
		Serializable& operator =(const Serializable&) = default;
		Serializable& operator =(Serializable&&) = default;
		virtual std::string serialize() = 0;
	};

	class FileReader
	{
	protected:
		std::string m_full_file_name;
		FileReader() = default;
	public:
		FileReader(std::string file_name, std::string directory);
		virtual ~FileReader() = default;
		FileReader(const FileReader&) = default;
		FileReader(FileReader&&) = default;
		FileReader& operator =(const FileReader&) = default;
		FileReader& operator =(FileReader&&) = default;
		[[nodiscard]] std::string read_from_file() const;
		[[nodiscard]] std::string read_from_file(const std::string& file_name) const;
	};
}
#endif // !__FILE_READER_H
