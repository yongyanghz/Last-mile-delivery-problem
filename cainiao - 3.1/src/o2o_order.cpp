#include "o2o_order.h"

o2o_order::o2o_order()
{
    //ctor
    willLate_ = false;
    willOutTime_ = false;
    latestTime_ = 720;
    mustLateTime_ = 0;
}

o2o_order::~o2o_order()
{
    //dtor
}

o2o_order::o2o_order(string s,int p,int d,int pt,int dt,int n,int site):
   id_(s),pickupLoc_(p),deliveryLoc_(d),pickupTime_(pt),deliveryTime_(dt),unload_(n),siteLoc_(site){
       willLate_ = false;
}

 void o2o_order::setID(string str){
    id_ = str;
 }
string o2o_order::id(){
    return id_;
}

void o2o_order::setPickupLoc(int index){
    pickupLoc_ = index;
}
int o2o_order::pickupLoc(){
    return pickupLoc_;
}

void o2o_order::setDeliveryLoc(int index){
    deliveryLoc_ = index;
}
int o2o_order::deliveryLoc(){
    return deliveryLoc_;
}

void o2o_order::setPickupTime(int time){
    pickupTime_ = time;
}
int o2o_order::pickupTime(){
    return pickupTime_;
}

void o2o_order::setDeliveryTime(int time){
    deliveryTime_ = time;
}
int o2o_order::deliveryTime(){
    return deliveryTime_;
}

void o2o_order::setUnload(int n){
    unload_ = n;
}
int o2o_order::unload(){
    return unload_;
}

void o2o_order::setSiteLoc(int index){
    siteLoc_ = index;
}
int o2o_order::siteLoc(){
    return siteLoc_;
}

void o2o_order::setWillLate(){
    willLate_ = true;
}

bool o2o_order::willLate(){
    return willLate_;
}
void o2o_order::setWillOutTime(){
    willOutTime_ = true;
}
bool o2o_order::willOutTime(){
    return willOutTime_;
}
void o2o_order::setLatestTime(int time){
    latestTime_ = time;
}
int o2o_order::latestTime(){
    return latestTime_;
}

void o2o_order::setMustLateTime(int time){
    mustLateTime_ = time;
}
void o2o_order::addMustLateTime(int time){
    mustLateTime_ += time;
}
int o2o_order::mustLateTime(){
    return mustLateTime_;
}
