//
//  Backend.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Backend_h
#define Backend_h

#include "Canvas.h"

class Backend {
    
private:
    Backend();
    static Backend *instance;
    
public:
    static Backend* getInstance();
    
public:
    void receive();
    
};

#endif /* Backend_h */
