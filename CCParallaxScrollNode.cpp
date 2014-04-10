#include "CCParallaxScrollNode.h"
#include "CCParallaxScrollOffset.h"

#ifndef PTM_RATIO
#define PTM_RATIO 1//32
#endif

#ifndef SIGN
#define SIGN(x) ((x < 0) ? -1 : (x > 0))
#endif

#include "support/data_support/ccCArray.h"

namespace cocos2d {
    
    CCParallaxScrollNode::~CCParallaxScrollNode()
    {
        if (scrollOffsets) {
            ccArrayFree(scrollOffsets);
            scrollOffsets = 0;
        }
    }
    
    bool CCParallaxScrollNode::init()
    {
        bool ret = true;
        
        if (ret)
        {
            scrollOffsets = ccArrayNew(5);
        }
        
        return ret;
    }
    
    //  CCParallaxScrollNode * CCParallaxScrollNode::node()
    //  {
    //      CCParallaxScrollNode *pRet = new CCParallaxScrollNode();
    //      pRet->autorelease();
    //      return pRet;
    //  }
    
    CCParallaxScrollNode * CCParallaxScrollNode::makeWithBatchFile(const char *batchFileName)
    {
        CCParallaxScrollNode *parallax = CCParallaxScrollNode::create();
        
        char *pngName = (char*)malloc(sizeof(char)*(strlen(batchFileName)+5));
        
        strcpy(pngName, batchFileName);
        *(pngName+strlen(batchFileName)) = 0;
        
        parallax->setBatch(CCSpriteBatchNode::create (strcat(pngName, ".png")));
        
        free(pngName);
        
        ((CCNode*)parallax)->addChild(parallax->batch);
        
        pngName = (char*)malloc(sizeof(char)*(strlen(batchFileName)+7));
        
        strcpy(pngName, batchFileName);
        *(pngName+strlen(batchFileName)) = 0;
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(strcat(pngName, ".plist"));
        
        free(pngName);
        return parallax;
    }
    
    void CCParallaxScrollNode::updateWithVelocity(const CCPoint &vel, float dt) {
        CCSize screen = CCDirector::sharedDirector()->getWinSize();
        
        CCPoint vel2 = ccpMult(vel, PTM_RATIO);
        
        for (int i=scrollOffsets->num - 1; i >= 0; i--) {
            CCParallaxScrollOffset *scrollOffset = (CCParallaxScrollOffset*)scrollOffsets->arr[i];
            CCNode *child = scrollOffset->getChild();
            
            CCPoint relVel = ccpMult(scrollOffset->getRelVelocity(), PTM_RATIO);
            CCPoint totalVel = ccpAdd(vel2, relVel);
            CCPoint tmp = ccpMult(totalVel, dt);
            CCPoint offset = ccpCompMult(tmp, scrollOffset->getRatio());

            
            child->setPosition(ccpAdd(child->getPosition(), offset));
            
            if ( (vel2.x < 0 && child->getPosition().x + child->getContentSize().width < 0) ||
                (vel2.x > 0 && child->getPosition().x > screen.width) ) {
                
                child->setPosition(ccpAdd(child->getPosition(), ccp(-SIGN(vel2.x) * fabs(scrollOffset->getScrollOffset().x), 0)));
            }
            
            // Positive y indicates upward movement in cocos2d
            if ( (vel2.y < 0 && child->getPosition().y + child->getContentSize().height < 0) ||
                (vel2.y > 0 && child->getPosition().y > screen.height) ) {
                child->setPosition(ccpAdd(child->getPosition(), ccp(0, -SIGN(vel2.y) * fabs(scrollOffset->getScrollOffset().y))));
            }
        }
    }
    
    void CCParallaxScrollNode::updateWithYPosition(float y, float dt)
    {
        for (int i=scrollOffsets->num - 1; i >= 0; i--) {
            CCParallaxScrollOffset *scrollOffset = (CCParallaxScrollOffset*)scrollOffsets->arr[i];
            CCNode *child = scrollOffset->getChild();
            float offset = y * scrollOffset->getRatio().y;//ccpCompMult(pos, scrollOffset.ratio);
            child->setPosition(ccp(child->getPosition().x, scrollOffset->getOrigPosition().y + offset));
        }
    }
    
    void CCParallaxScrollNode::addChild(CCSprite *node, int z, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v)
    {
        node->setAnchorPoint(ccp(0,0));
        CCParallaxScrollOffset *obj = CCParallaxScrollOffset::scrollWithNode(node, r, p, s, v);
        ccArrayAppendObjectWithResize(scrollOffsets, obj);
        if (batch) {
            batch->addChild(node, z);
        } else {
            ((CCNode*)this)->addChild(node, z);
        }
    }
    
