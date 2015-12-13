//
//  Backend.hpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#ifndef Backend_h
#define Backend_h

#define BACKEND_M 28
#define BACKEND_N 28

#define CATEGORY_SHOW 4
#define CNN_M0 28
#define CNN_N0 28
#define CNN_M1 14
#define CNN_N1 14
#define CNN_M2 7
#define CNN_N2 7
#define CNN_CHANNEL0 1
#define CNN_CHANNEL1 8
#define CNN_CHANNEL2 4
#define CNN_KERNEL1 3
#define CNN_KERNEL2 3
#define CNN_POOLING1 2
#define CNN_POOLING2 2
#define CNN_SOFTMAX 196
#define CNN_CATEGORY 62

class Backend {
    
private:
    Backend();
    static Backend *instance;
    
public:
    static Backend* getInstance();
    
private:
    unsigned int m, n;
    bool listening;
    void analyse(double **image);
    
public:
    void listen();
    void start();
    void stop();
    
private:
    void init();
    char character(int c);
    
    double matrix1[CNN_CHANNEL1][CNN_CHANNEL0][CNN_KERNEL1][CNN_KERNEL1];
    double matrix2[CNN_CHANNEL2][CNN_CHANNEL1][CNN_KERNEL2][CNN_KERNEL2];
    double matrixw[CNN_SOFTMAX][CNN_CATEGORY];
    double matrixb[CNN_CATEGORY];
    
    double input[CNN_CHANNEL0][CNN_M0][CNN_N0];
    double output11[CNN_CHANNEL1][CNN_M0][CNN_N0];
    double output1[CNN_CHANNEL1][CNN_M1][CNN_N1];
    double output21[CNN_CHANNEL2][CNN_M1][CNN_N1];
    double output2[CNN_CHANNEL2][CNN_M2][CNN_N2];
    double output[CNN_CATEGORY];
    
};

#endif /* Backend_h */
