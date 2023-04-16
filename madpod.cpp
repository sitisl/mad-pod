#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

#define MAX_THRUST 100
#define BOOST_THRUST 650
#define CHECKPOINT_RADIUS 600
#define POD_RADIUS 400

#define MIN_DIST_BOOST 5000
#define MIN_ANGLE_BOOST 2
#define SLOW_DOWN_DIST  (CHECKPOINT_RADIUS * 2)

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 typedef struct pod{
    int x,y;
    int lastx, lasty;
    int cpx, cpy;
    int cdist, angle;
    int speed;
    bool boost_used;
 }pod_t;

 pod_t pod = {0, };

 void GetPodInfo(pod_t* pod) {

    int x, y,  cpx, cpy, cpdist, cpang;
    cin >> x >> y >> cpx >> cpy >> cpdist >> cpang; cin.ignore();
    pod->x = x;
    pod->y = y;
    pod->angle = cpang;
    pod->cdist = cpdist;
    pod->cpx = cpx;
    pod->cpy = cpy;
}


bool TryUseBoost() {

    if(!pod.boost_used && (abs(pod.angle) < MIN_ANGLE_BOOST) && pod.cdist > MIN_DIST_BOOST){
        pod.boost_used = true;
        return true;
    }
    return false;
}

int AngleCompenstaion() {
    float speedFactor = (1 - abs((float)pod.angle)/90);
    if(speedFactor < 0){
        speedFactor = 0;
    }
    return round(speedFactor * MAX_THRUST);
}

float CheckpointDistCompensation() {
    float speedFactor(1 - (float)pod.cdist/SLOW_DOWN_DIST);
    if(speedFactor < 0){
        speedFactor = 1;
    }
    return round(speedFactor * MAX_THRUST);
}

float Compensation(){
    if(pod.cdist <= (SLOW_DOWN_DIST) ){
        cerr << "DISTANCE SPEED\n" <<endl;
        return CheckpointDistCompensation();
    }
    else{
        cerr << "ANGLE SPEED\n" <<endl;
        return AngleCompenstaion();
    }
}

void GetNextPosition(){
    pod.lastx = pod.x;
    pod.lasty = pod.y;
    if(pod.lastx == pod.x || pod.lasty == pod.y){
        return;
    }
}


int main()
{
    int lastx, lasty;
    // game loop
    while (1) {

        GetPodInfo(&pod);
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        int fac = AngleCompenstaion();
        int fac2 = CheckpointDistCompensation();
        
        pod.speed = Compensation();
        GetNextPosition();

        cout << pod.cpx << " " << pod.cpy << " ";
        if(TryUseBoost()){
            cout << "BOOST";
        }
        else{
            cout << pod.speed;
        }
        cout << endl;
        
        

        //cerr << "Distance: " << cpdist <<"\nAngle " << cpang << "\nThrust: "<< thrust<< endl;
        cerr << "Distance: " << pod.cdist <<"\nAngle " << abs(pod.angle) << "\nThrust: "<< pod.speed << endl;
        cerr << "X: " << pod.x <<"\nY " << pod.y << endl;
        cerr << "lX: " << pod.lastx <<"\nlY " << pod.lasty << endl;
        cerr << "\nBoost used: " << pod.boost_used << "\nAng Speed: " << fac <<"\nDist Speed: " << fac2 << endl;
        }  
}




