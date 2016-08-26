/*-------------------------------------------------------------------------Author Yang Yong ------------------------*/
#include "problem.h"

problem::problem()
{
    //ctor
}

problem::~problem()
{
    //dtor
}
/* Read the depot location,spot location and shop location from the files*/
/* 读取地址文件，包括网点地址，商铺地址，配送点地址 */
void problem::loadLocations(std::string site_file,std::string spot_file,std::string shop_file){
    loadALocationFile(site_file,depotLocs);
    loadALocationFile(spot_file,spotLocs);
    loadALocationFile(shop_file,spotLocs);
}

/* Read the location information from a file */
/* 读入一个地址文件，把读入的地址信息储存对应的vector里面*/
void problem::loadALocationFile(std::string fileName,std::vector<location> &locations){
    std::ifstream file(fileName.c_str());
    std::string line;
    while(std::getline(file,line,'\n')){
        std::stringstream iss(line);
        string id;
        double lng,lat;
        for(int col = 0;col<3;++col){
            std::string val;
            std::getline(iss,val,',');
            std::stringstream convertor(val);
            switch(col){
                case 0:convertor>>id;break;
                case 1:convertor>>lng;break;
                case 2:convertor>>lat;break;
            }
            if(!iss.good())
                break;
        }
        location a_site = location(id,lng,lat);
        locations.push_back(a_site);
        }
}

/* Print the debug information*/
void problem::printDebugInformation(){
    cout<<"Location information"<<endl;
    for(size_t i = 0;i<depotLocs.size();++i){
        cout<<depotLocs[i].id()<<" ";
        printf("%.5f\t",depotLocs[i].lng());
        printf("%.5f\n",depotLocs[i].lat());
    }
    for(size_t i = 0;i<spotLocs.size();++i){
        cout<<spotLocs[i].id()<<" ";
       printf("%.5f\t",spotLocs[i].lng());
        printf("%.5f\n",spotLocs[i].lat());
    }
//    cout<<"o2o orders information:"<<endl;
//    for(std::size_t i = 0;i< allO2OOrders.size();++i){
//        cout<<"o2o2 order id is"<<allO2OOrders[i].id()<<" The depot index is ";
//        cout<<allO2OOrders[i].siteLoc()<<"Pick: "<<allO2OOrders[i].pickupTime()<<"delivery: "<<\
//        allO2OOrders[i].deliveryTime()<<"The amount :"<<allO2OOrders[i].unload()<<endl;
//    }
//    cout<<"The ec order information:"<<endl;
//     for(std::size_t i = 0;i< allEOrders.size();++i){
//        cout<<"o2o2 order id: "<<allEOrders[i].id<<" The depot index: "<<allEOrders[i].depotLoc;
//        cout<<"spot loc: "<<allEOrders[i].deliveryLoc<<"The amount :"<<allEOrders[i].unload<<endl;
//     }

}


/* Create maps of location id and vector index*/
/* 创建地址与在vector中序号的映射*/
void problem::createLocMap(){
    for(std::size_t i = 0;i<depotLocs.size();++i){
        depotLocMap.insert(std::pair<std::string,int>(depotLocs[i].id(),i));
    }
    for(std::size_t i = 0;i<spotLocs.size();++i){
        spotLocMap.insert(std::pair<std::string,int>(spotLocs[i].id(),i));
    }
}

/* Read the electricity supplier orders from the file*/
/* 读取电商订单文件*/
 void problem::loadEOrders(std::string fileName){
    std::ifstream file(fileName.c_str());
    std::string line;
    while(std::getline(file,line,'\r')){
        std::stringstream iss(line);
        string id;
        int depot,spot,unload;
        for(int i = 0;i<4;++i){
            std::string val;
            std::getline(iss,val,',');
            std::stringstream convertor(val);
            switch(i){
                case 0:convertor>>id;break;
                case 1:convertor>>line;
                       spot = spotLocMap[line]; break;
                case 2: convertor>>line;
                       depot = depotLocMap[line]; break;
                case 3:convertor>>unload;break;
            }
            if(!iss.good())
                break;
        }
        eorder order = eorder(id,spot,depot,unload);
        allEOrders.push_back(order);
    }
 }
 /* Read the o2o orders from the file*/
