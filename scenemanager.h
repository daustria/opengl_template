#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "shader.h"

void framebuffer_size_callback(GLFWwindow *, int width, int height);
// Should probably make a singleton, since I plan to declare this as a global variable.
// But whatever
class SceneManager
{
	friend void framebuffer_size_callback(GLFWwindow *, int width, int height);
public:
	// Window affairs
	void initialize();
	void start_window();
	void process_input();

	// Actual objects for whatever project or tutorial we are doing. Should probably change depending on
	// whatever we are doing.
	void init_some_object();

private:
	// Window affairs
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;
	GLFWwindow *window = nullptr;

	// Project specific stuff	


};

#endif // SCENE_MANAGER_H
