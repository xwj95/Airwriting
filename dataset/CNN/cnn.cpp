#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

#define CATEGORY_SHOW 4

#define CNN_M0 100
#define CNN_N0 100
#define CNN_M1 46
#define CNN_N1 46
#define CNN_M2 19
#define CNN_N2 19
#define CNN_CHANNEL0 1
#define CNN_CHANNEL1 12
#define CNN_CHANNEL2 4
#define CNN_KERNEL1 9
#define CNN_KERNEL2 9
#define CNN_POOLING1 2
#define CNN_POOLING2 2
#define CNN_SOFTMAX 1444
#define CNN_CATEGORY 62

class Classifer {

private:

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

public:

void init() {
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

char character(int c) {
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

void analyse(double **image) {

    memset(input, 0, sizeof(input));
    memset(output11, 0, sizeof(output11));
    memset(output1, 0, sizeof(output1));
    memset(output21, 0, sizeof(output21));
    memset(output2, 0, sizeof(output2));
    memset(output, 0, sizeof(output));
    
    for (int i = 0; i < CNN_M0; ++i) {
        for (int j = 0; j < CNN_N0; ++j) {
            for (int c0 = 0; c0 < CNN_CHANNEL0; ++c0) {
                input[c0][i][j] = image[i][j] * 1.5 - 0.5;
            }
        }
    }
    for (int i = 0; i < CNN_M0 - CNN_KERNEL1 + 1; ++i) {
        for (int j = 0; j < CNN_N0 - CNN_KERNEL1 + 1; ++j) {
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
    for (int i = 0; i < CNN_M0 - CNN_KERNEL1 + 1; ++i) {
        for (int j = 0; j < CNN_N0 - CNN_KERNEL1 + 1; ++j) {
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
                double value = 0;
                for (int p11 = 0; p11 < CNN_POOLING1; ++p11) {
                    for (int p12 = 0; p12 < CNN_POOLING1; ++p12) {
                        value = std::max(value, output11[c1][i * CNN_POOLING1 + p11][j * CNN_POOLING1 + p12]);
                    }
                }
                output1[c1][i][j] = value;
            }
        }
    }
    for (int i = 0; i < CNN_M1 - CNN_KERNEL2 + 1; ++i) {
        for (int j = 0; j < CNN_N1 - CNN_KERNEL2 + 1; ++j) {
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
    for (int i = 0; i < CNN_M1 - CNN_KERNEL2 + 1; ++i) {
        for (int j = 0; j < CNN_N1 - CNN_KERNEL2 + 1; ++j) {
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
                double value = 0;
                for (int p21 = 0; p21 < CNN_POOLING2; ++p21) {
                    for (int p22 = 0; p22 < CNN_POOLING2; ++p22) {
                        value = std::max(value, output21[c2][i * CNN_POOLING2 + p21][j * CNN_POOLING2 + p22]);
                    }
                }
                output2[c2][i][j] = value;
            }
        }
    }
    for (int i = 0; i < CNN_M2; ++i) {
        for (int j = 0; j < CNN_N2; ++j) {
            for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
                for (int c = 0; c < CNN_CATEGORY; ++c) {
                    output[c] += output2[c2][i][j] * matrixw[c2 * CNN_M2 * CNN_N2 + i * CNN_N2 + j][c];
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
};


int main() {
	Classifer cnn;
	cnn.init();

	double **image;
	image = new double*[CNN_M0];
	for (int i = 0; i < CNN_M0; ++i) {
		image[i] = new double[CNN_N0];
	}

	std::ifstream fin;
	fin.open("image.txt");
	for (int i = 0; i < CNN_M0; i++)
		for (int j = 0; j < CNN_N0; j++)
			fin >> image[i][j];
	fin.close();

	cnn.analyse(image);
	return 0;
}