/* 读取o2o订单文件*/
void problem::loadO2OOrders(std::string fileName){
    std::ifstream file(fileName.c_str());
    std::string line;
    while(std::getline(file,line)){
        std::stringstream iss(line);
        string id;
        int pLoc,dLoc,pTime,dTime,unload,site;
        for(int i = 0;i<7;++i){
            std::string val;
            std::getline(iss,val,',');
            std::stringstream convertor(val);
            switch(i){
                case 0:convertor>>id;break;
                case 1:convertor>>line;
                       dLoc = spotLocMap[line];break;
                case 2:convertor>>line;
                       pLoc = spotLocMap[line];break;
                case 3:convertor>>pTime;break;
                case 4:convertor>>dTime;break;
                case 5:convertor>>unload;break;
                case 6:convertor>>line;
                       site = depotLocMap[line];break;
            }
            if(!iss.good())  break;
        }
        o2o_order order = o2o_order(id,pLoc,dLoc,pTime,dTime,unload,site);
        int travelTime = calDistanceTravelTime(spotLocs[pLoc],spotLocs[dLoc]);
        if( travelTime> (dTime - pTime)){
             order.setWillLate();
             order.setMustLateTime(travelTime-dTime +pTime);
        }
        if((pTime+travelTime)>LIMIT_TIME){
            order.setWillOutTime();
            order.setLatestTime(pTime+travelTime);
            order.addMustLateTime((pTime+travelTime)-LIMIT_TIME);
        }
        allO2OOrders.push_back(order);
    }
    // 根据取货时间对o2o订单进行排序
    std::sort(allO2OOrders.begin(),allO2OOrders.end(),myfunctionComp);// sort the o2o orders by pickup time
 }
/* Load the data need in this problem*/
/* 载入该问题所需文件*/
void problem::loadData(){
    loadLocations("new_1.csv","new_2.csv","new_3.csv");
    createLocMap();
    loadEOrders("new_4.csv");
    loadO2OOrders("o2o_order.csv");
}
/* Calculate the travel time from one location to another location*/
/* 计算地址1到地址2的旅行时间*/
int problem::calDistanceTravelTime(location &l1,location &l2){
    double  speed  = 0.25;    // 15 km/h,0.25/min
    double R = 6378.137;       // the radius of earth
    double delLng = l1.lng()/2 - l2.lng()/2;
    double delLat = l1.lat()/2 - l2.lat()/2;
    double distance = 2*R*asin(sqrt(pow(sin(PI/180*delLat),2)+\
                                       cos(PI/180*l1.lat())*cos(PI/180*l2.lat())\
                                       *pow(sin(PI/180*delLng),2)));
    int  travelTime = round(distance/speed);
    return travelTime;
}

