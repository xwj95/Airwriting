//
//  Task.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/12/4.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Task_h
#define Task_h

#include <queue>

class Task {
    
private:
    Task();
    static Task *instance;
    
public:
    ~Task();
    static Task* getInstance();
    
private:
    std::queue<float**> tasks;
    
public:
    unsigned long getSize();
    float** getTask();
    void pushTask();
    void popTask();
};

#endif /* Task_h */
