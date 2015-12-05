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
};

#endif /* Canvas_h */