/*Initialize the problem,prepare for solving problem*/
/* 初始化问题*/
void problem::initProblem(){
    for(std::size_t i =0;i<allEOrders.size();++i)
        eOrdWait.push_back(i);
    for(std::size_t i =0;i<allO2OOrders.size();++i)
        o2oOrdWait.push_back(i);
    capacity = CAPACITY;
    solution.clear();
}
/* Solve the problem,the main process function of this problem */
/* 解决问题，是本算法的主程序*/
void problem::solveProblem(){
    initProblem();
    int startTime;
    int startCourieId = 1;
    int endLocIndex = -1;
    while(!eOrdWait.empty() || !o2oOrdWait.empty()){
        courier aCourier; // a courier
        aCourier.setID(startCourieId);
        startTime = 0;
        while((!eOrdWait.empty() || !o2oOrdWait.empty()) && !aCourier.isWorkFinish()){
            route aRoute;         //Every loop add a route
            aRoute.setCourierID(aCourier.getID());
            aRoute.setStartTime(startTime);
            if(!eOrdWait.empty()){   //Get the e order package
                if(!getEorderPackage(aRoute,startTime,endLocIndex)) break;        // 获取电商订单
                while(!o2oOrdWait.empty())    // add o2o order
                    if(!chooseAnO2OtoAdd(aRoute)) break;   //Start a new route
            }else{
                if(!chooseAnO2OtoAdd(aRoute) && aRoute.vNodesEmpty()) break;      // 选择一个o2o订单插入到路径中
                while(!o2oOrdWait.empty())
                    if(!chooseAnO2OtoAdd(aRoute)){
                        aCourier.setWorkFinish(); break; //Start a new courier
                    }
            }
            routeToRecords(aRoute);
            aCourier.addRoute(aRoute);
            endLocIndex = aRoute.getEndLocIndex();
            startTime = aRoute.getEndTime();
            aRoute.printRouteInformation(); //For debug
        }    // a route ends here
        addCourier(aCourier);
        startCourieId++;
    }       // a courier ends here
}
/* Find the o2o orders in which the pickup time is within the time window*/
/* 找到所有取货时间在给定时间窗里的o2o订单*/
vector<int> problem::findO2OordWithinTime(int startT,int endT){
    vector<int> vec;
    for(std::size_t i = 0;i < o2oOrdWait.size();++i){
        if((allO2OOrders[o2oOrdWait[i]].pickupTime() > startT) &&\
           (allO2OOrders[o2oOrdWait[i]].pickupTime() < endT))
            vec.push_back(i);
    }
    return vec;
}
/* When the e-orders is not empty,choose an o2o within time to add to the current routes*/
/* 在一个o2o订单集合中，找到距离当前路径最近的一个o2o订单*/
int problem::findNearestO2O(vector<int> o2oWaitIndexSet,route R){
    int index = -1;
    location centre = calRouteCentre(R);
    int disMin = 99999;
    int dis = 99999;
    for(std::size_t i =0;i < o2oWaitIndexSet.size();++i){
        dis = 0.8*calDistanceTravelTime(centre,spotLocs[allO2OOrders[o2oOrdWait[o2oWaitIndexSet[i]]].pickupLoc()]);
        dis += 0.2*calDistanceTravelTime(centre,spotLocs[allO2OOrders[o2oOrdWait[o2oWaitIndexSet[i]]].deliveryLoc()]);
        if(dis<disMin){
            disMin = dis;
            index = i;
        }
    }
    return index;
}
/* Calculate the center of current route*/
/* 计算一条路径的中心位置*/
location problem::calRouteCentre(route R){
    location centre;
    double lng = 0;
    double lat = 0;
    for(std::size_t i = 0;i<R.vNodesSize();++i){
        lng += spotLocs[R[i].locIndex()].lng();
        lat += spotLocs[R[i].locIndex()].lat();
    }
    lng /= R.vNodesSize();
    lat /= R.vNodesSize();
    centre.setLng(lng);
    centre.setLat(lat);
    return centre;
}
/* Choose an o2o order to add*/
/* 选择一个o2o订单加入到当前路径中，可以加入返回true,不能加入返回false*/
bool problem::chooseAnO2OtoAdd(route &R){
    int continueTime = 110;
    route* rpt;
    int earlyIndex = 0;
    //if the pickup time is 1 hour later than the end time of route,then go back to depot to get e-orders
    if(!eOrdWait.empty() && (allO2OOrders[o2oOrdWait[earlyIndex]].pickupTime() > continueTime+R.getEndTime()))
        return false;
    vector<int> withinTimeO2Os;
    int nnIndex; //nearest neighbor index
    if(!eOrdWait.empty()){
        withinTimeO2Os = findO2OordWithinTime(R.getStartTime(),R.getEndTime()+continueTime);
        if(withinTimeO2Os.empty())  return false;
        nnIndex = withinTimeO2Os[findNearestO2O(withinTimeO2Os,R)];
    }
    else{  //e order is empty, only o2o order left to send
        nnIndex = findNearByO2O(R);
        if(nnIndex == FAIL) return false;
    }
    rpt = addO2OToRoute(nnIndex,R);
    if(rpt!= NULL){
        R = *rpt;
        o2oOrdWait.erase(o2oOrdWait.begin()+nnIndex);
        delete rpt;
        return true;
    }
    else
        return false;
}
/*If the  e-orders is empty*/
/* 如果待配送电商订单为空，根据时间和距离选择一个离当前路径较近的o2o订单*/
int problem::findNearByO2O(route R){
    if(R.vNodesEmpty())
        return 0;
    int earlist;
    int downT,upT;
    vector<int> o2oSet;
    bool canFind = false;
    for(std::size_t i = 0;i<o2oOrdWait.size();++i){
        if(allO2OOrders[o2oOrdWait[i]].pickupTime() > R.getStartTime()){
            earlist = i;
            canFind = true;
            break;
        }
    }
    if(!canFind) return FAIL;
    o2oSet.push_back(earlist);
    downT = allO2OOrders[o2oOrdWait[earlist]].pickupTime();
    upT = downT + 60;
    for(std::size_t i = 0;i<o2oOrdWait.size();++i){
         if(allO2OOrders[o2oOrdWait[i]].pickupTime() > downT &&\
            allO2OOrders[o2oOrdWait[i]].pickupTime() < upT )
                o2oSet.push_back(i);
    }
    return o2oSet[findNearestO2O(o2oSet,R)];
}
/* Add an giving o2o order to the current route*/
/* 给定一个o2o订单，将它插入到当前路径中，插入位置选择使路径cost最小的位置*/
route* problem::addO2OToRoute(int oInd,route R){

    route* rpt;
    visitnode pickNode = visitnode(true,allO2OOrders[o2oOrdWait[oInd]].unload(),\
                                   allO2OOrders[o2oOrdWait[oInd]].pickupLoc(),-1,o2oOrdWait[oInd]);
    visitnode deliveryNode = visitnode(true,-allO2OOrders[o2oOrdWait[oInd]].unload(),\
                                       allO2OOrders[o2oOrdWait[oInd]].deliveryLoc(),-1,o2oOrdWait[oInd]);
    bool canInsert = false;
    int minTotalTime = 9999;
    //Select the position to insert
    std::size_t  n = R.vNodesSize();
    if(allO2OOrders[o2oOrdWait[oInd]].willLate()){ //if this o2o will be late whatever 这个o2o订单一定会迟到
        for(std::size_t i = 0;i<n+1;++i){          // 选择插入位置
            R.insertVisitNode(i,pickNode);
            R.insertVisitNode(i+1,deliveryNode);
            route* rpt2 = calRouteTime(R);
            if(rpt2!=NULL)
                if(rpt2->getTotalCostTime() < minTotalTime){
                    rpt = rpt2;
                    minTotalTime = rpt2->getTotalCostTime();
                    canInsert = true;
                }
            R.eraseVisitNode(i+1);
            R.eraseVisitNode(i);
        }
    }else {                                  // 选择插入位置
        for(std::size_t i = 0;i<n+1;++i){
            R.insertVisitNode(i,pickNode);
            for(std::size_t j = i+1;j<n+2;++j){
                R.insertVisitNode(j,deliveryNode);
                route* rpt2 = calRouteTime(R);
                if(rpt2!=NULL)
                    if(rpt2->getTotalCostTime() < minTotalTime){
                        rpt = rpt2;
                        minTotalTime = rpt2->getTotalCostTime();
                        canInsert = true;
                    }
            R.eraseVisitNode(j);
            }
            R.eraseVisitNode(i);
        }
    }
    if(!canInsert) return NULL;
    else return rpt;
}
/* 为calRouteTime方法做一些变量的初始化，以减少方法行数*/
inline void problem::initForCalRoutTime(int &latestTime,int &sumLateTime,int &mustLateTime,\
                        int &lastArriveTime,int &currentTime,int &currentLoad, route &R){

    latestTime = LIMIT_TIME;
    sumLateTime = 0;
    mustLateTime = 0;
    lastArriveTime = 0;
    currentTime = R.getStartTime();
    currentLoad = R.getCurrentLoad();
}
/*calculate the time of route ,if this route is impossible(late to pick up the o2o order,
  out of capacity,out of work time,return NULL.*/
