//
//  Backend.cpp
//  Airwriting
//
//  Created by 徐炜杰 on 15/11/28.
//  Copyright © 2015年 徐炜杰. All rights reserved.
//

#include "Backend.h"
#include "Task.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

Backend *Backend::instance = new Backend();

Backend::Backend() {
    m = BACKEND_M;
    n = BACKEND_N;
    init();
}

Backend* Backend::getInstance() {
    if (!instance) {
        instance = new Backend();
    }
    return instance;
}

void Backend::init() {
    std::ifstream fin;
    fin.open("model.txt");
    if (!fin) {
        std::cout << "Cannot find model file." << std::endl;
        return;
    }
    for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
        for (int c0 = 0; c0 < CNN_CHANNEL0; ++c0) {
            for (int k11 = CNN_KERNEL1 - 1; k11 >= 0; --k11) {
                for (int k12 = CNN_KERNEL1 - 1; k12 >= 0; --k12) {
                    fin >> matrix1[c1][c0][k11][k12];
                }
            }
        }
    }
    for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
        for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
            for (int k21 = CNN_KERNEL2 - 1; k21 >= 0; --k21) {
                for (int k22 = CNN_KERNEL2 - 1; k22 >= 0; --k22) {
                    fin >> matrix2[c2][c1][k21][k22];
                }
            }
        }
    }
    for (int s = 0; s < CNN_SOFTMAX; ++s) {
        for (int c = 0; c < CNN_CATEGORY; ++c) {
            fin >> matrixw[s][c];
        }
    }
    for (int c = 0; c < CNN_CATEGORY; ++c) {
        fin >> matrixb[c];
    }
    fin.close();
}

double Backend::maxPool(double a, double b, double c, double d) {
    return std::max(std::max(a, b), std::max(c, d));
}

char Backend::character(int c) {
    if ((c >= 0) && (c <= 9)) {
        return c + 48;
    }
    else if ((c >= 10) && (c <= 35)) {
        return c + 55;
    }
    else if ((c >= 36) && (c <= 61)) {
        return c + 61;
    }
    return 32;
}

void Backend::analyse(double **image) {
    
    double input[CNN_CHANNEL0][CNN_M0 + 2][CNN_N0 + 2];
    double output11[CNN_CHANNEL1][CNN_M0 + 2][CNN_N0 + 2];
    double output1[CNN_CHANNEL1][CNN_M1 + 2][CNN_N1 + 2];
    double output21[CNN_CHANNEL2][CNN_M1 + 2][CNN_N1 + 2];
    double output2[CNN_CHANNEL2][CNN_M2 + 2][CNN_N2 + 2];
    double output[CNN_CATEGORY];
    
    memset(input, 0, sizeof(input));
    memset(output11, 0, sizeof(output11));
    memset(output1, 0, sizeof(output1));
    memset(output21, 0, sizeof(output21));
    memset(output2, 0, sizeof(output2));
    memset(output, 0, sizeof(output));
    
    for (int i = 0; i < CNN_M0; ++i) {
        for (int j = 0; j < CNN_N0; ++j) {
            for (int c0 = 0; c0 < CNN_CHANNEL0; ++c0) {
                input[c0][i + 1][j + 1] = image[i][j];
            }
        }
    }
    for (int i = 0; i < CNN_M0; ++i) {
        for (int j = 0; j < CNN_N0; ++j) {
            for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
                for (int c0 = 0; c0 < CNN_CHANNEL0; ++c0) {
                    for (int k11 = 0; k11 < CNN_KERNEL1; ++k11) {
                        for (int k12 = 0; k12 < CNN_KERNEL1; ++k12) {
                            output11[c1][i][j] += matrix1[c1][c0][k11][k12] * input[c0][i + k11][j + k12];
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < CNN_M0; ++i) {
        for (int j = 0; j < CNN_N0; ++j) {
            for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
                if (output11[c1][i][j] < 0) {
                    output11[c1][i][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < CNN_M1; ++i) {
        for (int j = 0; j < CNN_N1; ++j) {
            for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
                output1[c1][i + 1][j + 1] = maxPool(output11[c1][i + i][j + j], output11[c1][i + i + 1][j + j], output11[c1][i + i][j + j + 1], output11[c1][i + i + 1][j + j + 1]);
            }
        }
    }
    for (int i = 0; i < CNN_M1; ++i) {
        for (int j = 0; j < CNN_N1; ++j) {
            for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
                for (int c1 = 0; c1 < CNN_CHANNEL1; ++c1) {
                    for (int k21 = 0; k21 < CNN_KERNEL2; ++k21) {
                        for (int k22 = 0; k22 < CNN_KERNEL2; ++k22) {
                            output21[c2][i][j] += matrix2[c2][c1][k21][k22] * output1[c1][i + k21][j + k22];
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < CNN_M1; ++i) {
        for (int j = 0; j < CNN_N1; ++j) {
            for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
                if (output21[c2][i][j] < 0) {
                    output21[c2][i][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < CNN_M2; ++i) {
        for (int j = 0; j < CNN_N2; ++j) {
            for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
                output2[c2][i + 1][j + 1] = maxPool(output21[c2][i + i][j + j], output21[c2][i + i + 1][j + j], output21[c2][i + i][j + j + 1], output21[c2][i + i + 1][j + j + 1]);
            }
        }
    }
    for (int i = 0; i < CNN_M2; ++i) {
        for (int j = 0; j < CNN_N2; ++j) {
            for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
                for (int c = 0; c < CNN_CATEGORY; ++c) {
                    output[c] += output2[c2][i + 1][j + 1] * matrixw[c2 * CNN_M2 * CNN_N2 + i * CNN_N2 + j][c];
                }
            }
        }
    }
    int result[CNN_CATEGORY];
    double sum = 0;
    for (int c = 0; c < CNN_CATEGORY; ++c) {
        output[c] += matrixb[c];
        result[c] = c;
        sum += exp(output[c]);
    }
    double p[CNN_CATEGORY];
    for (int c = 0; c < CNN_CATEGORY; ++c) {
        p[c] = exp(output[c]) / sum;
    }
    for (int c1 = 0; c1 < CNN_CATEGORY - 1; ++c1) {
        for (int c2 = c1 + 1; c2 < CNN_CATEGORY; ++c2) {
            if (p[c1] < p[c2]) {
                std::swap(p[c1], p[c2]);
                std::swap(result[c1], result[c2]);
            }
        }
    }
    
    std::cout << std::endl << "Predict: " << std::endl;
    for (int c = 0; c < CATEGORY_SHOW; ++c) {
        std::cout << character(result[c]) << ": " << p[c] * 100 << "%" << std::endl;
    }
}

void Backend::listen() {
    Task *tasks = Task::getInstance();
//    unsigned int count = 0;
    while (listening) {
        if (tasks->getSize()) {
//            std::cout << "Receive frame " << count++ << "." << std::endl;
            double **image = tasks->getTask(m, n);
            tasks->popTask();
            analyse(image);
            tasks->release(image, m, n);
        }
    }
}

void Backend::start() {
    listening = true;
}

void Backend::stop() {
    listening = false;
}
