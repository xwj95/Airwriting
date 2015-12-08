//
//  AirwritingListener.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef AirwritingListener_h
#define AirwritingListener_h

#include "leap.h"

#define FINGER_INDEX 1
#define FINGER_X_MAX 50
#define FINGER_Z_MAX 50
#define FINGER_Y_MIN 10
#define FINGER_Y_MAX 300
#define GESTURE_TAP_MAX_TIMESTAMP_DELTA 80000

using namespace Leap;

class AirwritingListener : public Listener {
    
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
    virtual void onDeviceChange(const Controller&);
    virtual void onServiceConnect(const Controller&);
    virtual void onServiceDisconnect(const Controller&);
    AirwritingListener();
    ~AirwritingListener();
    
private:
    bool sampling;
    void sample(const Finger &finger);
    
    unsigned long long lastTimestamp;
    void push(unsigned long long timestamp);
    
};

#endif /* AirwritingListener_h */
