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
#define SLOW_DOWN_DIST  (CHECKPOINT_RADIUS * 4.0)

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 typedef struct pod{
    int x,y;
    int lastx, lasty;
    int nextx, nexty;
    int cpx, cpy;
    float cdist, angle;
    float speed;
    bool boost_used;

 }pod_t;

 pod_t pod = {0, };

 void GetPodInfo(pod_t* pod) {

    int x, y,  cpx, cpy, cpdist, cpang;
    cin >> x >> y >> cpx >> cpy >> cpdist >> cpang; cin.ignore();
    pod->x = x;
    pod->y = y;
    pod->angle = abs(cpang);
    pod->cdist = cpdist;
    pod->cpx = cpx;
    pod->cpy = cpy;
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

float Comp2(){
    return round(CheckpointDistCompensation() * AngleCompenstaion() * MAX_THRUST) ;
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

void GetLastPosition(){
    pod.lastx = pod.x;
    pod.lasty = pod.y;
}

void GetNextPosition(){
    int xdiff = pod.x - pod.lastx;
    int ydiff = pod.y - pod.lasty;

    pod.nextx = xdiff + pod.x;
    pod.nexty = ydiff + pod.y;
}


int main()
{
    int lastx, lasty;
    // game loop
    while (1) {

        GetPodInfo(&pod);
        //GetNextPosition();
        int opponent_x;
        int opponent_y;
        cin >> opponent_x >> opponent_y; cin.ignore();

        //float fac = AngleCompenstaion();
        //float fac2 = CheckpointDistCompensation();
        if(pod.angle < 1){
            pod.speed = 100;
        }else{
            float comp2 = Comp2();
            //pod.speed = round(Compensation() * MAX_THRUST);
            pod.speed = comp2;
        }
        // float comp2 = Comp2();
        // pod.speed = round(Compensation() * MAX_THRUST);
        // pod.speed = comp2;

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
        //cerr << "lX: " << pod.lastx <<"\nlY " << pod.lasty << endl;
        //cerr << "nX: " << pod.nextx <<"\nnY " << pod.nexty << endl;
        //cerr << "\nBoost used: " << pod.boost_used << "\nAng fac: " << fac <<"\nDist fac: " << fac2 <<"\nComp2: " << comp2 << endl;

        GetLastPosition();
        }  
}




