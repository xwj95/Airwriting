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

float** Task::getTask(unsigned int m, unsigned int n) {
    if (!tasks.empty()) {
        return compress(tasks.front(), m, n);
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
        for (int j = 0; j < n; ++j) {
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

float** Task::compress(float **image, unsigned int m, unsigned int n) {
    float **image_compressed = new float*[m];
    for (int i = 0; i < m; ++i) {
        image_compressed[i] = new float[n];
    }
    unsigned m_origin = Canvas::getInstance()->getm();
    unsigned n_origin = Canvas::getInstance()->getn();
    unsigned m_pooling = m_origin / m;
    unsigned n_pooling = n_origin / n;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            image_compressed[i][j] = 0;
            for (int p = 0; p < m_pooling; ++p) {
                for (int q = 0; q < n_pooling; ++q) {
                    float value = image[i * m_pooling + p][j * n_pooling + q];
                    if ((value == value) && (value > image_compressed[i][j])) {
                        image_compressed[i][j] = image[i * m_pooling + p][j * n_pooling + q];
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (image_compressed[i][j] < 0.1) {
                image_compressed[i][j] = 0;
            }
            if (image_compressed[i][j] > 0.1) {
                image_compressed[i][j] = 1;
            }
        }
    }
    return image_compressed;
}

void Task::release(float **image, unsigned int m, unsigned int n) {
    for (int i = 0; i < m; ++i) {
        delete image[i];
    }
    delete image;
}
