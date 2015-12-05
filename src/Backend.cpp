//
//  Backend.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Backend.h"
#include "Canvas.h"
#include "Task.h"

Backend *Backend::instance = new Backend();

Backend::Backend() {
}

Backend* Backend::getInstance() {
    if (!instance) {
        instance = new Backend();
    }
    return instance;
}

void Backend::analyse(float **image, unsigned int m, unsigned int n) {
}

void Backend::listen() {
    Task *tasks = Task::getInstance();
    Canvas *canvas = Canvas::getInstance();
    while (listening) {
        if (tasks->getSize()) {
            analyse(tasks->getTask(), canvas->getm(), canvas->getn());
            tasks->popTask();
        }
    }
}

void Backend::start() {
    listening = true;
}

void Backend::stop() {
    listening = false;
}
