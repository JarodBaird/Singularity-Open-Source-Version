#include <cstddef>

#include "../FileSystem/FileReaders/FileReader.h"
#include "SpriteRenderer.h"
#include "Sprite.h"
#include "Components/Shader.h"
#include "Components/Texture.h"

namespace Altair
{
	constexpr int32_t RendererMaxSprites = 60000;
	constexpr int32_t RendererVertexSize = sizeof(VertexData);
	constexpr int32_t RendererSpriteSize = RendererVertexSize * 4;
	constexpr int32_t RendererBufferSize = RendererSpriteSize * RendererMaxSprites;
	constexpr int32_t RendererIndicesSize = RendererMaxSprites * 6;

	constexpr int32_t ShaderVertexIndex = 0;
	constexpr int32_t ShaderUvIndex = 1;
	constexpr int32_t ShaderColorIndex = 2;
	constexpr int32_t ShaderBgcolorIndex = 3;

	SpriteRenderer::SpriteRenderer(uint32_t max_x, uint32_t max_y, uint32_t sprite_width, uint32_t sprite_height,
	                               uint32_t tile_size,
	                               uint32_t screen_width, uint32_t screen_height)
	{
		m_buffer = nullptr;

		Shader shader;
		shader.enable();

		m_max_x = max_x;
		m_max_y = max_y;
		m_tile_size = tile_size;
		m_screen_width = screen_width;
		m_screen_height = screen_height;

		FileReader vertex = FileReader("Vertex.vert", "GameData\\Assets\\Shaders");
		std::string vertex_string = vertex.read_from_file();
		const char* v = vertex_string.c_str();
		for (uint32_t i = 0; i < vertex_string.size(); i++) { m_vertex_source[i] = v[i]; }

		FileReader fragment = FileReader("Fragment.frag", "GameData\\Assets\\Shaders");
		std::string fragment_string = fragment.read_from_file();
		const char* f = fragment_string.c_str();
		for (uint32_t i = 0; i < fragment_string.size(); i++) { m_fragment_source[i] = f[i]; }

		glActiveTexture(GL_TEXTURE0);
		Texture texture = Texture();
		texture.bind();

		shader.enable();

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, RendererBufferSize, nullptr, GL_DYNAMIC_DRAW);

		// Specify the layout of the vertex data.
		glEnableVertexAttribArray(ShaderVertexIndex);
		glEnableVertexAttribArray(ShaderUvIndex);
		glEnableVertexAttribArray(ShaderColorIndex);
		glEnableVertexAttribArray(ShaderBgcolorIndex);

		glVertexAttribPointer(ShaderVertexIndex, 3, GL_FLOAT, GL_FALSE, RendererVertexSize,
		                      static_cast<const GLvoid*>(nullptr));
		glVertexAttribPointer(ShaderUvIndex, 2, GL_FLOAT, GL_FALSE, RendererVertexSize,
		                      reinterpret_cast<const GLvoid*>(offsetof(VertexData, VertexData::sprite_sheet_x)));
		glVertexAttribPointer(ShaderColorIndex, 4, GL_UNSIGNED_BYTE, GL_TRUE, RendererVertexSize,
		                      reinterpret_cast<const GLvoid*>(offsetof(VertexData, VertexData::color)));
		glVertexAttribPointer(ShaderBgcolorIndex, 4, GL_UNSIGNED_BYTE, GL_TRUE, RendererVertexSize,
		                      reinterpret_cast<const GLvoid*>(offsetof(VertexData, VertexData::bg_color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RendererIndicesSize];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < RendererIndicesSize; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_ibo = std::make_unique<IndexBuffer>(indices, RendererIndicesSize);

		glBindVertexArray(0);

		m_sprite_width = static_cast<GLfloat>(sprite_width) / texture.get_width();
		m_sprite_height = static_cast<GLfloat>(sprite_height) / texture.get_height();
		m_display_width = static_cast<GLfloat>(m_tile_size) / static_cast<GLfloat>(m_screen_width) * GLfloat(2.0);
		m_display_height = static_cast<GLfloat>(m_tile_size) / static_cast<GLfloat>(m_screen_height) * GLfloat(2.0);

		m_index_count = 0;
	}

	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteBuffers(1, &m_vbo);
	}

