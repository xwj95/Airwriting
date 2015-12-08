//
//  Backend.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Backend.h"
#include "Task.h"
#include <iostream>

Backend *Backend::instance = new Backend();

Backend::Backend() {
    m = BACKEND_M;
    n = BACKEND_N;
}

Backend* Backend::getInstance() {
    if (!instance) {
        instance = new Backend();
    }
    return instance;
}

void Backend::analyse(float **image) {
/*    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << image[i][j] << ' ';
        std::cout << std::endl;
    }*/
}

void Backend::listen() {
    Task *tasks = Task::getInstance();
//    unsigned int count = 0;
    while (listening) {
        if (tasks->getSize()) {
//            std::cout << "Receive frame " << count++ << "." << std::endl;
            float **image = tasks->getTask(m, n);
            tasks->popTask();
            analyse(image);
            tasks->release(image, m, n);
        }
    }
}

void Backend::start() {
    listening = true;
}

void Backend::stop() {
    listening = false;
}
