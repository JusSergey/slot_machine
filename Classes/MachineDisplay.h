#ifndef __MACHINE_DISPLAY_H__
#define __MACHINE_DISPLAY_H__

#include "cocos2d.h"
#include "Icon.h"
#include <list>
#include <vector>

static constexpr auto W = 4;
static constexpr auto H = 3;
static constexpr auto countRows = 42;

using Callback = std::function<void()>;
using IconVector2D = std::vector<std::vector<Icon *>>;
using MatchLinesVector = std::vector<int>;

class MachineDisplay : public cocos2d::Sprite
{
    bool _orderToStartSpin = true;
    cocos2d::DrawNode *_drawNodePrimitives;
public:
    virtual bool init();

    CREATE_FUNC(MachineDisplay)

    bool spinIcons();
    void setCallbackDidSpinFinish(const std::function<void ()> &value);

private:
    void initDrawNode();
    void addIconsForSpin();
    void applyAnimationToIcons(const Callback &callfunc);
    void showMatches();
    void showMatchLine(int indexLine);
    IconVector2D selectViewIcons();
    MatchLinesVector searchMatches();

private:
    void initIcons();
    void pushIconsForStart();
    void preloadResourceForIcons();
    Icon *createAndAddToChildren(int x, int y);
    cocos2d::Vec2 getPositionForCell(int x, int y) const;

private:
    std::vector<std::list<Icon *>> _allIcons;
    std::function<void()> _callbackDidSpinFinish = []{};

};

#endif // __MACHINE_DISPLAY_H__
