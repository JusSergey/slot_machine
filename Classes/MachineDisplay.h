#ifndef __MACHINE_DISPLAY_H__
#define __MACHINE_DISPLAY_H__

#include "cocos2d.h"
#include <list>

class MachineDisplay : public cocos2d::Sprite
{
public:
    virtual bool init();

    CREATE_FUNC(MachineDisplay)

    void spinIcons();

private:
    void initIcons();

private:
//    std::list<>

};

#endif // __MACHINE_DISPLAY_H__
