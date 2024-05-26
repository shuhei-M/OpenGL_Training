/**
 * @file   : Application.h
 * @author : Shuhei Matsushima
 *
 * @berief : アプリケーション
 */

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * アプリケーションクラス
 */
class Application
{
public:
	// コンストラクタ
	Application();

	// 初期化
	bool tryInit();
	// 実行
	void run();

private:
	// シェーダオブジェクトのコンパイル結果を表示する
	GLboolean printShaderInfoLog(GLuint shader, const char* str);
	// プログラムオブジェクトのリンク結果を表示する
	GLboolean printProgramInfoLog(GLuint program);
	// プログラムオブジェクトを作成する
	GLuint createProgram(const char* vsrc, const char* fsrc);
	// シェーダのソースファイルを読み込んだメモリを返す
	bool readShaderSource(const char* name, std::vector<GLchar>& buffer);
	// シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
	GLuint loadProgram(const char* vert, const char* frag);

private:
	int mTimer = 0;
	GLFWwindow* mWindow = nullptr;
};

#endif // #ifndef __APPLICATION_H_