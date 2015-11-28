//
//  Backend.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Backend.h"

Backend *Backend::instance = new Backend();

Backend::Backend() {
}

Backend* Backend::getInstance() {
    if (!instance) {
        instance = new Backend();
    }
    return instance;
}

void Backend::receive() {
    Canvas *instance = Canvas::getInstance();
    float **canvas = instance->getCanvas();
    int m = instance->getm();
    int n = instance->getn();
    float image[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; i < n; ++j) {
            image[i][j] = canvas[i][j];
        }
    }
    instance->clear();
}
