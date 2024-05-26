/**
 * @file   : Application.h
 * @author : Shuhei Matsushima
 *
 * @berief : アプリケーション
 */

#include "Application.h"

#include <string>
#include <fstream>

#include "InputSyetem.h"
#include "Shape.h"
#include "Window.h"


 // 矩形の頂点の位置 
constexpr Object::Vertex rectangleVertex[] =
{
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f }
};

/**
 * 初期化
 */
Application::Application()
    : mTimer(0), mWindow(nullptr)
    , mProgram(nullptr)
    , mSizeLoc(nullptr), mScaleLoc(nullptr), mLocationLoc(nullptr)
{
}

/**
 * デストラクタ
 */
Application::~Application()
{
    delete mWindow;
    delete mProgram;
    delete mSizeLoc;
    delete mScaleLoc;
    delete mLocationLoc;
}

/**
 * OpenGLの初期化
 */
bool
Application::tryInitGL()
{
    // GLFW を初期化する
    if (glfwInit() == GL_FALSE)
    {
        // 初期化に失敗した
        std::cerr << "Can't initialize GLFW" << std::endl;
        return false;
    }

    // プログラム終了時の処理を登録する
    atexit(glfwTerminate);

    // OpenGL Version 3.2 Core Profile を選択する
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 完了
    return true;
}

/**
 * ウィンドウの初期化
 */
void
Application::initWindow()
{
    // ウィンドウを作成する
    mWindow = new Window;

    // 背景色を指定する
    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
}

/**
 * シェーダの初期化
 */
void
Application::initShader()
{
    // プログラムオブジェクトを作成する
    mProgram = new GLuint(loadProgram("point.vert", "point.frag"));

    // uniform 変数の場所を取得する
    mSizeLoc = new GLint(glGetUniformLocation(*mProgram, "size"));
    mScaleLoc = new GLint(glGetUniformLocation(*mProgram, "scale"));
    mLocationLoc = new GLint(glGetUniformLocation(*mProgram, "location"));
}

/**
 * 実行
 */
void
Application::run()
{
    // ウィンドウの初期化
    initWindow();

    // 入力システムの初期化
    InputSystem::init(mWindow->getWindow());

    // シェーダーの初期化
    initShader();

    // 図形データを作成する 
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

    // ウィンドウが開いている間繰り返す
    while (mWindow->shouldClose() == GL_FALSE)
    {
        // ウィンドウを消去する
        glClear(GL_COLOR_BUFFER_BIT);

        // 入力情報の更新
        InputSystem::update(mWindow->getWindow());

        mWindow->updateScale();

        // シェーダプログラムの使用開始
        glUseProgram(*mProgram);

        // uniform 変数に値を設定する
        glUniform2fv(*mSizeLoc, 1, mWindow->getSize());
        glUniform1f(*mScaleLoc, mWindow->getScale());
        glUniform2fv(*mLocationLoc, 1, mWindow->getLocation());

        // 図形を描画する
        shape->draw();

        // カラーバッファを入れ替えてイベントを取り出す
        mWindow->swapBuffers();
    }
}






/**
 * シェーダオブジェクトのコンパイル結果を表示する
 * shader: シェーダオブジェクト名
 * str: コンパイルエラーが発生した場所を示す文字列
 */
GLboolean 
Application::printShaderInfoLog(GLuint shader, const char* str)
{
    // コンパイル結果を取得する
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

    // シェーダのコンパイル時のログの長さを取得する
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1)
    {
        // シェーダのコンパイル時のログの内容を取得する
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}


/**
 * プログラムオブジェクトのリンク結果を表示する
 * program: プログラムオブジェクト名
 */
GLboolean
Application::printProgramInfoLog(GLuint program)
{
    // リンク結果を取得する
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

    // シェーダのリンク時のログの長さを取得する
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1)
    {
        // シェーダのリンク時のログの内容を取得する
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

/**
 * プログラムオブジェクトを作成する
 * vsrc: バーテックスシェーダのソースプログラムの文字列
 * fsrc: フラグメントシェーダのソースプログラムの文字列
 */
GLuint
Application::createProgram(const char* vsrc, const char* fsrc)
{
    // 空のプログラムオブジェクトを作成する
    const GLuint program(glCreateProgram());

    if (vsrc != NULL)
    {
        // バーテックスシェーダのシェーダオブジェクトを作成する
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);

        // バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
        if (printShaderInfoLog(vobj, "vertex shader"))
            glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }

    if (fsrc != NULL)
    {
        // フラグメントシェーダのシェーダオブジェクトを作成する
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);

        // フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
        if (printShaderInfoLog(fobj, "fragment shader"))
            glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }

    // プログラムオブジェクトをリンクする
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);

    // 作成したプログラムオブジェクトを返す
    if (printProgramInfoLog(program))
        return program;

    // プログラムオブジェクトが作成できなければ 0 を返す
    glDeleteProgram(program);
    return 0;
}

/**
 * シェーダのソースファイルを読み込んだメモリを返す
 * name: シェーダのソースファイル名
 * buffer: 読み込んだソースファイルのテキスト
 */
bool
Application::readShaderSource(const char* name, std::vector<GLchar>& buffer)
{
    // ファイル名が NULL だった
    if (name == NULL) return false;
    // プロジェクトが変わった際は、適宜パスを書き換える事
    const char* path = "D:\\GitHub\\shuhei-M\\OpenGL_Training\\OpenGL_Training\\OpenGL_Training\\Shaders\\";
    std::string fullPath = (std::string)path + (std::string)name;
    std::ifstream file(fullPath.c_str(), std::ios::binary);
    if (file.fail())
    {
        // 開けなかった
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }

    // ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // ファイルサイズのメモリを確保
    buffer.resize(length + 1);

    // ファイルを先頭から読み込む
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail())
    {
        // うまく読み込めなかった
        std::cerr << "Error: Could not read souce file: " << name << std::endl;
        file.close();
        return false;
    }

    // 読み込み成功
    file.close();
    return true;
}

/**
 * シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
 * vert: バーテックスシェーダのソースファイル名
 * frag: フラグメントシェーダのソースファイル名
 */
GLuint
Application::loadProgram(const char* vert, const char* frag)
{
    // シェーダのソースファイルを読み込む
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));

    // プログラムオブジェクトを作成する
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}