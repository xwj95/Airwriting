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
#define CANVAS_WINDOW_X 100
#define CANVAS_WINDOW_Y 300

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
    double **canvas;
    unsigned int m, n;

public:
    void clear();
    double** getCanvas();
    int getm();
    int getn();
    
    void setPixel(unsigned int i, unsigned int j, double value);
    void setPixel(double y, double x, double value);
    
private:
    IplImage *cvImage;
    bool displaying;
    const std::string title = "Airwrite";
    
public:
    void show();
    void start();
    void stop();
};

#endif /* Canvas_h */
