#ifndef __MACHINE_DISPLAY_H__
#define __MACHINE_DISPLAY_H__

#include "cocos2d.h"

class MachineDisplay : public cocos2d::Sprite
{
public:
    virtual bool init();

    CREATE_FUNC(MachineDisplay)

    void spinIcons();

private:
    void initIcons();

};

#endif // __MACHINE_DISPLAY_H__
