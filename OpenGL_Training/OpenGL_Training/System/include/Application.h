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
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window;

/**
 * アプリケーションクラス
 */
class Application
{
public:
	// コンストラクタ
	Application();
	// デストラクタ
	~Application();

	// OpenGLの初期化
	bool tryInitGL();
	// 実行
	void run();

private:
	// ウィンドウの初期化
	void initWindow();
	// シェーダの初期化
	void initShader();

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
	Window* mWindow;

	// プログラムオブジェクト
	GLuint* mProgram;
	// uniform 変数
	GLint* mSizeLoc;
	GLint* mScaleLoc;
	GLint* mLocationLoc;
};

#endif // #ifndef __APPLICATION_H_