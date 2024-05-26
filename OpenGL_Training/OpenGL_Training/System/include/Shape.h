/**
 * @file   : Shape.h
 * @author : Shuhei Matsushima
 *
 * @berief : 図形の描画
 */

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <memory>
#include "Object.h"

 /**
  * 図形の描画クラス
  */
class Shape
{
public:
    // コンストラクタ
    Shape(GLint size, GLsizei vertexcount, const Object::Vertex* vertex);

    // 描画
    void draw() const;

    // 描画の実行
    virtual void execute() const;

protected:
    // 描画に使う頂点の数
    const GLsizei vertexcount;

private:
    // 図形データ
    std::shared_ptr<const Object> object;
};

#endif // #ifndef __SHAPE_H_