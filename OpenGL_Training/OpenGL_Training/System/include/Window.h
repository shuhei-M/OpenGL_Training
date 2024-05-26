/**
 * @file   : Window.h
 * @author : Shuhei Matsushima
 *
 * @berief : �E�B���h�E
 */

#ifndef __WINDOW_H_
#define __WINDOW_H_

#include <GL/glew.h> 
#include <GLFW/glfw3.h> 

/**
 * �E�B���h�E�N���X
 */
class Window
{
public:
    // �R���X�g���N�^
    Window(int width = 1280, int height = 720, const char* title = "Window");
    // �f�X�g���N�^
    virtual ~Window();

    // �E�B���h�E�����ׂ����𔻒肷��
    int shouldClose() const;
    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    void swapBuffers();
    // �E�B���h�E�̃T�C�Y�ύX���̏���
    static void resize(GLFWwindow* window, int width, int height);

    // �E�B���h�E�̎擾
    GLFWwindow* getWindow() const { return mWindow; }
    // �E�B���h�E�̃T�C�Y�����o��
    const GLfloat* getSize() const { return mSize; }
    // ���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦�����o��
    GLfloat getScale() const { return mScale; }
    // �ʒu�����o�� 
    const GLfloat* getLocation() const { return mLocation; }

    void updateScale();

private:

private:
    // �E�B���h�E�̎��ʎq
    GLFWwindow* const mWindow;
    // �E�B���h�E�̃T�C�Y
    GLfloat mSize[2];
    // ���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦
    GLfloat mScale;
    // �}�`�̐��K���f�o�C�X���W�n��ł̈ʒu 
    GLfloat mLocation[2];
};

#endif // #ifndef __WINDOW_H_