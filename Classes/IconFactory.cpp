#include "IconFactory.h"

USING_NS_CC;
using std::string;



IconFactory *IconFactory::instance = nullptr;

IconFactory *IconFactory::getInstance()
{
    if (!IconFactory::instance)
        IconFactory::instance = new IconFactory();

    return IconFactory::instance;
}

Icon *IconFactory::makeIcon(TypeIcon type)
{
    if (_isFirst) {
        preloadIconToCache();
        _isFirst = false;
    }

    Icon *icon = Icon::create();
    icon->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(getPathToIcon(type)));
    icon->_type = type;

    return icon;
}

void IconFactory::preloadIconToCache()
{
    auto textureCache = Director::getInstance()->getTextureCache();

    for (auto i : {TypeIcon::BOMB,
                   TypeIcon::CHERRY,
                   TypeIcon::COIN,
                   TypeIcon::SEVEN})
    {
        textureCache->addImage(getPathToIcon(i));
    }

}

std::string IconFactory::getPathToIcon(TypeIcon type) const
{
    return string("icons/") + std::to_string(static_cast<int>(type));
}

