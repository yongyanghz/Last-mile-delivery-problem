#include "location.h"

location::location()
{
    //ctor
}

location::~location()
{
    //dtor
}
location::location(string s,double lng,double lat):
    id_(s),lng_(lng),lat_(lat){
}

void location::setID(string str){
    id_ = str;
}
string location::id(){
    return id_;
}

void location::setLng(double value){
    lng_ = value;
}
double location::lng(){
    return lng_;
}

void location::setLat(double value){
    lat_ = value;
}
double location::lat(){
    return lat_;
}
