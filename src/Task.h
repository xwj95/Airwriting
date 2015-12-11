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
#include <string>
#include "opencv/highgui.h"
#include "opencv/cv.h"

#define COMPRESS_M 28
#define COMPRESS_N 28
#define CHARACTER_WINDOW_X 100
#define CHARACTER_WINDOW_Y 100

class Task {
    
private:
    Task();
    static Task *instance;
    
public:
    ~Task();
    static Task* getInstance();
    
private:
    std::queue<double**> tasks;
    
public:
    unsigned long getSize();
    double** getTask(unsigned int m, unsigned int n);
    void pushTask();
    void popTask();
    
    double** compress(double **image, unsigned int m, unsigned int n);
    void release(double **image, unsigned int m, unsigned int n);
    
private:
    IplImage *cvImage;
    bool displaying;
    std::string title = "Character";
    
public:
    void show();
    void start();
    void stop();
};

#endif /* Task_h */
