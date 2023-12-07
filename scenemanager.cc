#include "scenemanager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

unsigned int SceneManager::scr_width = 800;
unsigned int SceneManager::scr_height = 600;
Camera* SceneManager::camera = nullptr;
GLFWwindow* SceneManager::window = nullptr;

void SceneManager::initialize()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	// Register GLFW callbacks
	register_callbacks();

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	glEnable(GL_DEPTH_TEST);

	// Im not gonna bother deleting this in the deconstructor, who cares?
	camera = new Camera();
	init_cube();
	init_light_cube();
}

void SceneManager::start_window()
{
	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float current_frame = static_cast<float>(glfwGetTime());
		static float delta_time = 0.0f;
		static float last_frame = 0.0f;
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		// input
		process_input(delta_time);
		// Set uniforms, position objects
		app_logic();

		// render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void SceneManager::process_input(float delta_time)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, delta_time);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void SceneManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	scr_width = width;
	scr_height = height;
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void SceneManager::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	static bool firstMouse = true;
	static float lastX = scr_width / 2.0f;
	static float lastY = scr_height / 2.0f;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void SceneManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void SceneManager::register_callbacks()
{
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void SceneManager::init_cube()
{
	float vertices[] = { CUBE_VERTEX_DATA };

	cube_vertices = 36;
	glGenVertexArrays(1, &cube_vao);
	glGenBuffers(1, &cube_vbo);

	glBindVertexArray(cube_vao);
	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	default_shader = new Shader("shaders/cube.vs", "shaders/cube.fs");
}

void SceneManager::init_light_cube()
{
	float vertices[] = { CUBE_VERTEX_DATA };

	glGenVertexArrays(1, &light_vao);
	glGenBuffers(1, &light_vbo);

	glBindVertexArray(light_vao);
	glBindBuffer(GL_ARRAY_BUFFER, light_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
	glBindVertexArray(0); //unbind
	light_shader = new Shader("shaders/light.vs", "shaders/light.fs");
}

void SceneManager::app_logic()
{
	// normal cube
	glm::vec3 cube_pos(0.5f, 0.3f, -2.0f);
	glm::mat4 model(1.0f);
	model = glm::translate(model, cube_pos);
	model = glm::scale(model, glm::vec3(0.5f));
	glm::mat4 view = camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)scr_width / (float)scr_height, 0.1f, 100.0f);

	default_shader->use();
	default_shader->setMat4("model", model);

	default_shader->setMat4("view", view);
	default_shader->setMat4("projection", projection);

	default_shader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
	default_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

	// light cube
	glm::vec3 light_pos(-0.5f, 0.7f, -3.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, light_pos);
	model = glm::scale(model, glm::vec3(0.2f));
	light_shader->use();
	light_shader->setMat4("model", model);

	light_shader->setMat4("view", view);
	light_shader->setMat4("projection", projection);

	light_shader->setVec3("objectColor", 1.0f, 1.0f, 1.0f);
	light_shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
}

void SceneManager::draw()
{
	default_shader->use();
	glBindVertexArray(cube_vao);
	glDrawArrays(GL_TRIANGLES, 0, cube_vertices);

	light_shader->use();
	glBindVertexArray(light_vao);
	glDrawArrays(GL_TRIANGLES, 0, cube_vertices);

	glBindVertexArray(0);
}