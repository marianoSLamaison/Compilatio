#include "main.h"

//A callback is the way to report events here in GLFW, this are functions
//that recieve data to descrive the event and are called when it happens
//This one is for the event of an error ocurring
void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(int argc, char** argv)
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		//initialization failed
	}
	
	GLFWwindow* window = glfwCreateWindow(400, 400, "Compilatio", NULL, NULL);
	if (!window)
	{
		//The window was not created
	}
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	glfwSetKeyCallback(window, key_callback);

	int widt, height;
	glfwGetFramebufferSize(window, &widt, &height);
	//as with most events you can set a callback to notify when the size has changed
	glViewport(0, 0, widt, height);
	//here whe are keeping the program running with this. But 
	//once whe have a game loop, you should set this on a call back and place the game loop
	//here
	glfwSwapInterval(1);	
	//so this is to explain how fast the swaping, may ocurr, if it were 0 
	//whe will have screen tearing so that is unacceptable, instead whe set it to 1
	//witch is the standard for this

	while (!glfwWindowShouldClose(window))
	{
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

