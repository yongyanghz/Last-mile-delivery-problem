#include "eorder.h"
using namespace std;
eorder::eorder()
{
    //ctor
}

eorder::~eorder()
{
    //dtor
}

eorder::eorder(std::string s,int d,int si,int n):
    id_(s),deliveryLoc_(d),depotLoc_(si),unload_(n){
}


 void eorder::setID(int id){
    id_ = id;
 }

string eorder::id(){
    return id_;
}

void eorder::setDepotLoc(int de){
    depotLoc_ = de;
}
int eorder::depotLoc(){
    return depotLoc_;
}

void eorder::setDeliveryLoc(int de){
    deliveryLoc_ = de;
}

int eorder::deliveryLoc(){
    return deliveryLoc_;
}

void eorder::setUnload(int n){
    unload_ = n;
}

int eorder::unload(){
    return unload_;
}
