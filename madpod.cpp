#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define MAX_SPEED               100
#define CHECKPOINT_RADIUS       600

#define MIN_DIST_BOOST          5000
#define MIN_ANGLE_BOOST         2
#define RADIUS_MULTIPLIER       3.0
#define SLOW_DOWN_DIST          (CHECKPOINT_RADIUS * RADIUS_MULTIPLIER)

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 typedef struct pod{
    int x,y;
    int lastx, lasty;
    int cpx, cpy;
    float cdist, angle;
    float speed;
    bool boost_used;

 }pod_t;

 pod_t pod = {0, };

 void GetPodInfo() {

    int x, y,  cpx, cpy, cpdist, cpang;
    cin >> x >> y >> cpx >> cpy >> cpdist >> cpang; cin.ignore();
    pod.x = x;
    pod.y = y;
    pod.angle = abs(cpang);
    pod.cdist = cpdist;
    pod.cpx = cpx;
    pod.cpy = cpy;
}


bool TryUseBoost() {
    if(!pod.boost_used && (pod.angle < MIN_ANGLE_BOOST) && pod.cdist > MIN_DIST_BOOST){
        pod.boost_used = true;
        return true;
    }
    return false;
}

float AngleCompenstaion() {
    float speedFactor = (1 - pod.angle/90);
    if(speedFactor < 0){
        speedFactor = 0;
    }
    return speedFactor;
}

float CheckpointDistCompensation() {
    float speedFactor(1 - pod.cdist/SLOW_DOWN_DIST);
    if(speedFactor < 0){
        speedFactor = 1;
    }
    return speedFactor;
}

float SpeedCompensation(){  // Chooses if 
    float speedFactor;
    if(pod.cdist <= (SLOW_DOWN_DIST) ){
        cerr << "CP close\n" <<endl;
        speedFactor = CheckpointDistCompensation();
    }
    else{
        cerr << "Angle too wide\n" <<endl;
        speedFactor = AngleCompenstaion();
    }
    return round(speedFactor * MAX_SPEED);
}


void GetLastPosition(){
    pod.lastx = pod.x;
    pod.lasty = pod.y;
}

void GetNextPosition(){
    static bool initflag = false; // Sometimes the 1st checkpoint coord-s are not properly set
    if(initflag){
        int xdiff = pod.x - pod.lastx;
        int ydiff = pod.y - pod.lasty;

        pod.cpx -= (xdiff * RADIUS_MULTIPLIER);
        pod.cpy -= (ydiff * RADIUS_MULTIPLIER);
    }
    else initflag = true;   
}


int main()
{
    int lastx, lasty;
    // game loop
    while (1) {
        
        GetPodInfo();

        GetNextPosition();

        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        pod.speed = SpeedCompensation();

        cout << pod.cpx << " " << pod.cpy << " ";
        if(TryUseBoost()){
            cout << "BOOST";
        }
        else{
            cout << pod.speed;
        }
        cout << endl;

        cerr << "Distance: " << pod.cdist <<"\nAngle " << abs(pod.angle) << "\nSpeed: "<< pod.speed << endl;
        cerr << "X: " << pod.x <<"\nY " << pod.y << endl;

        pod.boost_used ? cerr << "Boost Used" << endl : cerr << "Boost not used" << endl;

        GetLastPosition();
        }  
}