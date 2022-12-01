#include <iostream>

#include <glad/glad.h>  
#include <GLFW/glfw3.h>

#include "Global.h"
#include "GameHeader/Game.h"
#include "GameHeader/ResourceManager.h"
#include <glm/ext/matrix_clip_space.hpp>
#include "GameHeader/SpriteRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
Game Breakout(SCR_WIDTH, SCR_HEIGHT);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	//创建window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Breakout", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//创建上下文
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//设置间隔（帧数）
	glfwSwapInterval(1);

	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建渲染窗口
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	//线框模式
	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	//默认模式
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//回调
	glfwSetKeyCallback(window, key_callback);

	GLfloat deltaTime = 0.0f; // 当前帧与上一帧的时间差
	GLfloat lastFrame = 0.0f; // 上一帧的时间

	Breakout.Init();
	Breakout.State = GAME_ACTIVE;

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader = ResourceManager::LoadShader("res/shaders/sprite.vs", "res/shaders/sprite.frag", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), static_cast<GLfloat>(SCR_HEIGHT), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	SpriteRenderer Renderer(shader);

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/*Breakout.ProcessInput(deltaTime);
		Breakout.Update(deltaTime);*/

		//渲染指令
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto texture = ResourceManager::GetTexture("background");
		Renderer.DrawSprite(texture,
			glm::vec2(0, 0), glm::vec2(SCR_WIDTH, SCR_WIDTH), 0.0f
		);

		Breakout.Render();

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//关闭
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Breakout.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Breakout.Keys[key] = GL_FALSE;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// 随平面拖拽变化
	glViewport(0, 0, width, height);
}