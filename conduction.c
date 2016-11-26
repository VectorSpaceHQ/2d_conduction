// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.

#include <iostream>
#include <string>
using namespace std;

int main(){
    float T[28][28] = {0.0};
    float T_old[28][28] = {0.0};
    float alpha = 1.0E-3;
    float dt = 1.0;
    float dx = 0.1;
    float dx_squared = dx * dx;

    // initial condition
    T[0][0] = 20;
    T[0][28] = 50;
    T[28][28] = 50;
    T[28][0] = 50;

    cout << T[12][13] << endl;

    for (int t=0; t<200; t++){

        // Please optimize this
        /* memcpy(T_old, T, sizeof (int) * 28 * 28); */
        for (int i=1; i<28; i++){
            for (int j=1; j<28; j++){
                T_old[i][j] = T[i][j];
            }
        }

        for (int i=1; i<28; i++){
            for (int j=1; j<28; j++){
                T[i][j] = ((alpha * dt) / (dx_squared)) * (T_old[i+1][j] + T_old[i-1][j] + T_old[i][j-1] + T_old[i][j+1]) - (4 * alpha * dt)/(dx_squared) * T_old[i][j] + T_old[i][j];

            }
        }
    }

    // just for debugging
    for (int i=1; i<28; i++){
        for (int j=1; j<28; j++){
            cout << T[i][j]<< ", " ;
        }
        cout << endl;
    }


    return 0;
}
