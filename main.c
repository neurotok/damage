#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>

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
}
void update() {
}
void render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.4,0.4,1.0,1.0);
}
void mainLoop() {
	update();
	render();
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
int main(void)
{
	GLFWwindow* window;

	GLFWrect rects[8] =
	{{ 250,  25, 350,  90},
		{ 250, 285, 350,  90},
		{ 250, 115,  90, 170},
		{285, 115,  90, 170},

		{425,  25, 350,  90},
		{425, 285, 350,  90},
		{425, 115,  90, 170},
		{685, 115,  90, 170},
	};


	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 2 );

	window = glfwCreateWindow(800, 400, "Window Title", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);


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

		glfwGetFramebufferSize(window, &width, &height);

		buffer_age = glfwGetBufferAge(window);

		ratio = width / (float) height;
		glViewport(0, 0, width, height);

		mainLoop();
		showFPS(&gStartTimeFPS);

		if (buffer_age > 0)
			glfwSwapBuffersWithDamage(window, rects, 8);
		else
			glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

