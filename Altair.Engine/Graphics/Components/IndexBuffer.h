#ifndef __INDEX_BUFFER_H
#define __INDEX_BUFFER_H

#include <GL/glew.h>

namespace Altair
{
	class IndexBuffer
	{
	private:
		GLuint m_buffer_id;
		GLuint m_count;
	public:
		IndexBuffer(GLushort* data, GLsizei count);
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();
		IndexBuffer(const IndexBuffer&) = default;
		IndexBuffer(IndexBuffer&&) = default;
		IndexBuffer& operator =(const IndexBuffer&) = default;
		IndexBuffer& operator =(IndexBuffer&&) = default;
		void bind() const;
		static void unbind();
	};
}
#endif // !__INDEX_BUFFER_H
