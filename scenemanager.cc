#include "scenemanager.h"


void SceneManager::initialize()
{
	// Im not gonna bother deleting this in the deconstructor, who cares?
	camera = new Camera();

	init_cube();
	init_light_cube();
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
