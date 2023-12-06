#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *, int width, int height);
// Should probably make a singleton, since I plan to declare this as a global variable.
// But whatever
class SceneManager
{
	friend void framebuffer_size_callback(GLFWwindow *, int width, int height);
public:
	void initialize();
	void start_window();
	void process_input();
private:
	unsigned int SCR_WIDTH = 800;
	unsigned int SCR_HEIGHT = 600;
	GLFWwindow *window = nullptr;
};

#endif // SCENE_MANAGER_H
