#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "shader.h"

// Should probably make a singleton, since I plan to declare this as a global variable.
// But whatever
class WindowManager
{
public:
	// Window affairs
	virtual void initialize() {}
	void start_window();

	virtual void process_input(float delta_time);

	// i mean for these guys to be called in the respective callback functions that we register to GLFW.
	// i dont think i can actually make these usable in the derived class this way, due to issues with 
	// the static keyword. but ill just leave it here anyway, cant hurt.
	virtual void mouse_event(double xPosIn, double yPosIn) {}
	virtual void scroll_callback(double xoffset, double yoffset) {}

	// Drawing stuff
	virtual void app_logic() {}
	virtual void draw() {}

protected:
	static unsigned int scr_width;
	static unsigned int scr_height;
	static GLFWwindow* window;
	static Camera* camera;

private:
	// Functions for processing input. We register these with GLFW.
	static void framebuffer_size_callback(GLFWwindow*, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void register_callbacks();
};

#endif // WINDOW_MANAGER_H