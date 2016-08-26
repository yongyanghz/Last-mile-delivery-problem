
#include<cstdlib>
#include<string>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include"problem.h"
#include"record.h"

using namespace std;

int main()
{
    problem p;
    p.loadData();           //载入数据
    ofstream myfile;
    string fileName ;

    fileName = "courier.csv";
    myfile.open (fileName.c_str());
    p.solveProblem();
    p.toCSV(myfile);       //写入文件
    myfile.close();

    return 0;
}
