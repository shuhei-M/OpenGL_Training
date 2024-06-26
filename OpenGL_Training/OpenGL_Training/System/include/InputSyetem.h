/**
 * @file   : InputSystem.h
 * @author : Shuhei Matsushima
 *
 * @berief : 入力
 */

#ifndef __INPUTSYSTEM_H_
#define __INPUTSYSTEM_H_

struct GLFWwindow;

/**
 * 入力クラス
 */
class InputSystem
{
public:
	static void init(GLFWwindow* window);
	static void update(GLFWwindow* window);
	static void resetWheel();

	static bool getMouseButtonPressL() { return mIsMouseButtonPressL; }
	static bool getMouseButtonPressR() { return mIsMouseButtonPressR; }
	static bool getIsMouseWheelScroll() { return mIsMouseWheelScroll; }
	static double getMouseWheelY() { return mMouseWheelY; }
	static double getMouseX() { return mMouseX; }
	static double getMouseY() { return mMouseY; }

private:
	static void wheel(GLFWwindow* window, double x, double y);

private:
	static bool mIsMouseButtonPressL;
	static bool mIsMouseButtonPressR;
	static double mMouseX;
	static double mMouseY;
	static bool mIsMouseWheelScroll;
	static double mMouseWheelY;
};

#endif // #ifndef __INPUTSYSTEM_H_