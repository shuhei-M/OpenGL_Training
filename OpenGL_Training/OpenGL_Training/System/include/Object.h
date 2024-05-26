/**
 * @file   : Object.h
 * @author : Shuhei Matsushima
 *
 * @berief : 図形データ
 */

#ifndef __OBJECT_H_
#define __OBJECT_H_

#include <array>
#include <GL/glew.h>

/**
 * 図形データクラス
 */
class Object
{
public:
    // 頂点属性
    struct Vertex
    {
        // 位置
        GLfloat position[2];
    };

    // コンストラクタ
    Object(GLint size, GLsizei vertexcount, const Vertex* vertex);
    // デストラクタ
    virtual ~Object();

    // 頂点配列オブジェクトの結合
    void bind() const;

private:
    // コピーコンストラクタによるコピー禁止
    Object(const Object& o);

    // 代入によるコピー禁止
    Object& operator=(const Object& o);

private:
    // 頂点配列オブジェクト名
    GLuint vao;
    // 頂点バッファオブジェクト名
    GLuint vbo;
};

#endif // #ifndef __OBJECT_H_