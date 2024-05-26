/**
 * @file   : Object.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : �}�`�f�[�^
 */

#include "Object.h"

/**
 * �}�`�f�[�^�N���X
 *    size: ���_�̈ʒu�̎���
 *    vertexcount: ���_�̐�
 *    vertex: ���_�������i�[�����z��
 */
Object::Object(GLint size, GLsizei vertexcount, const Vertex* vertex)
{
    // ���_�z��I�u�W�F�N�g
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // ���_�o�b�t�@�I�u�W�F�N�g
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
        vertexcount * sizeof(Vertex), vertex, GL_STATIC_DRAW);

    // ��������Ă��钸�_�o�b�t�@�I�u�W�F�N�g�� in �ϐ�����Q�Ƃł���悤�ɂ���
    glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

/**
 * �f�X�g���N�^
 */
Object::~Object()
{
    // ���_�z��I�u�W�F�N�g���폜����
    glDeleteBuffers(1, &vao);

    // ���_�o�b�t�@�I�u�W�F�N�g���폜����
    glDeleteBuffers(1, &vbo);
}


/**
 * ���_�z��I�u�W�F�N�g�̌���
 */
void 
Object::bind() const
{
    // �`�悷�钸�_�z��I�u�W�F�N�g���w�肷��
    glBindVertexArray(vao);
}