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

	//����window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MyOpenGL", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//����������
	glfwMakeContextCurrent(window);

	//���ü����֡����
	glfwSwapInterval(1);

	//glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//������Ⱦ����
	GLCall(glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT));
	//��ק�ص� �ı���Ⱦ���ڴ�С
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//���������
	if (showCursor)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//�߿�ģʽ
	//GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
	//Ĭ��ģʽ
	GLCall(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));

	//�ص�
	GLCall(glfwSetCursorPosCallback(window, mouse_callback));
	GLCall(glfwSetScrollCallback(window, scroll_callback));

	GLfloat deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
	GLfloat lastFrame = 0.0f; // ��һ֡��ʱ��

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//����
		processInput(window);

		//��Ⱦָ��
		GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));
		//GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
		/*
		* ��������  GL_COLOR_BUFFER_BIT������ɫ����
		* ��������  GL_DEPTH_BUFFER_BIT������Ȼ���
		* ��������  GL_STENCIL_BUFFER_BIT����ģ�建��
		*/
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//�ر�
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}