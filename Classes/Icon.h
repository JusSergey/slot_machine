#ifndef __ICON_H__
#define __ICON_H__

#include "cocos2d.h"

enum class TypeIcon : int { UNDEFINED = 0, BOMB, CHERRY, COIN, SEVEN};


class Icon : public cocos2d::Sprite
{
    cocos2d::TextureCache *_texCache = nullptr;
public:
    virtual bool init();
    CREATE_FUNC(Icon)
    static Icon* create(TypeIcon type);
    static Icon *createRandomIcon();
    inline TypeIcon getType() const { return _type; }

private:
    TypeIcon _type = TypeIcon::UNDEFINED;

public:
    static std::string getPathToIcon(TypeIcon type);
};



#endif // __ICON_H__
