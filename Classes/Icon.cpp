#include "Icon.h"
#include "Paths.h"

USING_NS_CC;

bool Icon::init()
{
    if (!_texCache)
        _texCache = Director::getInstance()->getTextureCache();

    if (_type != TypeIcon::UNDEFINED ?
            !Sprite::initWithTexture(_texCache->getTextureForKey(getPathToIcon(_type))) :
            !Sprite::init())
    {
        return false;
    }

    return true;
}

Icon *Icon::create(TypeIcon type)
{
    Icon *pRet = new(std::nothrow) Icon();
    if (pRet)
        pRet->_type = type;

    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

Icon *Icon::createRandomIcon()
{
    static const std::vector<TypeIcon> types = {TypeIcon::BOMB,
                                                TypeIcon::CHERRY,
                                                TypeIcon::COIN,
                                                TypeIcon::SEVEN};

    return Icon::create(static_cast<TypeIcon>(cocos2d::random(1, (int)types.size())));
}

std::string Icon::getPathToIcon(TypeIcon type)
{
    return PREFIX_PATH_TO_ICONS + std::to_string(static_cast<int>(type)) + ".png";
}
