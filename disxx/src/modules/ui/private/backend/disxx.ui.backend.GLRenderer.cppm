module;

#ifdef __APPLE__
#	include <OpenGL/gl3.h>
#else
#	include <GL/gl.h>
#endif

#include <cstdint>
#include <vector>

export module disxx.ui.backend.GLRenderer;

import disxx.ui.backend.IRenderer;

export namespace disxx::ui::backend
{
	class __attribute__((visibility("default"))) [[nodiscard]] GLRenderer final : public IRenderer
	{
	  private:
		static constexpr const char *s_pVertexSource = "#version 120\n"
			"uniform mat4 projection;\n"
			"attribute vec2 position;\n"
			"attribute vec3 incolor;\n"
			"varying vec4 color;\n"
			"void main()\n"
			"{\n"
			"\tgl_Position = projection * vec4(position, 1.f, 1.f);\n"
			"\tcolor = vec4(incolor, 1.f);"
			"}\n";
		
		static constexpr const char *s_pFragmentSource = "#version 120\n"
			"varying vec4 color;\n"
			"void main()\n"
			"{\n"
			"\tgl_FragColor = color;\n"
			"}\n";

	  private:
		std::vector<std::unique_ptr<renderable::Renderable>> m_Buffer{};
		GLuint m_Vao{};
		GLuint m_Vbo{};
		GLuint m_VertexShader{};
		GLuint m_FragmentShader{};
		GLuint m_Program{};

	  public:
		explicit GLRenderer(void) noexcept;

		~GLRenderer(void) noexcept;

		explicit GLRenderer(const GLRenderer &) noexcept = delete;
		GLRenderer &operator=(const GLRenderer &) noexcept = delete;

		explicit GLRenderer(GLRenderer &&) noexcept = delete;
		GLRenderer &operator=(GLRenderer &&) noexcept = delete;

		virtual void Push(std::unique_ptr<renderable::Renderable> &&) noexcept override;
		virtual void Pop(void) noexcept override;
		
		virtual void ClearBuffer(void) noexcept override;
		virtual void Render(void) noexcept override;
	};
} /* disxx::ui::backend */