/* 计算该路径是否可行，如果可行,返回route的指针，否则返回NULL*/
route* problem::calRouteTime(route R){
    if(R.getStartTime() > 550) return NULL;
    int latestTime,sumLateTime,mustLateTime,lastArriveTime,currentTime,currentLoad;
    initForCalRoutTime(latestTime,sumLateTime,mustLateTime,lastArriveTime,currentTime,currentLoad,R);
    visitnode v;
    for(std::size_t i = 0;i<R.vNodesSize();++i){
        if(i == 0){
            v = R[i];
            if((R.getCurrentLoad() ==0) &&v.isO2O() && currentTime==0)
                currentTime = shopFromNearestSite(v.locIndex());
            else
                currentTime += calDistanceTravelTime(depotLocs[R.getStartLocIndex()],spotLocs[v.locIndex()]);
        }else{
            visitnode v0 = R[i-1];
            v = R[i];
            currentTime += calDistanceTravelTime(spotLocs[v0.locIndex()],spotLocs[v.locIndex()]);
        }
        lastArriveTime = currentTime;
        if(!v.isO2O()){  // e-order
            if(currentTime>LIMIT_TIME)  return NULL;
            currentTime += calServeTime(allEOrders[v.eIndex()].unload());
            currentLoad += v.amount();
        }else{  // o2o order
            if(v.amount() > 0){//pickup package of o2o
                if(allO2OOrders[v.oIndex()].willLate())
                    mustLateTime += allO2OOrders[v.oIndex()].mustLateTime();
                if(allO2OOrders[v.oIndex()].willOutTime())
                    latestTime = allO2OOrders[v.oIndex()].latestTime();
                if(currentTime > allO2OOrders[v.oIndex()].pickupTime())  return NULL; // too late to pickup
                currentTime = allO2OOrders[v.oIndex()].pickupTime();
                currentLoad += v.amount();
                if(currentLoad >capacity)  return NULL;
            }else{            // delivery the package of o2o order
                if(currentTime > allO2OOrders[v.oIndex()].deliveryTime()) // late to delivery,penalize the time
                    sumLateTime += currentTime - allO2OOrders[v.oIndex()].deliveryTime();
                currentTime += calServeTime(allO2OOrders[v.oIndex()].unload());
                currentLoad += v.amount();
            }
        }
    }
    if(lastArriveTime>LIMIT_TIME)
        sumLateTime +=lastArriveTime - LIMIT_TIME;
    if((lastArriveTime > latestTime)|| (sumLateTime > mustLateTime)) return NULL;
    setRouteAfterCal(currentTime,5*sumLateTime,R);
    route* rpt =  new route(R);
    return rpt;
}
/* 设置计算路径后该路径的一些参数*/
inline void problem::setRouteAfterCal(int endTime,int punishTime,route &R){
    R.setEndTime(endTime);
    R.setPunishTime(punishTime);
    R.calTotalCost();
}
/* If the first order to send is o2o order,the courier should start from the nearest depot to
    get to the shop to pickup package*/
