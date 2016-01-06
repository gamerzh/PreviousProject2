#include "ai/AIMolo.h"

PlayerWork AIMolo::nextStep(int currentCoins) {
    PlayerWork playerWork;
//    int turrentLevel = rand()%this->getMaxTurrentLevel();
//    playerWork.setTurrentLevel(turrentLevel);
    
    if(count == 0) {
        nextCountReset = 60 + rand()%100;
        fireLevel = baseFireLevel + rand()%10;
    }
    
    if( count > nextCountReset && count < nextCountReset + 10 ) {
        playerWork.setAngle((float)angle);
        playerWork.setFire(false);
        lastFire = false;
        return playerWork;
    }
    
    if( count >  nextCountReset + 10 ) {
        count = 0;
    }
    
    playerWork.setTurrentLevel(this->getMaxTurrentLevel());
    
    int fire = rand()%100;
    
    int currentFireLevel = fireLevel;
    if(lastFire) {
        currentFireLevel = fireLevel+30;
    }
    
    if(fire < currentFireLevel) { // TODO : just test value
        if(!lastFire) {
            angle = 60 - rand()%120;
        }else {
            angle += 1 - rand()%2;
        }
        
        playerWork.setAngle((float)angle);
        playerWork.setFire(true);
        lastFire = true;
        return playerWork;
    }else {
        playerWork.setFire(false);
        lastFire = false;
        
        int turn = rand()%100;
        if(turn < 20) {
            angle = 60 - rand()%120;
            playerWork.setAngle((float)angle);
        }else {
            playerWork.setAngle(angle);
        }
    }
    
    count++;
    return playerWork;
    
}