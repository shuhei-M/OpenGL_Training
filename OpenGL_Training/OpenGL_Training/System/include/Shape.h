/**
 * @file   : Shape.h
 * @author : Shuhei Matsushima
 *
 * @berief : �}�`�̕`��
 */

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <memory>
#include "Object.h"

 /**
  * �}�`�̕`��N���X
  */
class Shape
{
public:
    // �R���X�g���N�^
    Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex);

    // �`��
    void draw() const;

    // �`��̎��s
    virtual void execute() const;

protected:
    // �`��Ɏg�����_�̐�
    const GLsizei vertexcount;

private:
    // �}�`�f�[�^
    std::shared_ptr<const Object> object;
};

#endif // #ifndef __SHAPE_H_