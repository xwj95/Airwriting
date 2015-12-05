//
//  Frontend.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Frontend_h
#define Frontend_h

#include "Leap.h"
#include "AirwritingListener.h"

using namespace Leap;

class Frontend {
    
private:
    Frontend();
    static Frontend *instance;
    
public:
    static Frontend* getInstance();
    
private:
    Controller controller;
    AirwritingListener listener;
    
public:
    void start();
    void stop();
};

#endif /* Frontend_h */
