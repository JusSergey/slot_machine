#ifndef __ICON_FACTORY_H__
#define __ICON_FACTORY_H__

#include "Icon.h"

#include "cocos2d.h"


class IconFactory {
    bool _isFirst = true;
    static IconFactory *instance;
    IconFactory() = default;
public:
    static IconFactory *getInstance();

public:
    Icon *makeIcon(TypeIcon type);

private:
    void preloadIconToCache();
    std::string getPathToIcon(TypeIcon type) const;
};

#endif // __ICON_FACTORY_H__
