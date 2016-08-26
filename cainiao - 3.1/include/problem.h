/*-------------------------------------------------------------------------Author Yang Yong ------------------------*/
#ifndef PROBLEM_H
#define PROBLEM_H

#include<cstdlib>
#include<string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include<queue>
#include<map>
#include<cmath>
#include<algorithm>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include"location.h"
#include"eorder.h"
#include"o2o_order.h"
#include"courier.h"
#include"route.h"
#include"visitnode.h"
#include"record.h"

#define PI 3.14159265
#define CAPACITY 140
#define FAIL -1
#define LIMIT_TIME 720

using namespace std;

inline bool myfunctionComp( o2o_order& q1,  o2o_order& q2){
    return  q1.pickupTime() < q2.pickupTime();
}


class problem
{
    public:
        problem();
        virtual ~problem();
        /** \brief Load all the data needed in this problem
         *
         * \param
         * \param
         * \return None
         *
         */
        void loadData();
       /** \brief Solve the problem,the main process function of this problem
        *
        * \param
        * \param
        * \return None
        *
        */
        void solveProblem();
        /** \brief Write the result of solution to a csv file
         *
         * \param
         * \param
         * \return None
         *
         */
        void toCSV(ofstream &myfile);
         /** \brief Print the debug information, for test
         *
         * \param
         * \param
         * \return None
         *
         */
        void printDebugInformation();

    protected:

    private:

        std::vector<eorder> allEOrders;     // 所有电商订单
        std::vector<o2o_order>allO2OOrders; // 所有o2o订单

        std::vector<int> eOrdWait;    // e-orders index waiting to send 未配送电商订单序号
        std::vector<int> o2oOrdWait;  // o2o orders  index waiting to send 未配送o2o订单序号

        std::vector<location> spotLocs; //including spot locations and shop locations 包括商铺地址和配送点地址
        std::vector<location> depotLocs;       // 网点地址
        std::map<std::string,int> depotLocMap; // 网点地址和序号的映射
        std::map<std::string,int> spotLocMap;  // 商铺地址或配送点地址和序号的映射
        vector<courier> solution;              // 解决方案
        int capacity;                          // 快递员容量

        /** \brief Load location file
         *
         * \param std::string fileName: the file name to load
         * \param std::vector<location> &locations:locations:the data structure to store the locations
         * \return None
         *
         */
        void loadALocationFile(std::string fileName,std::vector<location> &locations);
        /** \brief Load site file,spot file,shop file
         *
         * \param std::string site_file: the file name of site locations
         * \param std::string spot_file: the file name of spot locations
         * \param std::string shop_file: the file name of shop locations
         * \return None
         */
        void loadLocations(std::string site_file,std::string spot_file,std::string shop_file);

        /** \brief Load electric commerce orders file
         *
         * \param std::string fileName: the file name of the electric commerce orders
         * \return None;
         *
         */
        void loadEOrders(std::string fileName);
        /** \brief Load o2o orders file
         *
         * \param std::string fileName: the file name of the o2o orders
         * \return None;
         *
         */
        void loadO2OOrders(std::string fileName);
        /** \brief Create a map of location and index
         *
         * \param
         * \return None;
         *
         */
        void createLocMap();
        /** \brief Calculate the service time which is related to the number of packages
         *
         * \param int num: the the number of packages
         * \return the service time
         *
         */
        int calServeTime(int num);
        /** \brief Calculate the travel time from one location to another location
         *
         * \param location &l1: the start Location
         * \param location &l2: the end Location
         * \return travel time
         *
         */
        int calDistanceTravelTime(location &l1,location &l2);
        /** \brief Initialize the problem,prepare for solving problem
         *
         * \return None
         *
         */
        void initProblem();
        /** \brief From the eOrdWait (ec order to deliver),find the orders whose depot is the same as the demanding depot
         *
         * \param int index: the demanding depot location index
         * \param
         * \return  a vector of the index of orders in eOrdWait
         *
         */
        vector<int> findSameDepotEord(int index);
        /** \brief From a vector of e-orders, find the order that has the nearest distance from the current center of the spots          *
         *
         * \param vector<int> &eo:  the vector of current orders
         * \param vector<int> &sameDepotSet: the vector of orders to search
         * \return the index of e-order
         *
         */
        int getTheNearest(vector<int> &eo,vector<int> &sameDepotSet);
        /** \brief When get the e-orders,add records to the route
         *
         * \param vector<int> eo: the ec orders get
         * \param route &r: the route to add record
         * \return
         *
         */
        void addRecordGetE(vector<int> eo,route &r);
        /** \brief Start from a depot, get the e-orders to send
         *
         * \param route &R: the  current route
         * \param int &startTime: the start time
         * \param int endLocIndex: the end location index of the last route
         * \return true:can add ec orders to deliver.
         *         false:can not add ec orders to deliver.
         */
        bool getEorderPackage(route &R,int &startTime,int endLocIndex);
        /** \brief Reorder the visit nodes in route,use the greedy insert algorithm
         *
         * \param route &R: current route
         * \param
         * \return None
         *
         */
        void reOrder(route &R);

