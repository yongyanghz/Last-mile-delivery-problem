#ifndef RECORD_H
#define RECORD_H

#include<iostream>
#include<string>

#include <sstream>
#include<stdio.h>
using namespace std;


namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

class record
{
    public:
        record();
        virtual ~record();

        record(int cID,string ad,int arrive,int depart,int load,string ord):
        courierID(cID),addr(ad),arriveTime(arrive),departTime(depart),amount(load),orderID(ord){
        }

        void printRecord(){
        cout<<"Courier_Id: "<<courierID<<" addr: "<<addr<<" arrive_time: "<<arriveTime<<" depart_time: "<<\
        departTime<<" amount: "<<amount<<" order_ID: "<<orderID<<endl;
        }

        string toString(){ //separate with comma
            string entry = "D";
            char cID[10];
            sprintf(cID,"%04d",courierID);
            string str(cID);
            entry += str+",";
            entry += addr+",";
            entry += patch::to_string(arriveTime)+",";
            entry += patch::to_string(departTime)+",";
            entry += patch::to_string(amount)+",";
            entry += orderID + ",\n";
            return entry;
        }
    protected:

    private:

        int courierID;
        string addr;
        int arriveTime;
        int departTime;
        int amount;  // get +/deliver -
        string orderID;


};

#endif // RECORD_H
