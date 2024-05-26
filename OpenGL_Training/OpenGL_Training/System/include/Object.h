/**
 * @file   : Object.h
 * @author : Shuhei Matsushima
 *
 * @berief : �}�`�f�[�^
 */

#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <array>
#include <GL/glew.h>

/**
 * �}�`�f�[�^�N���X
 */
class Object
{
public:
    // ���_����
    struct Vertex
    {
        // �ʒu
        GLfloat position[2];
    };

    // �R���X�g���N�^
    Object(GLint size, GLsizei vertexcount, const Vertex* vertex);
    // �f�X�g���N�^
    virtual ~Object();

    // ���_�z��I�u�W�F�N�g�̌���
    void bind() const;

private:
    // �R�s�[�R���X�g���N�^�ɂ��R�s�[�֎~
    Object(const Object& o);

    // ����ɂ��R�s�[�֎~
    Object& operator=(const Object& o);

private:
    // ���_�z��I�u�W�F�N�g��
    GLuint vao;
    // ���_�o�b�t�@�I�u�W�F�N�g��
    GLuint vbo;
};

#endif // #ifndef __OBJECT_H_