/* 如果快递员第一个配送的快递是o2o订单，则需要从离该订单商铺最近网点出发，否则会被惩罚*/
int problem::shopFromNearestSite(int spot){
    int minT = LIMIT_TIME;
    int time = 0;
    for(std::size_t i = 0;i<depotLocs.size();++i){
        time = calDistanceTravelTime(depotLocs[i],spotLocs[spot]);
        if(time< minT){
            minT = time;
        }
    }
    return minT;
}
/*获取给定地址序号的最近网点地址序号*/
int problem::getNearestDepot(int endLocIndex){
    int minT =9999;
    int dis = 9999;
    int depotIndex;
    for(std::size_t i = 0;i<eOrdWait.size();++i){
        dis = calDistanceTravelTime(depotLocs[allEOrders[eOrdWait[i]].depotLoc()],\
                                 spotLocs[endLocIndex]);
        if(dis < minT){
            minT = dis;
            depotIndex = allEOrders[eOrdWait[i]].depotLoc();
        }
    }
    return depotIndex;
}
/* Get the index of depot to pickup package of e-orders*/
/* 确定从哪一个网点去取电商订单包裹*/
int problem::getDepotLocIndex(int startTime,int endLocIndex){
    int depotLocIndex;
      if(startTime!=0)
        depotLocIndex = getNearestDepot(endLocIndex);
    else{
        srand (time(NULL));
//        int i = rand() % eOrdWait.size();
        int i = 0;
        depotLocIndex = allEOrders[eOrdWait[i]].depotLoc();
    }
    return depotLocIndex;
}
/* Start from a depot, get the e-orders to send*/
/* 从某一网点出发，根据距离最近原则选取要配送的电商订单*/
bool problem::getEorderPackage(route &R,int &startTime,int endLocIndex){
    int depotLocIndex = getDepotLocIndex(startTime,endLocIndex);
    std::vector<int> eo;
    int first,next,indexSame;
    for(std::size_t i =0;i<eOrdWait.size();++i)
        if(allEOrders[eOrdWait[i]].depotLoc() == depotLocIndex){
            first = i;break;
        }
    eo.push_back(eOrdWait[first]);
    visitnode v0 = visitnode(false,-allEOrders[eOrdWait[first]].unload(),\
                             allEOrders[eOrdWait[first]].deliveryLoc(),eOrdWait[first],-1);
    route newR = R;
    newR.addVisitNode(v0);
    newR.addCurrentLoad(allEOrders[eOrdWait[first]].unload());
    int newStartTime =startTime;
    if(startTime!=0)
        newStartTime += calDistanceTravelTime(spotLocs[endLocIndex],depotLocs[depotLocIndex]);
    newR.setStartTime(newStartTime);
    newR.setStartLocIndex(allEOrders[eOrdWait[first]].depotLoc());
    route* rpt = calRouteTime(newR);
    if(rpt == NULL) return false;
    R = *rpt;
    eOrdWait.erase(eOrdWait.begin()+first);
    vector<int> sameDepot;
    // filter the same depot e-order
    while(R.getCurrentLoad() < capacity){
        newR = R;
        sameDepot = findSameDepotEord(depotLocIndex);
        indexSame = getTheNearest(eo,sameDepot);
        if(indexSame==FAIL) break;
        next = sameDepot[indexSame];
        if((newR.getCurrentLoad()+allEOrders[eOrdWait[next]].unload() > capacity))  break;
        visitnode v = visitnode(false,-allEOrders[eOrdWait[next]].unload(),\
                                allEOrders[eOrdWait[next]].deliveryLoc(),eOrdWait[next],-1);
        newR.addVisitNode(v);
        newR.addCurrentLoad(allEOrders[eOrdWait[next]].unload());
        route* rpt1 = calRouteTime(newR);
        if(rpt1 == NULL)  break;
        else{
            R = *rpt1;
            eo.push_back(eOrdWait[next]);
            eOrdWait.erase(eOrdWait.begin()+next);
        }
    }
    addRecordGetE(eo,R);
    reOrder(R);
    return true;
}
/*Use the greedy heuristic insert algorithm  to reorder the route*/
/* 应用贪心启发式插入算法对电商订单配送顺序进行重排*/
void problem::reOrder(route& R){
    route newR = R;
    for(std::size_t i =1;i<R.vNodesSize();++i)
        newR.eraseVisitNode(i);
    for(std::size_t i = 1;i<R.vNodesSize();++i){
        route* rpt;
        route newR1 = newR;
        int n = newR1.vNodesSize()+1;
        int minT = 9999;
        for(std::size_t j=0;j< n;++j){
            newR1.insertVisitNode(j,R[i]);
            rpt = calRouteTime(newR1);
            if(rpt!=NULL)
            if(rpt->getEndTime() < minT){
                minT = rpt->getEndTime();
                newR = *rpt;
            }
            newR1.eraseVisitNode(j);
        }
    }
    R = newR;
}
/*From a vector of e-orders, find the order that has the nearest distance from the current center of the spots*/
/* 选择一个电商订单，距离目前订单集合中各配送点的中心位置最近*/
int problem::getTheNearest(vector<int> &eo,vector<int>& sameDepotSet){
    int nnIndex = -1;
    double latMean = 0;
    double lngMean = 0;
    int minDis = LIMIT_TIME;
    for(std::size_t i = 0;i<eo.size();++i){
        location aLoc;
        aLoc  = spotLocs[allEOrders[eo[i]].deliveryLoc()];
        latMean += aLoc.lat();
        lngMean +=  aLoc.lng();
    }
    latMean /=eo.size();
    lngMean /=eo.size();
    location center = location("centre",lngMean,latMean);
    int dis;
    location aLoc;
    for(std::size_t i = 0;i< sameDepotSet.size();++i){
        aLoc  = spotLocs[allEOrders[eOrdWait[sameDepotSet[i]]].deliveryLoc()];
        dis = calDistanceTravelTime(center,aLoc);
        if(dis < minDis){
            minDis = dis;
            nnIndex = i;
        }
    }
    return nnIndex;
}
/*  From the eOrdWait (e-order to deliver),find the orders whose depot is the same as the demanding depot*/
/* 从待配送电商订单中获取属于同一网点的电商订单*/
vector<int> problem::findSameDepotEord(int depotLocIndex){
    vector<int> same;
    for(std::size_t i = 0;i<eOrdWait.size();++i){
            if(allEOrders[eOrdWait[i]].depotLoc() == depotLocIndex){
                same.push_back(i);
            }
    }
    return same;
}
/*  Calculate the service time which is related to the number of packages*/
/* 计算服务时间*/
int problem::calServeTime(int num){
    int time;
    time = round(3*sqrt(num*1.0)+5);
    return time;
}

