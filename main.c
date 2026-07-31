#include "main.h"

//A callback is the way to report events here in GLFW, this are functions
//that recieve data to descrive the event and are called when it happens
//This one is for the event of an error ocurring
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char** argv)
{
	float vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f
	};
	const char * vertexShaderSource = R"glsl(
	#version 150 core 
	in vec2 position;
	void main()
	{
		gl_Position = vec4(position, 0.0, 1.0);
	}
)glsl";
	const char * fragmentShaderSource = R"glsl(
	#version 150 core 
	out vec4 outColor;
	void main()
	{
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;

	GLuint vbo;//Vertex buffer object
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		return 1;
		//initialization failed
	}
	//To clarify whe are working with only core opengl
	//Allso it seems to crash if you do not clarify the versions suported
	//so remember to add them
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800,400, "Compilatio", NULL, NULL);


	if (!window)
	{
		return 1;
		//The window was not created
	}
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSetKeyCallback(window, key_callback);

	int widt, height;
	glfwGetFramebufferSize(window, &widt, &height);
	//as with most events you can set a callback to notify when the size has changed
	glViewport(0, 0, widt, height);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//to get ready the buffer to draw things to
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	GLint status= GL_TRUE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		return 1;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
		return 1;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);
	//here whe are keeping the program running with this. But 
	//once whe have a game loop, you should set this on a call back and place the game loop
	//here
	glfwSwapInterval(1);	
	//so this is to explain how fast the swaping, may ocurr, if it were 0 
	//whe will have screen tearing so that is unacceptable, instead whe set it to 1
	//witch is the standard for this

	while (!glfwWindowShouldClose(window))
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//do some stuff
		glfwSwapBuffers(window);
		//glfw works with double buffer witch means that whe render to 
		//buffer A but the one being displayed is buffer B
		//This is done to just display complete images
		

		glfwPollEvents();
		//checks if an event has arrived and then it process it acordingly
		//it does not block the thread as WaitEvents does. 
	}
	

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

