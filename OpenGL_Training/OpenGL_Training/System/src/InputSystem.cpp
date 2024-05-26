/**
 * @file   : InputSystem.h
 * @author : Shuhei Matsushima
 *
 * @berief : ����
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
	// �}�E�X�z�C�[�����쎞�ɌĂяo�������̓o�^ 
	glfwSetScrollCallback(window, wheel);
}

void 
InputSystem::update(GLFWwindow* window)
{
	// ���E�}�E�X�{�^��
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)) mIsMouseButtonPressL = true;
	else mIsMouseButtonPressL = false;
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) != GLFW_RELEASE)) mIsMouseButtonPressR = true;
	else mIsMouseButtonPressR = false;

	// �}�E�X�̈ʒu
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