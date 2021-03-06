#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#ifndef __WIN32
#include <windows.h>
#endif

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#if defined(_MSC_VER)
#define _USE_MATH_DEFINES
#endif

#include "linmath.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


#ifdef DEBUG
#  define GL(line) do {                      \
       line;                                 \
       assert(glGetError() == GL_NO_ERROR);  \
   } while(0)
#else
#  define GL(line) line
#endif

GLuint vertex_buffer, vertex_shader, fragment_shader, program;
GLint mvp_location, vpos_location;

static const vec2 vertices[4] =
{
	{ -0.6f, -0.6f },
	{  0.6f, -0.6f },
	{  0.6f,  0.6f },
	{ -0.6f,  0.6f }
};


static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec2 vPos;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(1.0);\n"
"}\n";


double gFrameCount=0;
void showFPS(double *gStartTimeFPS) {
	double currentTime=glfwGetTime();
	gFrameCount++;
	if(currentTime- *gStartTimeFPS>=1.0) {
		printf("%g FPS\n",gFrameCount );
		gFrameCount=0;
		double current = glfwGetTime();
		*gStartTimeFPS = current;
	}
}
void init() {

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GL(vertex_shader = glCreateShader(GL_VERTEX_SHADER));
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	GL(fragment_shader = glCreateShader(GL_FRAGMENT_SHADER));
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	GL(program = glCreateProgram());
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	GL(glLinkProgram(program));

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
			sizeof(vertices[0]), (void*) 0);
}

static void error_callback(int error, const char* description)
{
	printf("%s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

#ifndef __WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpszCmdLine, int nShowCmd)
#else
int main(int argc, char const *argv[])
#endif
{
	GLFWwindow* window;

	GLFWrect rects[8] =
	{{ 0,  0, 400,  400}
	};

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);


	
	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
	//glfwWindowHint( GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API );
	//glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(800, 400, "Window Title", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize OpenglES2 context\n");
		return -1;
	}

	double gStartTimeFPS=glfwGetTime();

	if (glfwExtensionSupported("GLX_EXT_create_context_es2_profile"))
	{
		printf("GLX_EXT_create_context_es2_profile Supported\n");
	}

	printf("%s\n",glGetString(GL_VERSION));
	glfwSetKeyCallback(window, key_callback);
	init();



	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		int buffer_age;

		mat4x4 m, p, mvp;

		const double angle = glfwGetTime() * M_PI / 180.0;

		glfwGetFramebufferSize(window, &width, &height);

		buffer_age = glfwGetBufferAge(window);


		ratio = width / (float) height;

		ratio = width / (float) height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.4,0.4,1.0,1.0);

		glUseProgram(program);

		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 0.f, 1.f);

		mat4x4_translate(m, 0.f, 0.f, 0.f);
		mat4x4_rotate_Z(m, m, (float) angle);
		mat4x4_mul(mvp, p, m);

		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
		glDisable(GL_MULTISAMPLE);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		showFPS(&gStartTimeFPS);

		if (buffer_age > 0)
			glfwSwapBuffersWithDamage(window, rects, 1);
		else
			glfwSwapBuffers(window);


		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

