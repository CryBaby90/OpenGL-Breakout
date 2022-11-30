#include "Application.h"

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MyOpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//创建上下文
	glfwMakeContextCurrent(window);

	//设置间隔（帧数）
	glfwSwapInterval(1);

	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//创建渲染窗口
	GLCall(glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
	//拖拽回调 改变渲染窗口大小
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//设置鼠标光标
	if (showCursor)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//线框模式
	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	//默认模式
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	//回调
	GLCall(glfwSetCursorPosCallback(window, mouse_callback));
	GLCall(glfwSetScrollCallback(window, scroll_callback));

	GLfloat deltaTime = 0.0f; // 当前帧与上一帧的时间差
	GLfloat lastFrame = 0.0f; // 上一帧的时间

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//输入
		processInput(window);

		//渲染指令
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		//GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		/*
		* 清屏函数  GL_COLOR_BUFFER_BIT清理颜色缓冲
		* 清屏函数  GL_DEPTH_BUFFER_BIT清理深度缓冲
		* 清屏函数  GL_STENCIL_BUFFER_BIT清理模板缓冲
		*/
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//关闭
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}