#include "pch.h"
#include "Input.h"
#include "Core.h"
#include "Events.h"
#include "Application.h"
#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine
{
	Input* Input::s_Instance	= new Input();
	float Input::s_scrollX		= 0;
	float Input::s_scrollY		= 0;



	bool Input::KeyPress(int keycode)
	{
		Application& app		= Application::Get();
		const Window& window	= app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		if (glfwGetKey(glfw_Window, keycode) == GLFW_PRESS)
			return true;

		return false;
	}




	bool Input::KeyRelease(int keycode)
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		if (glfwGetKey(glfw_Window, keycode) == GLFW_RELEASE)
			return true;

		return false;
	}




	bool Input::MousePress(int button)
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		if (glfwGetMouseButton(glfw_Window, button) == GLFW_PRESS)
			return true;

		return false;
	}




	bool Input::MouseRelease(int button)
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		if (glfwGetMouseButton(glfw_Window, button) == GLFW_RELEASE)
			return true;

		return false;
	}



	float Input::GetMouseX()
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		double x, y;

		glfwGetCursorPos(glfw_Window, &x, &y);

		return (float)x;
	}



	float Input::GetMouseY()
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		double x, y;

		glfwGetCursorPos(glfw_Window, &x, &y);

		return (float)y;
	}




	float Input::GetScroll()
	{
		Application& app = Application::Get();
		const Window& window = app.GetWindow();
		GLFWwindow* glfw_Window = window.m_GLFWwindow;

		glfwSetScrollCallback(glfw_Window, [](GLFWwindow* window, double xoff, double yoff)
		{
				s_scrollX = xoff;
				s_scrollY = yoff;
		});

		return s_scrollY;
	}
}