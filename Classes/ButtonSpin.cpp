#include "ButtonSpin.h"
#include "Paths.h"

USING_NS_CC;

bool ButtonSpin::init()
{
    if (!Button::init(PATH_TO_BUTTON_SPIN))
        return false;

    initText();

    return true;
}

void ButtonSpin::initText()
{
    Label *label = Label::createWithTTF("SPIN", "fonts/arial.ttf", 48);
    label->setPosition(getContentSize() / 2);

    addChild(label);
}
