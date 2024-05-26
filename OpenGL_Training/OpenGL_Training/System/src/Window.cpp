/**
 * @file   : Window.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : ウィンドウ
 */

#include "Window.h"
#include <iostream> 
#include "InputSyetem.h"

/**
 * コンストラクタ
 */
Window::Window(int width, int height, const char* title)
    : mWindow(glfwCreateWindow(width, height, title, NULL, NULL))
     ,mScale(100.0f), mLocation{ 0.0f, 0.0f }
{
    if (mWindow == NULL)
    {
        // ウィンドウが作成できなかった
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }

    // 現在のウィンドウを処理対象にする
    glfwMakeContextCurrent(mWindow);

    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        // GLEW の初期化に失敗した
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }

    // 作成したウィンドウに対する設定
    glfwSwapInterval(1);

    // ウィンドウのサイズ変更時に呼び出す処理の登録
    glfwSetWindowSizeCallback(mWindow, resize);

    // このインスタンスの this ポインタを記録しておく
    glfwSetWindowUserPointer(mWindow, this);

    // 開いたウィンドウの初期設定
    resize(mWindow, width, height);
}

/**
 * デストラクタ
 */
Window::~Window()
{
    // ウィンドウを破棄する
    glfwDestroyWindow(mWindow);
}

/**
 * ウィンドウを閉じるべきかを判定する
 */
int
Window::shouldClose() const
{    
    return glfwWindowShouldClose(mWindow);
}

/**
 * カラーバッファを入れ替えてイベントを取り出す
 */
void
Window::swapBuffers()
{
    // カラーバッファを入れ替える
    glfwSwapBuffers(mWindow);

    // イベントを取り出す
    glfwWaitEvents();

    // マウスの左ボタンが押されていたら
    if (InputSystem::getMouseButtonPressL())
    {
        // マウスカーソルの位置を取得する
        double x = InputSystem::getMouseX();
        double y = InputSystem::getMouseY();
        // マウスカーソルの正規化デバイス座標系上での位置を求める
        mLocation[0] = static_cast<GLfloat>(x) * 2.0f / mSize[0] - 1.0f;
        mLocation[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / mSize[1];
    }
}

/**
 * ウィンドウのサイズ変更時の処理
 */
void
Window::resize(GLFWwindow* window, int width, int height)
{
    // ウィンドウ全体をビューポートにする
    glViewport(0, 0, width, height);

    // このインスタンスの this ポインタを得る
    Window* const
        instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

    if (instance != NULL)
    {
        // 開いたウィンドウのサイズを保存する
        instance->mSize[0] = static_cast<GLfloat>(width);
        instance->mSize[1] = static_cast<GLfloat>(height);
    }
}





// マウスホイール操作時の処理 
void
Window::updateScale()
{
    if (InputSystem::getIsMouseWheelScroll)
    {
        // このインスタンスの this ポインタを得る
        Window* const
            instance(static_cast<Window*>(glfwGetWindowUserPointer(mWindow)));

        if (instance != NULL)
        {
            // ワールド座標系に対するデバイス座標系の拡大率を更新する
            instance->mScale += static_cast<GLfloat>(InputSystem::getMouseWheelY());
            if (instance->mScale < 0.0f) instance->mScale = 0.0f;
        }

        InputSystem::resetWheel();
    }
}