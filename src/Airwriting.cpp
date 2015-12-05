//
//  Airwriting.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Frontend.h"
#include "Backend.h"
#include "Canvas.h"
#include "Task.h"
#include <iostream>
#include <thread>

int main() {
    Frontend *frontend = Frontend::getInstance();
    Backend *backend = Backend::getInstance();
    Canvas *canvas = Canvas::getInstance();
    Task *task = Task::getInstance();
    
    std::cout << "Press Enter to quit..." << std::endl;
    backend->start();
    std::thread thd(std::mem_fn(&Backend::listen), backend);
    frontend->start();
    std::cin.get();
    frontend->stop();
    backend->stop();
    thd.join();
    
    delete task;
    delete canvas;
    delete backend;
    delete frontend;
    return 0;
}
