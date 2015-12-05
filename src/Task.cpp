//
//  Task.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/12/4.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Task.h"
#include "Canvas.h"

Task *Task::instance = new Task();

Task::Task() {
}

Task::~Task() {
    while (!tasks.empty()) {
        popTask();
    }
}

Task* Task::getInstance() {
    if (!instance) {
        instance = new Task();
    }
    return instance;
}

unsigned long Task::getSize() {
    return tasks.size();
}

float** Task::getTask() {
    if (!tasks.empty()) {
        return tasks.front();
    }
    return NULL;
}

void Task::pushTask() {
    float **canvas = Canvas::getInstance()->getCanvas();
    int m = Canvas::getInstance()->getm();
    int n = Canvas::getInstance()->getn();
    float **image = new float*[m];
    for (int i = 0; i < m; ++i) {
        image[i] = new float[n];
        for (int j = 0; i < n; ++j) {
            image[i][j] = canvas[i][j];
        }
    }
    tasks.push(image);
    Canvas::getInstance()->clear();
}

void Task::popTask() {
    if (tasks.empty()) {
        return;
    }
    float **image = tasks.front();
    tasks.pop();
    if (!image) {
        return;
    }
    for (int i = 0; i < Canvas::getInstance()->getm(); ++i) {
        delete image[i];
    }
    delete image;
}
