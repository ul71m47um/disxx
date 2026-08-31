module;

#ifdef __APPLE__
#	include <GLUT/glut.h>
#	include <OpenGL/gl3.h>
#else
#	define GL_GLEXT_PROTOTYPES
#	include <GL/freeglut.h>
#	include <GL/glext.h>
#	include <GL/gl.h>
#endif

#include <cstddef> // For offsetof

module disxx.ui.backend.GLRenderer;

import disxx.ui.renderable.Rectangle;
import disxx.ui.renderable.Triangle;
import disxx.ui.renderable.Shape;
import disxx.ui.renderable.Text;
import disxx.ui.utility.Vertex;
import disxx.ui.utility.Vec;

import std;

namespace disxx::ui::backend
{
	GLRenderer::GLRenderer(void) noexcept
		: m_Buffer{}
		, m_Vao{}
		, m_Vbo{}
		, m_VertexShader{}
		, m_FragmentShader{}
		, m_Program{}
	{
		glGenVertexArrays(1, &this->m_Vao);
		glBindVertexArray(this->m_Vao);

		glGenBuffers(1, &this->m_Vbo);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_Vbo);
		glBufferData(GL_ARRAY_BUFFER, 1024 * 1024, nullptr, GL_DYNAMIC_DRAW);
		// For positions
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(utility::Vertex<GLfloat>), std::bit_cast<GLvoid *>(offsetof(utility::Vertex<GLfloat>, position)));
		glEnableVertexAttribArray(0);
		// For colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(utility::Vertex<GLfloat>), std::bit_cast<GLvoid *>(offsetof(utility::Vertex<GLfloat>, color)));
		glEnableVertexAttribArray(1);

		this->m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(this->m_VertexShader, 1, &s_pVertexSource, nullptr);
		glCompileShader(this->m_VertexShader);
		
		this->m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(this->m_FragmentShader, 1, &s_pFragmentSource, nullptr);
		glCompileShader(this->m_FragmentShader);

		this->m_Program = glCreateProgram();
		glAttachShader(this->m_Program, this->m_VertexShader);
		glAttachShader(this->m_Program, this->m_FragmentShader);
		glBindAttribLocation(this->m_Program, 0, "position");
		glBindAttribLocation(this->m_Program, 1, "incolor");
		glLinkProgram(this->m_Program);
		glUseProgram(this->m_Program);
	}

	GLRenderer::~GLRenderer(void) noexcept
	{
		glDeleteVertexArrays(1, &this->m_Vao);
		glDeleteBuffers(1, &this->m_Vbo);
		glDeleteShader(this->m_VertexShader);
		glDeleteShader(this->m_FragmentShader);
		glDeleteProgram(this->m_Program);
	}

	void GLRenderer::Push(std::unique_ptr<renderable::Renderable> &&ptr) noexcept
	{
		if (this->m_Buffer.size() < 1024 * 1024) [[likely]]
			this->m_Buffer.emplace_back(std::forward<std::unique_ptr<renderable::Renderable> &&>(ptr));
	}

	void GLRenderer::Pop(void) noexcept
	{
		if (this->m_Buffer.size() > 0) [[likely]]
			this->m_Buffer.pop_back();
	}

	void GLRenderer::ClearBuffer(void) noexcept
	{
		if (this->m_Buffer.size() > 0) [[likely]]
			this->m_Buffer.clear();
	}

	void GLRenderer::Render(void) noexcept
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Get actual window size and set up a projection
		GLfloat projection[] = {
			2.f / glutGet(GLUT_WINDOW_WIDTH), 0.f, 0.f, 0.f,
			0.f, 2.f / glutGet(GLUT_WINDOW_HEIGHT), 0.f, 0.f,
			0.f, 0.f, -1.f, 0.f,
			-1.f, -1.f, 0.f, 1.f
		};

		glUseProgram(this->m_Program);
		GLint loc{glGetUniformLocation(this->m_Program, "projection")};
		glUniformMatrix4fv(loc, 1, GL_FALSE, projection);

		std::vector<utility::Vertex<GLfloat>> vertices{};
		for (const auto &ptr : this->m_Buffer)
		{
			if (dynamic_cast<renderable::Text *>(ptr.get()))
			{
				if (!vertices.empty())
            	{
            	    glBindVertexArray(this->m_Vao);
            	    glBindBuffer(GL_ARRAY_BUFFER, this->m_Vbo);
            	    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(utility::Vertex<GLfloat>), vertices.data());
            	    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLuint>(vertices.size()));
            	    vertices.clear();
            	}
				glUseProgram(0);

				const auto [r, g, b]{ptr->GetColor()};
				const auto [x, y]{ptr->GetPosition()};

				// Using an old OpenGL with GLUT is the simplest way to render a text
				glColor3f(r, g, b);
				glWindowPos2f(x, y);
				for (const auto ch : dynamic_cast<renderable::Text &>(*ptr).GetText())
					glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ch);
				continue;
			}

			glUseProgram(this->m_Program);	
			for (const auto &vertex : ptr->GetVertices())
				vertices.push_back(vertex);
		}

		if (!vertices.empty())
		{
			glBindVertexArray(this->m_Vao);
			glBindBuffer(GL_ARRAY_BUFFER, this->m_Vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(utility::Vertex<GLfloat>), vertices.data());
			glUseProgram(this->m_Program);
			glDrawArrays(GL_TRIANGLES, 0, vertices.size() & std::numeric_limits<GLuint>::max());
			glUseProgram(0);
		}
	}
} /* disxx::ui::backend */
