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
    cvImage = cvCreateImage(cvSize(COMPRESS_M, COMPRESS_N), 8, 3);
    cvZero(cvImage);
    cvNamedWindow(title.data(), 0);
    cvMoveWindow(title.data(), CHARACTER_WINDOW_X, CHARACTER_WINDOW_Y);
}

Task::~Task() {
    while (!tasks.empty()) {
        popTask();
    }
    cvReleaseImage(&cvImage);
    cvDestroyAllWindows();
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

double** Task::getTask(unsigned int m, unsigned int n) {
    if (!tasks.empty()) {
        return compress(tasks.front(), m, n);
    }
    return NULL;
}

void Task::pushTask() {
    double **canvas = Canvas::getInstance()->getCanvas();
    int m = Canvas::getInstance()->getm();
    int n = Canvas::getInstance()->getn();
    double **image = new double*[m];
    for (int i = 0; i < m; ++i) {
        image[i] = new double[n];
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
    double **image = tasks.front();
    tasks.pop();
    if (!image) {
        return;
    }
    for (int i = 0; i < Canvas::getInstance()->getm(); ++i) {
        delete image[i];
    }
    delete image;
}

double** Task::compress(double **image, unsigned int m, unsigned int n) {
    double **image_compressed = new double*[m];
    for (int i = 0; i < m; ++i) {
        image_compressed[i] = new double[n];
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
                    double value = image[i * m_pooling + p][j * n_pooling + q];
                    if ((value == value) && (value > image_compressed[i][j])) {
                        image_compressed[i][j] += image[i * m_pooling + p][j * n_pooling + q];
                    }
                }
            }
            image_compressed[i][j] = image_compressed[i][j];
        }
    }
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (image_compressed[i][j] < 1e-7) {
                image_compressed[i][j] = 0;
            }
            if (image_compressed[i][j] > 1 - 1e-7) {
                image_compressed[i][j] = 1;
            }
            cvSet2D(cvImage, i, j, CV_RGB(image_compressed[i][j] * 255, image_compressed[i][j] * 255, image_compressed[i][j] * 255));
        }
    }
    return image_compressed;
}

void Task::release(double **image, unsigned int m, unsigned int n) {
    for (int i = 0; i < m; ++i) {
        delete image[i];
    }
    delete image;
}

void Task::show() {
    while (displaying) {
        cvShowImage(title.data(), cvImage);
        cvWaitKey(10);
    }
}

void Task::start() {
    displaying = true;
}

void Task::stop() {
    displaying = false;
}
