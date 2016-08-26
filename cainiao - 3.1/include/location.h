#ifndef SITE_H
#define SITE_H

#include<iostream>
#include<string>

using namespace std;

class location
{
    public:
        location();
        location(string id,double lng,double lat);
        virtual ~location();

        void setID(string str);
        string id();

        void setLng(double value);
        double lng();

        void setLat(double value);
        double lat();

    protected:

    private:
        string id_;
        double lng_;
        double lat_;
};

#endif // SITE_H
