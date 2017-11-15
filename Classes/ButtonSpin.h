#ifndef __BUTTON_SPIN_H__
#define __BUTTON_SPIN_H__

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

class ButtonSpin : public cocos2d::ui::Button
{
public:
    virtual bool init();

    CREATE_FUNC(ButtonSpin)

private:
    void initText();

};

#endif // __BUTTON_SPIN_H__
