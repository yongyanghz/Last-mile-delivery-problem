# Alibaba Tianchi Big Data Competition: Last Mile delivery problem
阿里巴巴天池大数据比赛：最后一公里极速配送

The Competition link:
https://tianchi.aliyun.com/competition/information.htm?spm=5176.11165320.5678.2.47b45cdeIYay8b&raceId=231581

## Problem Description:
The most chanllenging issue in e-commerce shipping business it the last mile delivery where packages are delivered from local branchesof express companies to individual customers. The last mile delivery also includes the scenario of intra city O2O(Online To Offline) delivery.

In this competition, participants are required to provide solutions to couriers for 2 types of packages which is e-commerce package and intra city O2O packages.For e-commerce packages, couriers will pick up local branches of express companies and deliver to individual customers. For intra city O2O packages, couriers will pick up packages at O2O shops and deliver to cutomers with pick up and delivery time requirement.

We will focus on one express company which owns 124 service branches in Shanghai, and the maximum number of couriers is 1000.

The details of the requirements are listed in [the link](https://tianchi.aliyun.com/competition/entrance/231581/information?lang=en-us) above.

 
The performance is measured by the total amount of time spent by all couriers. The less time, the better.

## Delivery Strategy and Algorithm

### Call graph of problem::solveProblem()
![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classproblem_a37c6ff9240b7d94ab82b0b8cc2088f08_cgraph_org.svg) 

Basic Strategy for a courier: 

 1. Add a courier, start working from 8:00 and at the branch that the first e-commerce package remained ;
 
 2. If there are e-commerce packages to delivery, get the e-commerce packages from the same depot branch. And the strategy to get next e-commerce package is pick the package that the delivery location is the nearest to the center of delivery locations of the other packages on hands.
 
 3. Plan a short path using  a greedy heuristic insert algorithm for the packages on hand;
 	
 4. If there are o2o packages to delivery, get the o2o packages, and insert them into the path if possible;
 
 4. Deilvery all the packages on hand through this path;
 
 5.  Back to the nearest depot branch, and repeat step 2-5 until the time is off.
 
 Apply this strategy to all of the couriers until the job is done. 
 

## Class Design

### UML Model
![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/Last-mile-delivery.svg) 

### Classes
- problem
Responsible for load data and solve the problem

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classproblem__coll__graph_org.svg) 

- courier 
class of courier, incudes the information of  a courier.

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classcourier__coll__graph.svg) 


- eorder
class of e-commerce package

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classeorder__coll__graph.svg) 

- o2o_order
class of intra city O2O(Online To Offline) delivery package

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classo2o__order__coll__graph_org.svg) 

- location
class of location, it consists of id, longitude and latitude information

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classlocation__coll__graph.svg) 

- record
class of record, when a courier visit a place and leave, a record will be generated, which includes the location and time information

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classrecord__coll__graph.svg) 

- visitnode
Courier visit a place to delivery package, whether it is e-commerce package or o2o package, the visitnode record the index of package and the location.
![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classvisitnode__coll__graph.svg) 

- visitnode
Courier visit a place to delivery package, whether it si e-commerce package or o2o package, the visitnode record the index of package and the location

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classvisitnode__coll__graph.svg) 

- route
A route class records route that a courier send all the packages on hands.

![](https://github.com/yongyanghz/Last-mile-delivery-problem/blob/master/img/classroute__coll__graph_org.svg) 









