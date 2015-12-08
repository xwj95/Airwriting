//
//  Canvas.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Canvas.h"
#include "math.h"

Canvas *Canvas::instance = new Canvas();

Canvas::Canvas() {
    m = CANVAS_M;
    n = CANVAS_N;
    create();
    cvNamedWindow(title.data(), 0);
    cvMoveWindow(title.data(), WINDOW_X, WINDOW_Y);
}

Canvas::~Canvas() {
    destroy();
    cvDestroyAllWindows();
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
    
    image = cvCreateImage(cvSize(m, n), 8, 3);
    cvZero(image);
}

void Canvas::destroy() {
    if (!canvas) {
        return;
    }
    for (int i = 0; i < m; ++i) {
        delete canvas[i];
    }
    delete canvas;
    
    cvReleaseImage(&image);
}

void Canvas::clear() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            canvas[i][j] = 0;
        }
    }
    
    cvZero(image);
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

void Canvas::show() {
    while (displaying) {
        cvShowImage(title.data(), image);
        cvWaitKey(10);
    }
}

void Canvas::setPixel(unsigned int j, unsigned int i, float value) {
    if ((i >= m) || (j >= n)) {
        return;
    }
    canvas[i][j] += value;
    if (canvas[i][j] < 0) {
        canvas[i][j] = 0;
    }
    if (canvas[i][j] > 1) {
        canvas[i][j] = 1;
    }
    
    cvSet2D(image, i, j, CV_RGB(canvas[i][j] * 255, canvas[i][j] * 255, canvas[i][j] * 255));
}

void Canvas::setPixel(float x, float y, float value) {
    if (fabs(x) > 1 || fabs(y) > 1) {
        return;
    }
    x = (x + 1) / 2;
    y = (y + 1) / 2;
    unsigned int x1 = floor(x * m);
    unsigned int x2 = x1 + 1;
    unsigned int y1 = floor(y * n);
    unsigned int y2 = y1 + 1;
    float wx = x * m - x1;
    float wy = y * n - y1;
    setPixel(x1, y1, value * wx * wy);
    setPixel(x1, y2, value * wx * (1 - wy));
    setPixel(x2, y1, value * (1 - wx) * wy);
    setPixel(x2, y2, value * (1 - wx) * (1 - wy));
}

void Canvas::start() {
    displaying = true;
}

void Canvas::stop() {
    displaying = false;
}
