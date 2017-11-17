#include "MachineDisplay.h"
#include "Paths.h"
#include "Helper.h"

USING_NS_CC;

bool MachineDisplay::init() {

    if (!Sprite::initWithFile(PATH_TO_MACHINE_DISPLAY))
        return false;

    preloadResourceForIcons();
    pushIconsForStart();
    initDrawNode();

    return true;
}

bool MachineDisplay::spinIcons()
{
    if (!_orderToStartSpin)
        return false;

    _drawNodePrimitives->clear();

    addIconsForSpin();
    applyAnimationToIcons([this] {
        _orderToStartSpin = true;
        showMatches();
        _callbackDidSpinFinish();
    });

    _orderToStartSpin = false;
    return true;

}

void MachineDisplay::initDrawNode()
{
    _drawNodePrimitives = DrawNode::create(Director::getInstance()->getVisibleSize().width * 0.005);
    _drawNodePrimitives->setPosition(Vec2::ZERO);
    addChild(_drawNodePrimitives, 1);
}

void MachineDisplay::addIconsForSpin()
{
    for (int i = H + 1; i < countRows + H + 1; ++i)
        for (int j = 0; j < W; ++j)
            _allIcons[j].push_back(createAndAddToChildren(j, i));
}

void MachineDisplay::applyAnimationToIcons(const Callback &callfunc)
{
    const float distanceBetweenCells = getPositionForCell(0, 1).y - getPositionForCell(0, 0).y;

    float timeForSpin = 3;

    for (auto &column : _allIcons) {

        int index = 0;
        timeForSpin += 2;

        for (auto icon : column) {
            auto baseAction = MoveBy::create(timeForSpin, Vec2(0, -distanceBetweenCells * (countRows)));
            auto smoothAction = EaseOut::create(baseAction, 6);

            // останні, що видимі на екрані не мають видалятися із гри
            if (index > countRows-1) {
                icon->runAction(smoothAction);
            }
            else {
                auto callbackDelete = CallFunc::create([=]{ icon->removeFromParent(); });
                auto smoothAndDeleteDidFinish = Sequence::create(smoothAction, callbackDelete, nullptr);
                icon->runAction(smoothAndDeleteDidFinish);
            }
            ++index;
        }
        // видалення із списку усіх кого не видно
        auto e = column.end();
        std::advance(e, -H-2);
        column.erase(column.begin(), e);
    }

    // після того, як усі зупинилися, дозволити запустити знову
    scheduleOnce([callfunc](float){
        callfunc();
    }, timeForSpin, "setOrder");
}

void MachineDisplay::showMatches()
{
    {
        // print dump
        std::string line;
        for (const auto &v : selectViewIcons()) {
            for (Icon *ic : v) {
                (line += ' ') += (char)(static_cast<int>(ic->getType()) + '0');
            }
            line += '\n';
        }

        cocos2d::log("dump:\n%s", line.c_str());
    }

    for (auto i : searchMatches())
        showMatchLine(i);

}

void MachineDisplay::showMatchLine(int indexLine)
{
    Vec2 p1 = getPositionForCell(0,   indexLine),
         p2 = getPositionForCell(W-1, indexLine);

    _drawNodePrimitives->drawLine(p1, p2, Color4F(1.f, 0.f, 0.f, 0.5f));

    auto vv = selectViewIcons();
    for (int i = 0; i < W; ++i) {
        auto in  = ScaleTo::create(0.15f, 1.3f);
        auto out = ScaleTo::create(0.15f, 1.0f);
        auto del = DelayTime::create(0.05f * i);
        auto seq = Sequence::create(del, in, out, nullptr);
        vv[indexLine][i]->runAction(seq);
    }
}

IconVector2D MachineDisplay::selectViewIcons()
{
    IconVector2D vvResult;
    vvResult.resize(H);
    for (auto &v : vvResult)
        v.resize(W);

    int i = 0;

    for (const auto &row : _allIcons) {

        auto endIter   = row.end();   --endIter;
        auto beginIter = row.begin(); ++beginIter;
        int j = 0;

        for (auto iter = beginIter; iter != endIter; ++iter) {

            vvResult[j][i] = *iter;

            ++j;
        }

        ++i;
    }

    return vvResult;

}

MatchLinesVector MachineDisplay::searchMatches()
{
    auto isAllEqual = [](const IconVector2D::value_type &vecline) -> bool {
        if (vecline.empty())
            return true;

        auto first = vecline[0]->getType();
        for (int i = 1; i < vecline.size(); ++i)
            if (vecline[i]->getType() != first)
                return false;

        return true;
    };

    MatchLinesVector resultLines;

    auto vec2D = selectViewIcons();

    for (int i = 0; i < vec2D.size(); ++i) {
        if (isAllEqual(vec2D[i])) {
            resultLines.push_back(i);
        }
    }

    return resultLines;
}

void MachineDisplay::initIcons()
{

}

void MachineDisplay::pushIconsForStart()
{
    _allIcons.resize(W);

    for (int i = -1; i < H+1; ++i)
        for (int j = 0; j < W; ++j)
            _allIcons[j].push_back(createAndAddToChildren(j, i));

}

void MachineDisplay::preloadResourceForIcons()
{
    auto textureCache = Director::getInstance()->getTextureCache();

    for (auto i : {TypeIcon::BOMB,
                   TypeIcon::CHERRY,
                   TypeIcon::COIN,
                   TypeIcon::SEVEN})
    {
        textureCache->addImage(Icon::getPathToIcon(i));
    }
}

Icon *MachineDisplay::createAndAddToChildren(int x, int y)
{
    Icon *icon = Icon::createRandomIcon();

    icon->setPosition(getPositionForCell(x, y));
    addChild(icon);

    return icon;
}

Vec2 MachineDisplay::getPositionForCell(int x, int y) const
{
    const  Size content = getContentSize();
    return Vec2(content.width / (W+1) * (x+1),
                content.height/ (H+1) * (y+1));
}

void MachineDisplay::setCallbackDidSpinFinish(const std::function<void ()> &value)
{
    _callbackDidSpinFinish = value;
}
