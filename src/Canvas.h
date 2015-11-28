//
//  Canvas.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

class Canvas {
    
private:
    Canvas();
    ~Canvas();
    void create();
    void destroy();
    static Canvas *instance;
    
public:
    static Canvas* getInstance();
    
private:
    float **canvas;
    int m, n;

public:
    void clear();
    void setSize(int m, int n);
    float** getCanvas();
    int getm();
    int getn();
    
    void setPixel(int i, int j, float value);
};

#endif /* Canvas_h */
