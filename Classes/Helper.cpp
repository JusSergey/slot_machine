#include "Helper.h"

USING_NS_CC;

Vec2 getPoint(float x, float y)
{
    static const Size size(Director::getInstance()->getVisibleSize());
    return Vec2(size.width * x, size.height * y);
}

Vec2 getPoint(const Vec2 &pos)
{
    return getPoint(pos.x, pos.y);
}
