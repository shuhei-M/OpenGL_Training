/**
 * @file   : Window.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : �E�B���h�E
 */

#include "Window.h"
#include <iostream> 
#include "InputSyetem.h"

/**
 * �R���X�g���N�^
 */
Window::Window(int width, int height, const char* title)
    : mWindow(glfwCreateWindow(width, height, title, NULL, NULL))
     ,mScale(100.0f), mLocation{ 0.0f, 0.0f }
{
    if (mWindow == NULL)
    {
        // �E�B���h�E���쐬�ł��Ȃ�����
        std::cerr << "Can't create GLFW window." << std::endl;
        exit(1);
    }

    // ���݂̃E�B���h�E�������Ώۂɂ���
    glfwMakeContextCurrent(mWindow);

    // GLEW ������������
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        // GLEW �̏������Ɏ��s����
        std::cerr << "Can't initialize GLEW" << std::endl;
        exit(1);
    }

    // �쐬�����E�B���h�E�ɑ΂���ݒ�
    glfwSwapInterval(1);

    // �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
    glfwSetWindowSizeCallback(mWindow, resize);

    // ���̃C���X�^���X�� this �|�C���^���L�^���Ă���
    glfwSetWindowUserPointer(mWindow, this);

    // �J�����E�B���h�E�̏����ݒ�
    resize(mWindow, width, height);
}

/**
 * �f�X�g���N�^
 */
Window::~Window()
{
    // �E�B���h�E��j������
    glfwDestroyWindow(mWindow);
}

/**
 * �E�B���h�E�����ׂ����𔻒肷��
 */
int
Window::shouldClose() const
{    
    return glfwWindowShouldClose(mWindow);
}

/**
 * �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
 */
void
Window::swapBuffers()
{
    // �J���[�o�b�t�@�����ւ���
    glfwSwapBuffers(mWindow);

    // �C�x���g�����o��
    glfwWaitEvents();

    // �}�E�X�̍��{�^����������Ă�����
    if (InputSystem::getMouseButtonPressL())
    {
        // �}�E�X�J�[�\���̈ʒu���擾����
        double x = InputSystem::getMouseX();
        double y = InputSystem::getMouseY();
        // �}�E�X�J�[�\���̐��K���f�o�C�X���W�n��ł̈ʒu�����߂�
        mLocation[0] = static_cast<GLfloat>(x) * 2.0f / mSize[0] - 1.0f;
        mLocation[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / mSize[1];
    }
}

/**
 * �E�B���h�E�̃T�C�Y�ύX���̏���
 */
void
Window::resize(GLFWwindow* window, int width, int height)
{
    // �E�B���h�E�S�̂��r���[�|�[�g�ɂ���
    glViewport(0, 0, width, height);

    // ���̃C���X�^���X�� this �|�C���^�𓾂�
    Window* const
        instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

    if (instance != NULL)
    {
        // �J�����E�B���h�E�̃T�C�Y��ۑ�����
        instance->mSize[0] = static_cast<GLfloat>(width);
        instance->mSize[1] = static_cast<GLfloat>(height);
    }
}





// �}�E�X�z�C�[�����쎞�̏��� 
void
Window::updateScale()
{
    if (InputSystem::getIsMouseWheelScroll)
    {
        // ���̃C���X�^���X�� this �|�C���^�𓾂�
        Window* const
            instance(static_cast<Window*>(glfwGetWindowUserPointer(mWindow)));

        if (instance != NULL)
        {
            // ���[���h���W�n�ɑ΂���f�o�C�X���W�n�̊g�嗦���X�V����
            instance->mScale += static_cast<GLfloat>(InputSystem::getMouseWheelY());
            if (instance->mScale < 0.0f) instance->mScale = 0.0f;
        }

        InputSystem::resetWheel();
    }
}