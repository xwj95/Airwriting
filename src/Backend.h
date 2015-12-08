//
//  Backend.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Backend_h
#define Backend_h

#define BACKEND_M 28
#define BACKEND_N 28

class Backend {
    
private:
    Backend();
    static Backend *instance;
    
public:
    static Backend* getInstance();
    
private:
    unsigned int m, n;
    bool listening;
    void analyse(float **image);
    
public:
    void listen();
    void start();
    void stop();
};

#endif /* Backend_h */
