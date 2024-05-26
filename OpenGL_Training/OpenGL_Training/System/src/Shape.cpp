/**
 * @file   : Shape.cpp
 * @author : Shuhei Matsushima
 *
 * @berief : �}�`�̕`��
 */

#include "Shape.h"

/**
 * �R���X�g���N�^
 *    size: ���_�̈ʒu�̎���
 *    vertexcount: ���_�̐�
 *    vertex: ���_�������i�[�����z��
 */
Shape::Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex)
    : object(new Object(size, vertexcount, vertex))
    , vertexcount(vertexcount)
{
}

/**
 * �`��
 */
void
Shape::draw() const
{
    // ���_�z��I�u�W�F�N�g����������
    object->bind();

    // �`������s����
    execute();
}

/**
 * �`��̎��s
 */
void
Shape::execute() const
{
    // �܂���ŕ`�悷��
    glDrawArrays(GL_LINE_LOOP, 0, vertexcount);
}