        /** \brief Find the o2o orders in which the pickup time is within the time window
         *
         * \param int startT: start time
         * \param int endT: end time
         * \return a vector of indexes of o2o orders
         *
         */
        vector<int> findO2OordWithinTime(int startT,int endT);
        /** \brief When the e-orders is not empty,choose an o2o within time to add to the current route
         *
         * \param vector<int> o2oWaitIndexSet: o2o orders within the time
         * \param route R: the current route
         * \return the index of o2o orders in set
         *
         */
        int findNearestO2O(vector<int> o2oWaitIndexSet,route R);
        /** \brief When the 2-orders is empty, choose an o2o order to add to the current route
         *
         * \param route R: current route
         * \return the index of o2o order
         *
         */
        int findNearByO2O(route R);
        /** \brief Calculate the center of current route
         *
         * \param route R: current route
         * \return the location of center
         *
         */
        location calRouteCentre(route R);
        /** \brief Choose an o2o order to add
         *
         * \param route &R: current route
         * \return true: can add an o2o order to the route
         *         false:can't add an o2o order to the route
         */
        bool chooseAnO2OtoAdd(route &R);
        /** \brief Add an giving o2o order to the current route
         *
         * \param int oInd: the index of o2o order
         * \param route R: the current route
         * \return NULL: can't add
         *         route* : can add
         *
         */
        route* addO2OToRoute(int oInd,route R);
        /** \brief If the first order to send is o2o order,the courier should start from the nearest depot to
         *         get to the shop to pickup package
         *
         * \param int spot: the index of shop location
         * \return the index of depot location
         *
         */
        int shopFromNearestSite(int spot);
        /** \brief Calculate the time of this route, and test if it is a legal route
         *
         * \param route R: route
         * \return  NULL: this route is illegal
         *          route*: this route is legal
         *
         */
        route* calRouteTime(route R);
        /** \brief Transform the information of route to records
         *
         * \param route &R: route
         * \return None
         *
         */
        void routeToRecords(route &R);
        /** \brief Add a courier to solution
         *
         * \param courier c: courier
         * \return
         *
         */
        void addCourier(courier c);
        /** \brief Get the nearest depot location index from the end location of last route
         *
         * \param int endLocIndex: the index of end location
         * \return the index of depot
         *
         */
        int getNearestDepot(int endLocIndex);

         /** \brief Get the index of depot to pickup package of e-orders
         *
         * \param int startTime: start time
         * \param int endLocIndex: the end location index of last route
         * \return the index of depot
         *
         */
        int getDepotLocIndex(int startTime,int endLocIndex);
        /* Inline method to short the length of the method*/
        inline void initForCalRoutTime(int &latestTime,int &sumLateTime,int &mustLateTime,\
                        int &lastArriveTime,int &currentTime,int &currentLoad, route &R);
        /* Inline method to short the length of the method*/
        inline void setRouteAfterCal(int endTime,int punishTime,route &R);



};

#endif // PROBLEM_H
