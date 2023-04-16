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
    if(!pod.boost_used && (pod.angle < MIN_ANGLE_BOOST) && pod.cdist > MIN_DIST_BOOST){ // Use boost only if angle is narrow enough and distance far enough
        pod.boost_used = true;                                                          // This ensures that the pod does not overshoot the checkpoint, if it is too close.
        return true;                                                                    // Also if the angle is wrong the boost wont move us towards the CP optimally.
    }
    return false;
}

float AngleCompenstaion() {                                                             // If the angle is equal or over 90 deg, the speedfactor will be 0
    float speedFactor = (1 - pod.angle/90);                                             // Else the pod will be slower for a wider angle and faster when the angle is most narrow.
    if(speedFactor < 0){
        speedFactor = 0;
    }
    return speedFactor;
}

float CheckpointDistCompensation() {                                                    // Similar logic to AngleCompensation(). Start to slow down if we reach SLOW_DOWN_DIST
    return (1 - pod.cdist/SLOW_DOWN_DIST);                                              // The closer we are, the more we slow down
}                                                                                           

float SpeedCompensation(){  // Chooses if 
    float speedFactor;
    if(pod.cdist <= (SLOW_DOWN_DIST) ){                                                 // Only call CheckpointDistCompensation(), when we are in range of SLOW_DOWN_DIST
        cerr << "CP close\n" <<endl;
        speedFactor = CheckpointDistCompensation();
    }
    else{
        cerr << "Angle too wide\n" <<endl;                                              // Else comepensate for angle
        speedFactor = AngleCompenstaion();
    }
    return round(speedFactor * MAX_SPEED);
}


void GetLastPosition(){                                                                 // Needed for calculating next position
    pod.lastx = pod.x;                                                                  
    pod.lasty = pod.y;
}

void GetNextPosition(){
    static bool initflag = false;                                                        // Sometimes the 1st checkpoint coord-s are not properly set
    if(initflag){
        int xdiff = pod.x - pod.lastx;                                                   // Once we have prev pos, we can calculate the difference between the last and current pos.
        int ydiff = pod.y - pod.lasty;

        pod.cpx -= (xdiff * RADIUS_MULTIPLIER);                                          // If we have the difference coordinates we can change the perceived checkpoint from the pods POV
        pod.cpy -= (ydiff * RADIUS_MULTIPLIER);                                          // This ensures that the pod wont drive until the CP center, the game's "intertia" will carry the pod on
    }
    else initflag = true;   
}


int main()
{
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