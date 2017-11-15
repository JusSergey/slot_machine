#include "MachineDisplay.h"
#include "Paths.h"

USING_NS_CC;

bool MachineDisplay::init() {

    if (!Sprite::initWithFile(PATH_TO_MACHINE_DISPLAY))
        return false;

    return true;
}

void MachineDisplay::spinIcons()
{

}

void MachineDisplay::initIcons()
{

}
