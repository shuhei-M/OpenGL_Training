/**
 * @file   : Application.h
 * @author : Shuhei Matsushima
 *
 * @berief : �A�v���P�[�V����
 */

#include "Application.h"

#include <string>
#include <fstream>

#include "InputSyetem.h"
#include "Shape.h"
#include "Window.h"


 // ��`�̒��_�̈ʒu 
constexpr Object::Vertex rectangleVertex[] =
{
    { -0.5f, -0.5f },
    {  0.5f, -0.5f },
    {  0.5f,  0.5f },
    { -0.5f,  0.5f }
};

/**
 * ������
 */
Application::Application()
    : mTimer(0), mWindow(nullptr)
    , mProgram(nullptr)
    , mSizeLoc(nullptr), mScaleLoc(nullptr), mLocationLoc(nullptr)
{
}

/**
 * �f�X�g���N�^
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
 * OpenGL�̏�����
 */
bool
Application::tryInitGL()
{
    // GLFW ������������
    if (glfwInit() == GL_FALSE)
    {
        // �������Ɏ��s����
        std::cerr << "Can't initialize GLFW" << std::endl;
        return false;
    }

    // �v���O�����I�����̏�����o�^����
    atexit(glfwTerminate);

    // OpenGL Version 3.2 Core Profile ��I������
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ����
    return true;
}

/**
 * �E�B���h�E�̏�����
 */
void
Application::initWindow()
{
    // �E�B���h�E���쐬����
    mWindow = new Window;

    // �w�i�F���w�肷��
    glClearColor(0.75f, 0.75f, 0.75f, 0.0f);
}

/**
 * �V�F�[�_�̏�����
 */
void
Application::initShader()
{
    // �v���O�����I�u�W�F�N�g���쐬����
    mProgram = new GLuint(loadProgram("point.vert", "point.frag"));

    // uniform �ϐ��̏ꏊ���擾����
    mSizeLoc = new GLint(glGetUniformLocation(*mProgram, "size"));
    mScaleLoc = new GLint(glGetUniformLocation(*mProgram, "scale"));
    mLocationLoc = new GLint(glGetUniformLocation(*mProgram, "location"));
}

/**
 * ���s
 */
void
Application::run()
{
    // �E�B���h�E�̏�����
    initWindow();

    // ���̓V�X�e���̏�����
    InputSystem::init(mWindow->getWindow());

    // �V�F�[�_�[�̏�����
    initShader();

    // �}�`�f�[�^���쐬���� 
    std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

    // �E�B���h�E���J���Ă���ԌJ��Ԃ�
    while (mWindow->shouldClose() == GL_FALSE)
    {
        // �E�B���h�E����������
        glClear(GL_COLOR_BUFFER_BIT);

        // ���͏��̍X�V
        InputSystem::update(mWindow->getWindow());

        mWindow->updateScale();

        // �V�F�[�_�v���O�����̎g�p�J�n
        glUseProgram(*mProgram);

        // uniform �ϐ��ɒl��ݒ肷��
        glUniform2fv(*mSizeLoc, 1, mWindow->getSize());
        glUniform1f(*mScaleLoc, mWindow->getScale());
        glUniform2fv(*mLocationLoc, 1, mWindow->getLocation());

        // �}�`��`�悷��
        shape->draw();

        // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
        mWindow->swapBuffers();
    }
}






/**
 * �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
 * shader: �V�F�[�_�I�u�W�F�N�g��
 * str: �R���p�C���G���[�����������ꏊ������������
 */
GLboolean 
Application::printShaderInfoLog(GLuint shader, const char* str)
{
    // �R���p�C�����ʂ��擾����
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;

    // �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1)
    {
        // �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}


/**
 * �v���O�����I�u�W�F�N�g�̃����N���ʂ�\������
 * program: �v���O�����I�u�W�F�N�g��
 */
GLboolean
Application::printProgramInfoLog(GLuint program)
{
    // �����N���ʂ��擾����
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) std::cerr << "Link Error." << std::endl;

    // �V�F�[�_�̃����N���̃��O�̒������擾����
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

    if (bufSize > 1)
    {
        // �V�F�[�_�̃����N���̃��O�̓��e���擾����
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }

    return static_cast<GLboolean>(status);
}

/**
 * �v���O�����I�u�W�F�N�g���쐬����
 * vsrc: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�����̕�����
 * fsrc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̕�����
 */
GLuint
Application::createProgram(const char* vsrc, const char* fsrc)
{
    // ��̃v���O�����I�u�W�F�N�g���쐬����
    const GLuint program(glCreateProgram());

    if (vsrc != NULL)
    {
        // �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);

        // �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
        if (printShaderInfoLog(vobj, "vertex shader"))
            glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }

    if (fsrc != NULL)
    {
        // �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);

        // �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
        if (printShaderInfoLog(fobj, "fragment shader"))
            glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }

    // �v���O�����I�u�W�F�N�g�������N����
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "fragment");
    glLinkProgram(program);

    // �쐬�����v���O�����I�u�W�F�N�g��Ԃ�
    if (printProgramInfoLog(program))
        return program;

    // �v���O�����I�u�W�F�N�g���쐬�ł��Ȃ���� 0 ��Ԃ�
    glDeleteProgram(program);
    return 0;
}

/**
 * �V�F�[�_�̃\�[�X�t�@�C����ǂݍ��񂾃�������Ԃ�
 * name: �V�F�[�_�̃\�[�X�t�@�C����
 * buffer: �ǂݍ��񂾃\�[�X�t�@�C���̃e�L�X�g
 */
bool
Application::readShaderSource(const char* name, std::vector<GLchar>& buffer)
{
    // �t�@�C������ NULL ������
    if (name == NULL) return false;
    // �v���W�F�N�g���ς�����ۂ́A�K�X�p�X�����������鎖
    const char* path = "D:\\GitHub\\shuhei-M\\OpenGL_Training\\OpenGL_Training\\OpenGL_Training\\Shaders\\";
    std::string fullPath = (std::string)path + (std::string)name;
    std::ifstream file(fullPath.c_str(), std::ios::binary);
    if (file.fail())
    {
        // �J���Ȃ�����
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }

    // �t�@�C���̖����Ɉړ������݈ʒu�i���t�@�C���T�C�Y�j�𓾂�
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());

    // �t�@�C���T�C�Y�̃��������m��
    buffer.resize(length + 1);

    // �t�@�C����擪����ǂݍ���
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';

    if (file.fail())
    {
        // ���܂��ǂݍ��߂Ȃ�����
        std::cerr << "Error: Could not read souce file: " << name << std::endl;
        file.close();
        return false;
    }

    // �ǂݍ��ݐ���
    file.close();
    return true;
}

/**
 * �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���Ńv���O�����I�u�W�F�N�g���쐬����
 * vert: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�t�@�C����
 * frag: �t���O�����g�V�F�[�_�̃\�[�X�t�@�C����
 */
GLuint
Application::loadProgram(const char* vert, const char* frag)
{
    // �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));

    // �v���O�����I�u�W�F�N�g���쐬����
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}