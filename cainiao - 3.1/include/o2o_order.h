#ifndef O2O_ORDER_H
#define O2O_ORDER_H

#include"location.h"

using namespace std;
class o2o_order
{
    public:
        o2o_order();
        virtual ~o2o_order();


        o2o_order(string s,int p,int d,int pt,int dt,int n,int site);
        // The information of the o2o order
        void setID(string str);
        string id();

        void setPickupLoc(int index);
        int pickupLoc();

        void setDeliveryLoc(int index);
        int deliveryLoc();

        void setPickupTime(int time);
        int pickupTime();

        void setDeliveryTime(int time);
        int deliveryTime();

        void setUnload(int n);
        int unload();

        void setSiteLoc(int index);
        int siteLoc();

        void setWillLate();
        bool willLate();

        void setWillOutTime();
        bool willOutTime();

        void setLatestTime(int time);
        int latestTime();

        void setMustLateTime(int time);
        void addMustLateTime(int time);
        int mustLateTime();


    protected:

    private:
        string id_;                         // 订单编号
        int pickupLoc_,deliveryLoc_;        // 取货地址序号，送货地址序号
        int pickupTime_,deliveryTime_;      // 取货时间，最迟送货时间
        int unload_;                        // 包裹件数
        int siteLoc_;                       // 属于的网点地址序号
        bool willLate_;                     // 配送是否一定会迟到
        bool willOutTime_;                  // 配送是否一定会晚于晚上8点
        int latestTime_;                    // 如果一定迟到，最早可以到达配送点的时间
        int mustLateTime_;                  // 如果一定迟到，迟到的累计时间
};

#endif // O2O_ORDER_H
