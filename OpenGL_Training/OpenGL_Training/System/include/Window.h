/**
 * @file   : Window.h
 * @author : Shuhei Matsushima
 *
 * @berief : ウィンドウ
 */

#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <GL/glew.h> 
#include <GLFW/glfw3.h> 

/**
 * ウィンドウクラス
 */
class Window
{
public:
    // コンストラクタ
    Window(int width = 1280, int height = 720, const char* title = "Window");
    // デストラクタ
    virtual ~Window();

    // ウィンドウを閉じるべきかを判定する
    int shouldClose() const;
    // カラーバッファを入れ替えてイベントを取り出す
    void swapBuffers();
    // ウィンドウのサイズ変更時の処理
    static void resize(GLFWwindow* window, int width, int height);

    // ウィンドウの取得
    GLFWwindow* getWindow() const { return mWindow; }
    // ウィンドウのサイズを取り出す
    const GLfloat* getSize() const { return mSize; }
    // ワールド座標系に対するデバイス座標系の拡大率を取り出す
    GLfloat getScale() const { return mScale; }
    // 位置を取り出す 
    const GLfloat* getLocation() const { return mLocation; }

    void updateScale();

private:

private:
    // ウィンドウの識別子
    GLFWwindow* const mWindow;
    // ウィンドウのサイズ
    GLfloat mSize[2];
    // ワールド座標系に対するデバイス座標系の拡大率
    GLfloat mScale;
    // 図形の正規化デバイス座標系上での位置 
    GLfloat mLocation[2];
};

#endif // #ifndef __WINDOW_H_