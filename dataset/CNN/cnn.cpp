#include <string>
#include <fstream>
#include <iostream>

using namespace std;

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

class Classifer {

private:

    double matrix1[CNN_CHANNEL1][CNN_CHANNEL0][CNN_KERNEL1][CNN_KERNEL1];
    double matrix2[CNN_CHANNEL2][CNN_CHANNEL1][CNN_KERNEL2][CNN_KERNEL2];
    double matrixw[CNN_SOFTMAX][CNN_CATEGORY];
    double matrixb[CNN_CATEGORY];

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

	double maxer(double a, double b, double c, double d) {
		double res = a;
		if (b > res) res = b;
		if (c > res) res = c;
		if (d > res) res = d;
		return res;
	}

	void analyse(double **image) {

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
		            output1[c1][i + 1][j + 1] = maxer(output11[c1][i + i][j + j], output11[c1][i + i + 1][j + j], output11[c1][i + i][j + j + 1], output11[c1][i + i + 1][j + j + 1]);
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
		            output2[c2][i + 1][j + 1] = maxer(output21[c2][i + i][j + j], output21[c2][i + i + 1][j + j], output21[c2][i + i][j + j + 1], output21[c2][i + i + 1][j + j + 1]);
		        }
		    }
		}
		for (int i = 0; i < CNN_M2; ++i) {
		    for (int j = 0; j < CNN_N2; ++j) {
		        for (int c2 = 0; c2 < CNN_CHANNEL2; ++c2) {
		            for (int c = 0; c < CNN_CATEGORY; ++c) {
		                output[c] += matrixw[c2 * 7 * 7 + i * 7 + j][c] * output2[c2][i + 1][j + 1];
		            }
		        }
		    }
		}
		for (int c = 0; c < CNN_CATEGORY; ++c) {
		    output[c] += matrixb[c];
		}
		int result = 0;
		std::cout << std::endl;
		for (int c = 0; c < CNN_CATEGORY; ++c) {
		    if ((c >= 0) && (c <= 9)) {
		        std::cout << (char) (c + 48);
		    }
		    else if ((c >= 10) && (c <= 35)) {
		        std::cout << (char) (c + 55);
		    }
		    else if ((c >= 36) && (c <= 61)) {
		        std::cout << (char) (c + 61);
		    }
		    std::cout << " : " << output[c] << "  \t" << matrixb[c] << std::endl;
		    if (output[c] > output[result]) {
		        result = c;
		    }
		}

		result = result + 1;
		if ((result >= 1) && (result <= 10)) {
		    std::cout << (char) (result + 47) << "!";
		}
		else if ((result >= 11) && (result <= 36)) {
		    std::cout << (char) (result + 54) << "?";
		}
		else if ((result >= 37) && (result <= 62)) {
		    std::cout << (char) (result + 60) << "#";
		}
		std::cout << std::endl;
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
