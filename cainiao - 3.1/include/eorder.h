#ifndef EORDER_H
#define EORDER_H

#include"location.h"

using namespace std;
class eorder
{
    public:
        eorder();
        virtual ~eorder();

        eorder(string id,int s,int si,int n);
        // E-order information
        void setID(int id);
        string id();

        void setDepotLoc(int de);
        int depotLoc();

        void setDeliveryLoc(int de);
        int deliveryLoc();

        void setUnload(int n);
        int unload();

    protected:


    private:
        string id_;
        int depotLoc_;
        int deliveryLoc_;
        int unload_;
};

#endif // EORDER_H
