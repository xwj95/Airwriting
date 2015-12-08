//
//  AirwritingListener.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "AirwritingListener.h"
#include "Canvas.h"
#include "Task.h"

const std::string fingerNames[] = {"Thumb", "Index", "Middle", "Ring", "Pinky"};
const std::string boneNames[] = {"Metacarpal", "Proximal", "Middle", "Distal"};
const std::string stateNames[] = {"STATE_INVALID", "STATE_START", "STATE_UPDATE", "STATE_END"};

void AirwritingListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void AirwritingListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void AirwritingListener::onDisconnect(const Controller& controller) {
    // Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void AirwritingListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

void AirwritingListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    unsigned long long timestamp = frame.timestamp();
    
    /*
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << frame.hands().count()
    << ", extended fingers: " << frame.fingers().extended().count()
    << ", tools: " << frame.tools().count()
    << ", gestures: " << frame.gestures().count() << std::endl;
    */

    
    HandList hands = frame.hands();
    for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
        // Get the first hand
        const Hand hand = *hl;
        std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
        
        /*
        std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
        << ", palm position: " << hand.palmPosition() << std::endl;
        */
        
        /*
        // Get the hand's normal vector and direction
        const Vector normal = hand.palmNormal();
        const Vector direction = hand.direction();
        */
        
        /*
        // Calculate the hand's pitch, roll, and yaw angles
        std::cout << std::string(2, ' ') <<  "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
        << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
        << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
        */
        
        /*
        // Get the Arm bone
        Arm arm = hand.arm();
        std::cout << std::string(2, ' ') <<  "Arm direction: " << arm.direction()
        << " wrist position: " << arm.wristPosition()
        << " elbow position: " << arm.elbowPosition() << std::endl;
        */
        
        // Get fingers
        const FingerList fingers = hand.fingers();
        for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
            const Finger finger = *fl;
            sample(finger);
            
            /*
            std::cout << std::string(4, ' ') <<  fingerNames[finger.type()]
            << " finger, id: " << finger.id()
            << ", length: " << finger.length()
            << "mm, width: " << finger.width() << std::endl;
            */
            
            /*
            // Get finger bones
            for (int b = 0; b < 4; ++b) {
                Bone::Type boneType = static_cast<Bone::Type>(b);
                Bone bone = finger.bone(boneType);
                std::cout << std::string(6, ' ') <<  boneNames[boneType]
                << " bone, start: " << bone.prevJoint()
                << ", end: " << bone.nextJoint()
                << ", direction: " << bone.direction() << std::endl;
            }
            */
        }
    }
    
    
    /*
    // Get tools
    const ToolList tools = frame.tools();
    for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
        const Tool tool = *tl;
        std::cout << std::string(2, ' ') <<  "Tool, id: " << tool.id()
        << ", position: " << tool.tipPosition()
        << ", direction: " << tool.direction() << std::endl;
    }
    */
    

    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
        Gesture gesture = gestures[g];
        
        switch (gesture.type()) {
            case Gesture::TYPE_CIRCLE:
            {
                CircleGesture circle = gesture;
                std::string clockwiseness;
                
                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/2) {
                    clockwiseness = "clockwise";
                } else {
                    clockwiseness = "counterclockwise";
                }
                
                // Calculate angle swept since last frame
                float sweptAngle = 0;
                if (circle.state() != Gesture::STATE_START) {
                    CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
                    sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
                }
                /*
                std::cout << std::string(2, ' ')
                << "Circle id: " << gesture.id()
                << ", state: " << stateNames[gesture.state()]
                << ", progress: " << circle.progress()
                << ", radius: " << circle.radius()
                << ", angle " << sweptAngle * RAD_TO_DEG
                <<  ", " << clockwiseness << std::endl;
                */
                break;
            }
            case Gesture::TYPE_SWIPE:
            {
                SwipeGesture swipe = gesture;
                /*
                std::cout << std::string(2, ' ')
                << "Swipe id: " << gesture.id()
                << ", state: " << stateNames[gesture.state()]
                << ", direction: " << swipe.direction()
                << ", speed: " << swipe.speed() << std::endl;
                */
                break;
            }
            case Gesture::TYPE_KEY_TAP:
            {
                KeyTapGesture tap = gesture;
                push(timestamp);
                /*
                std::cout << std::string(2, ' ')
                << "Key Tap id: " << gesture.id()
                << ", state: " << stateNames[gesture.state()]
                << ", position: " << tap.position()
                << ", direction: " << tap.direction()<< std::endl;
                */
                break;
            }
            case Gesture::TYPE_SCREEN_TAP:
            {
                ScreenTapGesture screentap = gesture;
                /*
                std::cout << std::string(2, ' ')
                << "Screen Tap id: " << gesture.id()
                << ", state: " << stateNames[gesture.state()]
                << ", position: " << screentap.position()
                << ", direction: " << screentap.direction()<< std::endl;
                */
                break;
            }
            default:
                /*
                std::cout << std::string(2, ' ')  << "Unknown gesture type." << std::endl;
                */
                break;
        }
    }
    
    
    /*
    if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
        std::cout << std::endl;
    }
    */
    
}

void AirwritingListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void AirwritingListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}

void AirwritingListener::onDeviceChange(const Controller& controller) {
    std::cout << "Device Changed" << std::endl;
    const DeviceList devices = controller.devices();
    
    for (int i = 0; i < devices.count(); ++i) {
        std::cout << "id: " << devices[i].toString() << std::endl;
        std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
    }
}

void AirwritingListener::onServiceConnect(const Controller& controller) {
    std::cout << "Service Connected" << std::endl;
}

void AirwritingListener::onServiceDisconnect(const Controller& controller) {
    std::cout << "Service Disconnected" << std::endl;
}

void AirwritingListener::push(unsigned long long timestamp) {
    if (lastTimestamp == 0) {
//        std::cout << "Frame id: " << timestamp << ": Now start sampling." << std::endl;
        lastTimestamp = timestamp;
        sampling = true;
        return;
    }
    if (timestamp - lastTimestamp < GESTURE_TAP_MAX_TIMESTAMP_DELTA) {
//        std::cout << "Frame id: " << timestamp << ": Throw a frame." << std::endl;
        return;
    }
    if (sampling) {
//        std::cout << "Frame id: " << timestamp << ": Send a frame." << std::endl;
        Task::getInstance()->pushTask();
    }
    sampling = !sampling;
    lastTimestamp = timestamp;
}

void AirwritingListener::sample(const Finger &finger) {
    if (finger.type() == FINGER_INDEX) {
        if (sampling) {
            float x = finger.tipPosition().x;
            float y = finger.tipPosition().y;
            float z = finger.tipPosition().z;
            if ((y > FINGER_Y_MIN) && (y < FINGER_Y_MAX)) {
                if ((fabs(x) < FINGER_X_MAX) && (fabs(z) < FINGER_Z_MAX)) {
                    Canvas::getInstance()->setPixel(x / FINGER_X_MAX, z / FINGER_Z_MAX, y / 30);
                }
            }
        }
    }
}

AirwritingListener::AirwritingListener() {
    lastTimestamp = 0;
    sampling = false;
}

AirwritingListener::~AirwritingListener() {
    sampling = false;
}
