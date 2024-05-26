/**
 * @file   : InputSystem.h
 * @author : Shuhei Matsushima
 *
 * @berief : 入力
 */

#include "InputSyetem.h"
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 

bool InputSystem::mIsMouseButtonPressL = false;
bool InputSystem::mIsMouseButtonPressR = false;

bool InputSystem::mIsMouseWheelScroll = false;
double InputSystem::mMouseWheelY = 0.0f;

double InputSystem::mMouseX = 0.0;
double InputSystem::mMouseY = 0.0;

void
InputSystem::init(GLFWwindow* window)
{
	// マウスホイール操作時に呼び出す処理の登録 
	glfwSetScrollCallback(window, wheel);
}

void 
InputSystem::update(GLFWwindow* window)
{
	// 左右マウスボタン
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)) mIsMouseButtonPressL = true;
	else mIsMouseButtonPressL = false;
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) != GLFW_RELEASE)) mIsMouseButtonPressR = true;
	else mIsMouseButtonPressR = false;

	// マウスの位置
	glfwGetCursorPos(window, &mMouseX, &mMouseY);
}

void
InputSystem::resetWheel()
{
	mMouseWheelY = 0.0f;
	mIsMouseWheelScroll = false;
}



void
InputSystem::wheel(GLFWwindow* window, double x, double y)
{
	mMouseWheelY = y;
	mIsMouseWheelScroll = true;
}