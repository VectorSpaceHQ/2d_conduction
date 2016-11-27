// 2D, Transient Conduction Solver for Hackaday 1Kb challenge.

#include <iostream>
#include <iomanip>
using namespace std;


int main(){
    int N = 28;
    int tmax = 1000;

    float T[N][N];
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

    cout << endl << "Initial conditions" << endl;
    cout << setprecision(2);
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << T[i][j]<< ", " ;
        }
        cout << endl;
    }


    for (int t=0; t<tmax; t++){

        // Please optimize this
        for (int i=0; i<=N; i++){
            for (int j=0; j<=N; j++){
                T_old[i][j] = T[i][j];
            }
        }

        for (int j=1; j<N-1; j++){
            for (int i=1; i<N-1; i++){
                T[i][j] = ((alpha * dt) / dx_squared)
                    * (T_old[i+1][j] + T_old[i-1][j] + T_old[i][j-1] + T_old[i][j+1] - 4*T_old[i][j])
                    + T_old[i][j];
            }
        }
    }


    // display matrix just for debugging
    cout << endl << "Final conditions" << endl;
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << T[i][j]<< ", " ;
        }
        cout << endl;
    }

    return 0;
}
