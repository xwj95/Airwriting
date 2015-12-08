//
//  Canvas.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

#include "opencv/highgui.h"
#include "opencv/cv.h"

#define CANVAS_M 336
#define CANVAS_N 336
#define WINDOW_X 224
#define WINDOW_Y 224

class Canvas {
    
private:
    Canvas();
    void create();
    void destroy();
    static Canvas *instance;
    
public:
    ~Canvas();
    static Canvas* getInstance();
    
private:
    float **canvas;
    unsigned int m, n;

public:
    void clear();
    float** getCanvas();
    int getm();
    int getn();
    
    void setPixel(unsigned int i, unsigned int j, float value);
    void setPixel(float i, float j, float value);
    
private:
    IplImage *image;
    bool displaying;
    const std::string title = "Airwrite";
    
public:
    void show();
    void start();
    void stop();
};

#endif /* Canvas_h */
