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
    if ((m <= 0) || (n <= 0)) {
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

void Canvas::setSize(int m, int n) {
    destroy();
    if (m < 1) {
        m = 200;
    }
    if (n < 1) {
        n = 200;
    }
    this->m = m;
    this->n = n;
    create();
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

void Canvas::setPixel(int i, int j, float value) {
    canvas[i][j] = value;
}
