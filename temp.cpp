#include "iostream"
using namespace std;

float height(float x, float y){
    return x * x + y * y;
}

int main() {
    // 定义坐标
    float vertices[10 * 10 * 3];
    float indices[9 * 9 * 2 * 3];
    float x, z = 1, y;
    float ride = 2.0 / 10;
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < 10; i++) {
        x = -1;
        for (int j = 0; j < 10; j++) {
            x += ride;
            y = height(x, z);
            vertices[count1++] = x;
            vertices[count1++] = y;
            vertices[count1++] = z;

            if (i - 1 >= 0 && j - 1 >= 0) {
                indices[count2++] = i * 10 + j;
                indices[count2++] = (i - 1) * 10 + j;
                indices[count2++] = i * 10 + (j - 1);
            }
            if (i + 1 < 10 && j + 1 < 10) {
                indices[count2++] = i * 10 + j;
                indices[count2++] = (i + 1) * 10 + j;
                indices[count2++] = i * 10 + (j + 1);
            }
        }
        z -= ride;
    }

    for(int i = 0; i < count1;i++) {
        cout << indices[i] << ", ";
        if((i+1)% 3==0) cout << endl;
    }
}