    void CCParallaxScrollNode::addChild(CCSprite *node, int z, const CCPoint &r, const CCPoint &p, const CCPoint &s)
    {
        addChild(node, z, r, p, s, ccp(0,0));
    }
    
    void CCParallaxScrollNode::removeChild(CCSprite *node, bool cleanup)
    {
        for (int i=0; i < scrollOffsets->num; i++) {
            CCParallaxScrollOffset *scrollOffset = (CCParallaxScrollOffset*)scrollOffsets->arr[i];
            if(scrollOffset->getChild()->isEqual(node)) {
                ccArrayRemoveObjectAtIndex(scrollOffsets, i);
                break;
            }
        }
        if (batch) {
            batch->removeChild(node, cleanup);
        }
    }
    
    void CCParallaxScrollNode::addChild(CCNode *node, int z)
    {
        CCNode::addChild(node, z);
    }
    
    void CCParallaxScrollNode::removeAllChildrenWithCleanup(bool cleanup)
    {
        ccArrayRemoveAllObjects(scrollOffsets);
        if (batch) {
            batch->removeAllChildrenWithCleanup(cleanup);
        }
    }
    
    void CCParallaxScrollNode::addInfiniteScrollWithObjects(CCArray *objects, int z, const CCPoint ratio, const CCPoint &pos, const CCPoint &dir)
    {
        // NOTE: corrects for 1 pixel at end of each sprite to avoid thin lines appearing
        
        // Calculate total width and height
        float totalWidth = 0;
        float totalHeight = 0;
        for (int i = 0; i < objects->count(); i++) {
            CCSprite *object = (CCSprite *)(objects->objectAtIndex(i));
            totalWidth += object->getContentSize().width - 2;//1;
            totalHeight += object->getContentSize().height - 2;//1;
        }
        
        // Position objects, add to parallax
        CCPoint currPos = pos;
        for (int i = 0; i < objects->count(); i++) {
            CCSprite *object = (CCSprite *)(objects->objectAtIndex(i));
            addChild(object, z, ratio, currPos, ccp(totalWidth, totalHeight));
            CCPoint nextPosOffset = ccp(dir.x * (object->getContentSize().width - 2/*1*/), dir.y * (object->getContentSize().height - 2/*1*/));
            currPos = ccpAdd(currPos, nextPosOffset);
        }
    }
    
    void CCParallaxScrollNode::addInfiniteScrollWithZ(int z, const CCPoint ratio, const CCPoint &pos, const CCPoint &dir, CCSprite *firstObject, ...)
    {
        va_list args;
        va_start(args, firstObject);
        
        CCArray* argArray = CCArray::createWithCapacity(2);
        for (CCSprite *arg = firstObject; arg != 0; arg = va_arg(args, CCSprite*)) {
            argArray->addObject(arg);
        }
        va_end(args);
        
        addInfiniteScrollWithObjects(argArray, z, ratio, pos, dir);
    }
    
    void CCParallaxScrollNode::addInfiniteScrollXWithZ(int z, const CCPoint ratio, const CCPoint &pos, CCSprite *firstObject, ...)
    {
        va_list args;
        va_start(args, firstObject);
        
        CCArray* argArray = CCArray::createWithCapacity(2);
        for (CCSprite *arg = firstObject; arg != 0; arg = va_arg(args, CCSprite*)) {
            argArray->addObject(arg);
        }
        va_end(args);
        
        addInfiniteScrollWithObjects(argArray, z, ratio, pos, ccp(1, 0));
    }
    
    void CCParallaxScrollNode::addInfiniteScrollYWithZ(int z, const CCPoint ratio, const CCPoint &pos, CCSprite *firstObject, ...)
    {
        va_list args;
        va_start(args, firstObject);
        
        CCArray* argArray = CCArray::createWithCapacity(2);
        for (CCSprite *arg = firstObject; arg != 0; arg = va_arg(args, CCSprite*)) {
            argArray->addObject(arg);
        }
        va_end(args);
        
        addInfiniteScrollWithObjects(argArray, z, ratio, pos, ccp(0, 1));
    }
    
    void CCParallaxScrollNode::setScrollOffsets(ccArray *pScrollOffsets)
    {
        scrollOffsets = pScrollOffsets;
    }
    
    void CCParallaxScrollNode::setBatch(CCSpriteBatchNode *pBatch)
    {
        batch = pBatch;
    }
    
    ccArray * CCParallaxScrollNode::getScrollOffsets()
    {
        return scrollOffsets;
    }
    
    CCSpriteBatchNode * CCParallaxScrollNode::getBatch()
    {
        return batch;
    }
    
}// namespace cocos2d