#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "shader.h"

//void framebuffer_size_callback(GLFWwindow*, int width, int height);
// Should probably make a singleton, since I plan to declare this as a global variable.
// But whatever
class SceneManager
{
public:
	// Window affairs
	void initialize();
	void start_window();

private:

	// Window affairs
	void process_input(float delta_time);

	static unsigned int scr_width;
	static unsigned int scr_height;
	static GLFWwindow* window;
	static Camera* camera;

	// Functions for processing input. We register these with GLFW.
	static void framebuffer_size_callback(GLFWwindow*, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void register_callbacks();

	// update and draw the objects in our scene
	void app_logic();
	void draw();

	// Actual objects for whatever project or tutorial we are doing. This will change depending on
	// whatever we are doing.
	void init_cube();
	void init_light_cube();

	unsigned int cube_vertices = 36;
	unsigned int cube_vao = 0;
	unsigned int cube_vbo = 0;
	Shader* default_shader = nullptr;

	unsigned int light_vao = 0;
	unsigned int light_vbo = 0;
	Shader* light_shader = nullptr;
};

#define CUBE_VERTEX_DATA -0.5f, -0.5f, -0.5f,\
0.5f, -0.5f, -0.5f,\
0.5f, 0.5f, -0.5f,\
0.5f, 0.5f, -0.5f,\
-0.5f, 0.5f, -0.5f,\
-0.5f, -0.5f, -0.5f,\
-0.5f, -0.5f, 0.5f,\
0.5f, -0.5f, 0.5f,\
0.5f, 0.5f, 0.5f,\
0.5f, 0.5f, 0.5f,\
-0.5f, 0.5f, 0.5f,\
-0.5f, -0.5f, 0.5f,\
-0.5f, 0.5f, 0.5f,\
-0.5f, 0.5f, -0.5f,\
-0.5f, -0.5f, -0.5f,\
-0.5f, -0.5f, -0.5f,\
-0.5f, -0.5f, 0.5f,\
-0.5f, 0.5f, 0.5f,\
0.5f, 0.5f, 0.5f,\
0.5f, 0.5f, -0.5f,\
0.5f, -0.5f, -0.5f,\
0.5f, -0.5f, -0.5f,\
0.5f, -0.5f, 0.5f,\
0.5f, 0.5f, 0.5f,\
-0.5f, -0.5f, -0.5f,\
0.5f, -0.5f, -0.5f,\
0.5f, -0.5f, 0.5f,\
0.5f, -0.5f, 0.5f,\
-0.5f, -0.5f, 0.5f,\
-0.5f, -0.5f, -0.5f,\
-0.5f, 0.5f, -0.5f,\
0.5f, 0.5f, -0.5f,\
0.5f, 0.5f, 0.5f,\
0.5f, 0.5f, 0.5f,\
-0.5f, 0.5f, 0.5f,\
-0.5f, 0.5f, -0.5f
#endif // SCENE_MANAGER_H