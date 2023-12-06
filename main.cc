#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include "scenemanager.h"

SceneManager manager;

int main() 
{
	manager.initialize();
	manager.start_window();
	return 0;
}

