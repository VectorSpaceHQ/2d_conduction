// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.

#ifndef __AVR
#include <iostream>
#include <iomanip>
using namespace std;
#endif


void assign_color(float T, float Tmin, float Tmax){
    // Assign a color to a given temperature using the coolwarm colormap.
    // http://www.kennethmoreland.com/color-maps/

    float scale[34] = {0, 0.03125, 0.0625, 0.09375, 0.125, 0.15625, 0.1875, 0.21875, 0.25, 0.28125, 0.3125, 0.34375, 0.375, 0.40625, 0.4375, 0.46875, 0.5, 0.53125, 0.5625, 0.59375, 0.625, 0.65625, 0.6875, 0.71875, 0.75, 0.78125, 0.8125, 0.84375, 0.875, 0.90625, 0.9375, 0.96875, 1};
    int reds[34] = {59,68,77,87,98,108,119,130,141,152,163,174,184,194,204,213,221,229,236,241,245,247,247,247,244,241,236,229,222,213,203,192,180};
    int greens[34] = {76, 90, 104, 117, 130, 142, 154, 165, 176, 185, 194, 201, 208, 213, 217, 219, 221, 216, 211, 204, 196, 187, 177, 166, 154, 141, 127, 112, 96, 80, 62, 40, 4};
    int blues[34] = {192, 204, 215, 225, 234, 241, 247, 251, 254, 255, 255, 253, 249, 244, 238, 230, 221, 209, 197, 185, 173, 160, 148, 135, 123, 111, 99, 88, 77, 66, 56, 47, 38};

    int index = 0;
    float ratio = (T - Tmin) / (Tmax - Tmin);
    for (int i=0; i<34; i++){
        if (ratio < scale[i]){
            index = i;
            break;
        }
    }


#ifndef __AVR
    cout << ratio << ", " << index << endl;
#endif

    int color[3] = {reds[index], blues[index], greens[index]};
}


int main(){
    int N = 8;
    int tmax = 1000;

    volatile float T[N][N];
    float T_old[N][N];
    float alpha = 1.0E-2;
    // time step size
    float dt = 0.1;
    // distance between LEDs, squared
    float dx_squared = 1.0 * 1.0;


    // initial conditions
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            T[i][j] = 40.0;
        }
    }
    for (int i=0; i<N; i++){
        T[i][0] = 40.0;
    }
    for (int i=0; i<N; i++){
        T[i][N-1] = 50.0;
    }
    for (int i=0; i<N; i++){
        T[0][i] = 50.0;
    }
    for (int i=0; i<N; i++){
        T[N-1][i] = 50.0;
    }

#ifndef __AVR
    cout << endl << "Initial conditions" << endl;
    cout << setprecision(2);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << T[i][j]<< ", " ;
        }
        cout << endl;
    }
#endif


    for (int t=0; t<tmax; t++){

        // Please optimize this
        for (int i=0; i<N; i++){
            for (int j=0; j<N; j++){
                T_old[i][j] = T[i][j];
            }
        }

        for (int j=1; j<N-1; j++){
            for (int i=1; i<N-1; i++){
                T[i][j] = ((alpha * dt) / dx_squared)
                    * (T_old[i+1][j] + T_old[i-1][j] + T_old[i][j-1] + T_old[i][j+1] - 4*T_old[i][j])
                    + T_old[i][j];
                /* assign_color(T[i][j], 40.0, 50.0); */
            }
        }
    }

#ifndef __AVR
    // display matrix just for debugging
    cout << endl << "Final conditions" << endl;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << T[i][j]<< ", " ;
        }
        cout << endl;
    }
#endif

    return 0;
}
