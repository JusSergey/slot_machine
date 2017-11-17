#ifndef __HELPER_H__
#define __HELPER_H__

#include "cocos2d.h"

cocos2d::Vec2 getPoint(float x, float y);
cocos2d::Vec2 getPoint(const cocos2d::Vec2 &pos);
cocos2d::Vec2 getPointWithSize(float x, float y, const cocos2d::Size &size);
cocos2d::Vec2 sizeToVec2(const cocos2d::Size &sz);
cocos2d::Vec2 operator * (const cocos2d::Vec2 &v1, const cocos2d::Vec2 &v2);

#endif // __HELPER_H__
