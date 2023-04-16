#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_THRUST 100
#define BOOST_THRUST 650
#define CHECKPOINT_RADIUS 600
#define POD_RADIUS 400

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 typedef struct pod{
    int x;
    int y;

    int cpx;
    int cpy;

    int cdist;
    int angle;

    int speed;
 }pod_t;

 pod_t pod;

 void GetPodInfo(int x, int y, int cpx, int cpy, int cpdist, int cpang){


    pod.x = x;
    pod.y = y;
    pod.angle = cpang;
    pod.cdist = cpdist;
    pod.cpx = cpx;
    pod.cpy = cpy;
}


int main()
{
    
    // game loop
    while (1) {

        
        int x, y,  cpx, cpy, cpdist, cpang;
        cin >> x >> y >> cpx >> cpy >> cpdist >> cpang; cin.ignore();
        GetPodInfo(x, y,  cpx, cpy, cpdist, cpang);
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int thrust;
        static bool boost_used = false;
        if(!boost_used && cpang == 0 && cpdist > 5000){
            cout << pod.cpx << " " << pod.cpy << " BOOST" << endl;
            boost_used = true;
        }
        else{
            if(cpang > 90 || cpang < -90) {
                thrust = 0;
                pod.speed = 0;
        }
            else{
                thrust = 100;
                pod.speed = 100;
        }
        // You have to output the target position
        // followed by the power (0 <= thrust <= 100) or "BOOST"
        // i.e.: "x y thrust"
            cout << pod.cpx << " " << pod.cpy << " "<< pod.speed << endl;

            //cerr << "Distance: " << cpdist <<"\nAngle " << cpang << "\nThrust: "<< thrust<< endl;
            cerr << "Distance: " << pod.cdist <<"\nAngle " << pod.angle << "\nThrust: "<< pod.speed << endl;
            cerr << "\nBoost used: " << boost_used << endl;
        }  
    }
}


int AngleCompensation(int cpx, int cpy){
    
}