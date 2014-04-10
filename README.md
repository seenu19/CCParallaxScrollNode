CCParallaxScrollNode
====================

scroll background parallax for cocos2d-x 2.2.2.

tested with cocos2dx 2.2.2

stungyen created for cocos2dx 3.0 version. it having some issues in 2.2.2
https://github.com/stnguyen/CCParallaxScrollNode 

here, http://www.cocos2d-x.org/forums/6/topics/14096?r=38800 roko12 has given source for 2.2.2

 Usage:- 

Include the following files in your project

    CCParallaxScrollNode.h
    CCParallaxScrollNode.cpp
    CCParallaxScrollOffset.h
    CCParallaxScrollOffset.cpp

Use it in your class file..
     
    #include "CCParallaxScrollNode.h"

    pNode = CCParallaxScrollNode::create();

    CCSprite *bg1 = CCSprite::create("bg1.png");
    CCSprite *bg2 = CCSprite::create("bg2.png”);
    CCSprite *bg3 = CCSprite::create("bg3.png");

    pNode->addInfiniteScrollXWithZ(0, Point(0.5, 0.9), Point(0,0), bg1, bg2, bg3, NULL);
    this->addChild(pNode);

    // in update()
    pNode->updateWithVelocity(ccp(-100,0), delta);
