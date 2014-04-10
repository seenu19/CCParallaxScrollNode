#ifndef _CCPARALLAX_SCROLL_OFFSET_H_
#define _CCPARALLAX_SCROLL_OFFSET_H_

#include "cocos2d.h"

namespace cocos2d {
    
    class CC_DLL CCParallaxScrollOffset : public CCObject
    {
    private:
        CCPoint scrollOffset, origPosition, relVelocity, ratio, position, currPosition;
        CCNode *child;
    public:
        ~CCParallaxScrollOffset();
        static CCParallaxScrollOffset * scrollWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s);
        static CCParallaxScrollOffset * scrollWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v);
        bool initWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s);
        bool initWithNode(CCNode *node, const CCPoint &r, const CCPoint &p, const CCPoint &s, const CCPoint &v);
        
        
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, scrollOffset, ScrollOffset);
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, origPosition, OrigPosition);
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, relVelocity, RelVelocity);
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, ratio, Ratio);
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, position, Position);
        //        CC_PROPERTY_PASS_BY_REF(CCPoint, currPosition, CurrPosition);
        //
        //        CC_PROPERTY(CCNode *, child, Child);
        
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, scrollOffset, ScrollOffset);
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, origPosition, OrigPosition);
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, relVelocity, RelVelocity);
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, ratio, Ratio);
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, position, Position);
        //        CC_SYNTHESIZE_PASS_BY_REF(CCPoint, currPosition, CurrPosition);
        //
        //        CC_SYNTHESIZE_PASS_BY_REF(CCNode *, child, Child);
        
        void setScrollOffset(const CCPoint &val);
        void setOrigPosition(const CCPoint &val);
        void setRelVelocity(const CCPoint &val);
        void setRatio(const CCPoint &val);
        void setPosition(const CCPoint &val);
        void setCurrPosition(const CCPoint &val);
        void setChild(CCNode *val);
        const CCPoint & getScrollOffset() const;
        const CCPoint & getOrigPosition() const;
        const CCPoint & getRelVelocity() const;
        const CCPoint & getRatio() const;
        const CCPoint & getPosition() const;
        const CCPoint & getCurrPosition() const;
        CCNode * getChild() const;
        
    };
    
} // namespace cocos2d
#endif //__CCPARALLAX_SCROLL_NODE_H__