/* When get the e-orders,add records to the route*/
/* 将取电商包裹转化为记录*/
void problem::addRecordGetE(vector<int> eo,route &r){
    for(std::size_t i = 0;i<eo.size();++i){
        record aRecord  = record(r.getCourierID(),depotLocs[r.getStartLocIndex()].id(),r.getStartTime(),r.getStartTime(),\
                                 allEOrders[eo[i]].unload(),allEOrders[eo[i]].id());
        r.addRecord(aRecord);
    }
}
/* Transform the information of route to records*/
/* 将路径信息转化为记录*/
void problem::routeToRecords(route &R){
    int currentTime = R.getStartTime();
    record aRecord;
    int arriveTime,departTime;
    string addr,orderID;;
    for(std::size_t i = 0;i < R.vNodesSize();++i){
        visitnode v;
        if(i == 0){
            v = R[i];
             if((R.getCurrentLoad() == 0)&&v.isO2O() && currentTime==0)
                currentTime = shopFromNearestSite(v.locIndex());
            else
                currentTime += calDistanceTravelTime(depotLocs[R.getStartLocIndex()],spotLocs[v.locIndex()]);
        }else{
            visitnode v0 = R[i-1];
            v = R[i];
            currentTime += calDistanceTravelTime(spotLocs[v0.locIndex()],spotLocs[v.locIndex()]);
        }
        arriveTime = currentTime;
        if(!v.isO2O()){  // e-order
            currentTime += calServeTime(allEOrders[v.eIndex()].unload());
            orderID = allEOrders[v.eIndex()].id();
        }else{  // o2o order
            orderID = allO2OOrders[v.oIndex()].id();
            if(v.amount() > 0)//pickup package of o2o
                currentTime = allO2OOrders[v.oIndex()].pickupTime();
            else            // delivery the package of o2o order
                currentTime += calServeTime(allO2OOrders[v.oIndex()].unload());
         }
        departTime = currentTime;
        addr = spotLocs[v.locIndex()].id();
        aRecord = record(R.getCourierID(),addr,arriveTime,departTime,v.amount(),orderID);
        R.addRecord(aRecord);
    }
    R.setEndTime(currentTime);
    R.calTotalCost();
}
/* Add a courier to solution*/
/* 添加快递员*/
void problem::addCourier(courier c){
    solution.push_back(c);
}
/* Write the result of solution to a csv file*/
/* 将结果写入文件*/
void problem::toCSV(ofstream &myfile){
    string record;
    for(std::size_t i = 0;i<solution.size();++i)
            solution[i].toCSV(myfile);
}
