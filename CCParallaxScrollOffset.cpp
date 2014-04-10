#include "CCParallaxScrollOffset.h"

namespace cocos2d {
    
    CCParallaxScrollOffset::~CCParallaxScrollOffset()
    {
        
    }
    
    CCParallaxScrollOffset * CCParallaxScrollOffset::scrollWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s)
    {
        CCParallaxScrollOffset *pobSprite = new CCParallaxScrollOffset();
        if (pobSprite && pobSprite->initWithNode(node, r, p, s))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    }
    
    CCParallaxScrollOffset * CCParallaxScrollOffset::scrollWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v)
    {
        CCParallaxScrollOffset *pobSprite = new CCParallaxScrollOffset();
        if (pobSprite && pobSprite->initWithNode(node, r, p, s, v))
        {
            pobSprite->autorelease();
            return pobSprite;
        }
        CC_SAFE_DELETE(pobSprite);
        return NULL;
    }
    
    bool CCParallaxScrollOffset::initWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s)
    {
        return initWithNode(node, r, p, s, ccp(0,0));
    }
    
    bool CCParallaxScrollOffset::initWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v)
    {
        bool ret = true;
        
        if(ret) {
            child = node;
            ratio = r;
            scrollOffset = s;
            relVelocity = v;
            child->setPosition(p);
            origPosition = p;
            //currPosition = p;
            child->setAnchorPoint(ccp(0, 0));
        }
        return ret;
    }
    
    void CCParallaxScrollOffset::setScrollOffset(const CCPoint &val)
    {
        scrollOffset = val;
    }
    
    void CCParallaxScrollOffset::setOrigPosition(const CCPoint &val)
    {
        origPosition = val;
    }
    
    void CCParallaxScrollOffset::setRelVelocity(const CCPoint &val)
    {
        relVelocity = val;
    }
    
    void CCParallaxScrollOffset::setRatio(const CCPoint &val)
    {
        ratio = val;
    }
    
    void CCParallaxScrollOffset::setPosition(const CCPoint &val)
    {
        position = val;
    }
    
    void CCParallaxScrollOffset::setCurrPosition(const CCPoint &val)
    {
        currPosition = val;
    }
    
    void CCParallaxScrollOffset::setChild(CCNode *val)
    {
        child = val;
    }
    
    const CCPoint & CCParallaxScrollOffset::getScrollOffset() const
    {
        return scrollOffset;
    }
    
    const CCPoint & CCParallaxScrollOffset::getOrigPosition() const
    {
        return origPosition;
    }
    
    const CCPoint & CCParallaxScrollOffset::getRelVelocity() const
    {
        return relVelocity;
    }
    
    const CCPoint & CCParallaxScrollOffset::getRatio() const
    {
        return ratio;
    }
    
    const CCPoint & CCParallaxScrollOffset::getPosition() const
    {
        return position;
    }
    
    const CCPoint & CCParallaxScrollOffset::getCurrPosition() const
    {
        return currPosition;
    }
    
    CCNode * CCParallaxScrollOffset::getChild() const
    {
        return child;
    }
    
}// namespace cocos2d