//
//  Backend.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Backend_h
#define Backend_h

class Backend {
    
private:
    Backend();
    static Backend *instance;
    
public:
    static Backend* getInstance();
    
private:
    bool listening;
    void analyse(float **image, unsigned int m, unsigned int n);
    
public:
    void listen();
    void start();
    void stop();
};

#endif /* Backend_h */
