#ifndef COURIER_H
#define COURIER_H


#include<iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include "route.h"

using namespace std;
class courier
{
    public:
        courier();
        virtual ~courier();


        int getID(){
            return id;
        }
        void setID(int n){
            id = n;
        }
        bool isWorkFinish(){
           return workFinish;
        }
        void setWorkFinish(){
            workFinish = true;
        }
        void addRoute(route r){
            routes.push_back(r);
        }
        void toCSV(ofstream &myfile){
            for(std::vector<route>::iterator it = routes.begin();it!=routes.end();++it){
                it->toCSV(myfile);
            }
        }

    protected:

    private:
        int id;
        bool workFinish;
        vector<route> routes;
};

#endif // COURIER_H