	void SpriteRenderer::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		m_buffer = static_cast<VertexData*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void SpriteRenderer::end()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteRenderer::clear_screen() { glClear(GL_COLOR_BUFFER_BIT); }

	void SpriteRenderer::render(Sprite& sprite)
	{
		const int64_t x = sprite.get_x();
		const int64_t y = sprite.get_y();

		if (y >= 0 && y <= m_max_y) { if (x >= 0 && x <= m_max_x) { push(sprite); } }
	}

	void SpriteRenderer::render(TextItem& text)
	{
		std::string t = text.get_display_text();

		const int base_x = text.get_x();

		int32_t current_x = base_x;
		int32_t current_y = text.get_y();

		for (size_t i = 0; i < t.size(); i++)
		{
			const char c = t.at(i);

			Sprite sprite = Sprite(current_x, current_y, c, text.get_color(i));
			push(sprite);

			current_x++;
			if (static_cast<uint64_t>(current_x) > m_max_x - 1)
			{
				current_x = base_x;
				current_y++;
			}
		}
	}

	void SpriteRenderer::push(Sprite& sprite)
	{
		const int32_t x = sprite.get_x();
		const int32_t y = sprite.get_y();

		const GLfloat sprite_x = m_display_width * x - 1.0f;
		const GLfloat sprite_x2 = sprite_x + m_display_width;
		const GLfloat sprite_y = 1.0f - m_display_height * y;
		const GLfloat sprite_y2 = sprite_y - m_display_height;

		const uint32_t c = sprite.get_color().to_int();
		const uint32_t bg_color = sprite.get_background_color().to_int();

		const GLfloat coords_x = sprite.get_sprite_x() * m_sprite_width;
		const GLfloat coords_x2 = coords_x + m_sprite_width;
		const GLfloat coords_y = sprite.get_sprite_y() * m_sprite_height;
		const GLfloat coords_y2 = coords_y + m_sprite_height;

		m_buffer->color = c;
		m_buffer->position.v1 = sprite_x;
		m_buffer->position.v2 = sprite_y;
		m_buffer->position.v3 = 0;
		m_buffer->sprite_sheet_x = coords_x;
		m_buffer->sprite_sheet_y = coords_y;
		m_buffer->bg_color = bg_color;

		set_buffer(m_buffer, c, sprite_x, sprite_y, coords_x, coords_y, bg_color);
		m_buffer++;

		set_buffer(m_buffer, c, sprite_x, sprite_y2, coords_x, coords_y2, bg_color);
		m_buffer++;

		set_buffer(m_buffer, c, sprite_x2, sprite_y2, coords_x2, coords_y2, bg_color);
		m_buffer++;

		set_buffer(m_buffer, c, sprite_x2, sprite_y, coords_x2, coords_y, bg_color);
		m_buffer++;

		m_index_count += 6;
	}

	void SpriteRenderer::set_buffer(VertexData* buffer, uint32_t color, GLfloat v1, GLfloat v2, GLfloat sprite_x,
	                                GLfloat sprite_y, uint32_t bg_color)
	{
		buffer->color = color;
		buffer->position.v1 = v1;
		buffer->position.v2 = v2;
		buffer->position.v3 = 0;
		buffer->sprite_sheet_x = sprite_x;
		buffer->sprite_sheet_y = sprite_y;
		buffer->bg_color = bg_color;
	}

	void SpriteRenderer::draw()
	{
		glBindVertexArray(m_vao);
		m_ibo->bind();

		glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);

		m_ibo->unbind();
		glBindVertexArray(0);

		m_index_count = 0;
	}
}
