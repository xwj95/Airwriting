//
//  Canvas.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Canvas.h"

Canvas *Canvas::instance = new Canvas();

Canvas::Canvas() {
    m = 200;
    n = 200;
    create();
}

Canvas::~Canvas() {
    destroy();
}

Canvas* Canvas::getInstance() {
    if (!instance) {
        instance = new Canvas();
    }
    return instance;
}

void Canvas::create() {
    canvas = new float*[m];
    for (int i = 0; i < m; ++i) {
        canvas[i] = new float[n];
    }
}

void Canvas::destroy() {
    if (!canvas) {
        return;
    }
    for (int i = 0; i < m; ++i) {
        delete canvas[i];
    }
    delete canvas;
}

void Canvas::clear() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            canvas[i][j] = 0;
        }
    }
}

float** Canvas::getCanvas() {
    return canvas;
}

int Canvas::getm() {
    return m;
}

int Canvas::getn() {
    return n;
}

void Canvas::setPixel(unsigned int i, unsigned int j, float value) {
    canvas[i][j] = value;
}
