#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "windowmanager.h"
#include "shader.h"

class SceneManager : public WindowManager
{
public:
	virtual void initialize() override;
	// stuff i can implement if i want
	//virtual void process_input(float delta_time) override;
	//virtual void mouse_event(double xPosIn, double yPosIn) override;
	//virtual void scroll_callback(double xoffset, double yoffset) override;

	// Drawing stuff
	virtual void app_logic() override;
	virtual void draw() override;

private:
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