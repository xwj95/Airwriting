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
#include <iostream>

int main() {
    Frontend *frontend = Frontend::getInstance();
    Backend *backend = Backend::getInstance();
    Canvas *canvas = Canvas::getInstance();
    canvas->setSize(200, 200);
    frontend->start();
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    frontend->stop();
    return 0;
}
