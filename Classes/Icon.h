#ifndef __ICON_H__
#define __ICON_H__

#include "cocos2d.h"

enum class TypeIcon : int { BOMB = 1, CHERRY, COIN, SEVEN};


class Icon : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(Icon)

public:
    TypeIcon _type;
};



#endif // __ICON_H__
