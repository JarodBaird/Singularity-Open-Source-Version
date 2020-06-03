#ifndef __SHADER_H
#define __SHADER_H

namespace Altair
{
	class Shader
	{
	private:
		GLuint m_shader_id;
	public:
		Shader();
		~Shader();
		Shader(const Shader&) = default;
		Shader(Shader&&) = default;
		Shader& operator =(const Shader&) = default;
		Shader& operator =(Shader&&) = default;
		void enable() const;
		static void disable();
	};
}
#endif // !__SHADER_H
