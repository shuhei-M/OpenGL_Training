/**
 * @file   : Application.h
 * @author : Shuhei Matsushima
 *
 * @berief : �A�v���P�[�V����
 */

#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * �A�v���P�[�V�����N���X
 */
class Application
{
public:
	// �R���X�g���N�^
	Application();

	// ������
	bool tryInit();
	// ���s
	void run();

private:
	// �V�F�[�_�I�u�W�F�N�g�̃R���p�C�����ʂ�\������
	GLboolean printShaderInfoLog(GLuint shader, const char* str);
	// �v���O�����I�u�W�F�N�g�̃����N���ʂ�\������
	GLboolean printProgramInfoLog(GLuint program);
	// �v���O�����I�u�W�F�N�g���쐬����
	GLuint createProgram(const char* vsrc, const char* fsrc);
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ��񂾃�������Ԃ�
	bool readShaderSource(const char* name, std::vector<GLchar>& buffer);
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���Ńv���O�����I�u�W�F�N�g���쐬����
	GLuint loadProgram(const char* vert, const char* frag);

private:
	int mTimer = 0;
	GLFWwindow* mWindow = nullptr;
};

#endif // #ifndef __APPLICATION_H_