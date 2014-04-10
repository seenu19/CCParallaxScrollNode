#ifndef _CCPARALLAX_SCROLL_NODE_H_
#define _CCPARALLAX_SCROLL_NODE_H_

#include "cocos2d.h"
//#include "CCParallaxScrollOffset.h"

namespace cocos2d {
    
    class CC_DLL CCParallaxScrollNode : public CCNode
    {
    private:
        ccArray *scrollOffsets;
        CCSpriteBatchNode *batch;
        bool init();
    public:
        ~CCParallaxScrollNode();
        //static CCParallaxScrollNode * node();
        static CCParallaxScrollNode * makeWithBatchFile(const char *batchFileName);
        void addChild(CCSprite *node, int z, const CCPoint &r, const CCPoint &p, const CCPoint &s);
        void addChild(CCSprite *node, int z, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v);
        
        void addChild(CCNode *node, int z);
        
        void removeChild(CCSprite *node, bool cleanup);
        void removeAllChildrenWithCleanup(bool cleanup);
        void updateWithVelocity(const CCPoint &vel, float dt);
        void updateWithYPosition(float y, float dt);
        void addInfiniteScrollWithZ(int z, const CCPoint ratio , const CCPoint &pos, const CCPoint &dir, CCSprite *firstObject, ...);
        void addInfiniteScrollXWithZ(int z, const CCPoint ratio, const CCPoint &pos, CCSprite *firstObject, ...);
        void addInfiniteScrollYWithZ(int z, const CCPoint ratio, const CCPoint &pos, CCSprite *firstObject, ...);
        void addInfiniteScrollWithObjects(CCArray *objects, int z, const CCPoint ratio , const CCPoint &pos, const CCPoint &dir);
        
        void setScrollOffsets(ccArray *pScrollOffsets);
        void setBatch(CCSpriteBatchNode *pBatch);
        ccArray * getScrollOffsets();
        CCSpriteBatchNode * getBatch();
        
        //CC_SYNTHESIZE(ccArray *, scrollOffsets, ScrollOffsets);
        //CC_SYNTHESIZE(CCSpriteBatchNode *, batch, Batch)
        
        CREATE_FUNC (CCParallaxScrollNode);//какая-то хрень
    };
    
} // namespace cocos2d
#endif //__CCPARALLAX_SCROLL_NODE_H__