#include "Helper.h"

USING_NS_CC;

Vec2 getPoint(float x, float y)
{
    static const Size size(Director::getInstance()->getVisibleSize());
    return getPointWithSize(x, y, size);//Vec2(size.width * x, size.height * y);
}

Vec2 getPoint(const Vec2 &pos)
{
    return getPoint(pos.x, pos.y);
}

Vec2 getPointWithSize(float x, float y, const Size &size)
{
    return Vec2(size.width * x, size.height * y);
}

Vec2 sizeToVec2(const Size &sz)
{
    return Vec2(sz.width, sz.height);
}

Vec2 operator *(const Vec2 &v1, const Vec2 &v2) {
    return cocos2d::Vec2(v1.x * v2.x, v1.y * v2.y);
}
