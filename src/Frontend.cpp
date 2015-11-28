//
//  Frontend.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Frontend.h"
#include <iostream>
#include <string>

Frontend *Frontend::instance = new Frontend();

Frontend::Frontend() {
    controller = Controller();
    listener = AirwritingListener();
}

Frontend* Frontend::getInstance() {
    if (!instance) {
        instance = new Frontend();
    }
    return instance;
}

void Frontend::start() {
    controller.addListener(listener);
}

void Frontend::stop() {
    controller.removeListener(listener);
}
