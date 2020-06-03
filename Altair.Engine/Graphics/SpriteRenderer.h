#ifndef __SPRITE_RENDERER_H
#define __SPRITE_RENDERER_H
#include <GL/glew.h>

#include "TextItem.h"
#include "Sprite.h"
#include "../FileSystem/ImageReaders/ImageReader.h"
#include "Components/IndexBuffer.h"

namespace Altair
{
	struct VertexData
	{
		struct
		{
			GLfloat v1;
			GLfloat v2;
			GLfloat v3;
		} position;

		GLfloat sprite_sheet_x;
		GLfloat sprite_sheet_y;
		uint32_t color;
		uint32_t bg_color;
	};

	class SpriteRenderer
	{
	private:
		uint32_t m_max_x, m_max_y;
		GLfloat m_sprite_width, m_sprite_height;
		GLfloat m_display_width, m_display_height;
		uint32_t m_tile_size;
		uint32_t m_screen_width, m_screen_height;
		uint8_t m_vertex_source[1024]{};
		uint8_t m_fragment_source[1024]{};
		ImageReader m_resource_manager;
		GLuint m_vao{}, m_vbo{}; // The IDs of the vertex objects.
		std::unique_ptr<IndexBuffer> m_ibo;
		sf::Image m_sprite_sheet;
		sf::Vector2u m_image_size;

		GLsizei m_index_count;

		VertexData* m_buffer;

		static void set_buffer(VertexData* buffer, uint32_t color, GLfloat v1, GLfloat v2, GLfloat sprite_x,
		                       GLfloat sprite_y, uint32_t bg_color);
	public:
		SpriteRenderer(uint32_t max_x, uint32_t max_y, uint32_t sprite_width, uint32_t sprite_height,
		               uint32_t tile_size, uint32_t screen_width, uint32_t screen_height);
		~SpriteRenderer();
		SpriteRenderer(const SpriteRenderer&) = delete;
		SpriteRenderer(SpriteRenderer&&) = default;
		SpriteRenderer& operator =(const SpriteRenderer&) = delete;
		SpriteRenderer& operator =(SpriteRenderer&&) = default;
		void begin();
		static void end();
		static void clear_screen();
		void render(Sprite& sprite);
		void render(TextItem& text);
		void push(Sprite& sprite);
		void draw();
	};
}
#endif // !__SPRITE_RENDERER_H
