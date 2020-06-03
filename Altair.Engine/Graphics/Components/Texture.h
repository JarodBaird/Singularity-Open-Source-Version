#ifndef __TEXTURE_H
#define __TEXTURE_H
#include <string>

namespace Altair
{
	class Texture
	{
	private:
		std::string m_file_name;
		GLuint m_texture_id;
		GLsizei m_width, m_height;
	public:
		Texture();
		void bind() const;
		static void unbind();

		uint32_t get_width() const;
		uint32_t get_height() const;
	};
}
#endif // !__TEXTURE_H
