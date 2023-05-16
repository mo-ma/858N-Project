#include "LDDArb.h"
#include "LDD.h"
#include "seq.h"
#include <iostream>
#include <chrono>
#include<fstream>
#include<sstream> 

using namespace std;
ofstream outtable;
const int REPS = 3;
double test_parallel(parlay::sequence<parlay::sequence<int>> &edges, double beta) {
    auto begin_time = std::chrono::system_clock::now();
    for(int i=0;i<REPS;i++){
        auto c = ldd::get_LDD(edges, beta);
    }
    auto end_time = std::chrono::system_clock::now();
    double tm = chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count() / 1000000.0;
    return tm/REPS;
}
double test_parallel_arb(parlay::sequence<parlay::sequence<int>> &edges, double beta) {
    auto begin_time = std::chrono::system_clock::now();
    for(int i=0;i<REPS;i++){
        auto c = lddarb::get_LDD(edges, beta);
    }
    auto end_time = std::chrono::system_clock::now();
    double tm = chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count() / 1000000.0;
    return tm/REPS;
}
double test_sequential(vector<vector<int>> &vec_edges, double beta){
    auto begin_time = std::chrono::system_clock::now();
    for(int i=0;i<REPS;i++){
        auto c = sequential_LDD(vec_edges, beta);
    }
    auto end_time = std::chrono::system_clock::now();
    double tm = chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count() / 1000000.0;
    return tm/REPS;
}
string filenames[] = {"tests/test1000-0.txt","tests/test1000-1.txt","tests/test1000-10.txt","tests/test1000-11.txt","tests/test1000-12.txt","tests/test1000-13.txt","tests/test1000-14.txt","tests/test1000-15.txt","tests/test1000-16.txt","tests/test1000-17.txt","tests/test1000-18.txt","tests/test1000-19.txt","tests/test1000-2.txt","tests/test1000-20.txt","tests/test1000-21.txt","tests/test1000-22.txt","tests/test1000-23.txt","tests/test1000-24.txt","tests/test1000-25.txt","tests/test1000-26.txt","tests/test1000-27.txt","tests/test1000-28.txt","tests/test1000-29.txt","tests/test1000-3.txt","tests/test1000-4.txt","tests/test1000-5.txt","tests/test1000-6.txt","tests/test1000-7.txt","tests/test1000-8.txt","tests/test1000-9.txt","tests/test100000-0.txt","tests/test100000-1.txt","tests/test100000-10.txt","tests/test100000-11.txt","tests/test100000-12.txt","tests/test100000-13.txt","tests/test100000-14.txt","tests/test100000-15.txt","tests/test100000-16.txt","tests/test100000-17.txt","tests/test100000-18.txt","tests/test100000-19.txt","tests/test100000-2.txt","tests/test100000-20.txt","tests/test100000-21.txt","tests/test100000-22.txt","tests/test100000-23.txt","tests/test100000-24.txt","tests/test100000-25.txt","tests/test100000-26.txt","tests/test100000-27.txt","tests/test100000-28.txt","tests/test100000-29.txt","tests/test100000-3.txt","tests/test100000-4.txt","tests/test100000-5.txt","tests/test100000-6.txt","tests/test100000-7.txt","tests/test100000-8.txt","tests/test100000-9.txt","tests/testv2-100000-0.txt","tests/testv2-100000-1.txt","tests/testv2-100000-10.txt","tests/testv2-100000-11.txt","tests/testv2-100000-12.txt","tests/testv2-100000-13.txt","tests/testv2-100000-14.txt","tests/testv2-100000-15.txt","tests/testv2-100000-16.txt","tests/testv2-100000-17.txt","tests/testv2-100000-18.txt","tests/testv2-100000-19.txt","tests/testv2-100000-2.txt","tests/testv2-100000-20.txt","tests/testv2-100000-21.txt","tests/testv2-100000-22.txt","tests/testv2-100000-23.txt","tests/testv2-100000-24.txt","tests/testv2-100000-25.txt","tests/testv2-100000-26.txt","tests/testv2-100000-27.txt","tests/testv2-100000-28.txt","tests/testv2-100000-29.txt","tests/testv2-100000-3.txt","tests/testv2-100000-4.txt","tests/testv2-100000-5.txt","tests/testv2-100000-6.txt","tests/testv2-100000-7.txt","tests/testv2-100000-8.txt","tests/testv2-100000-9.txt","tests/testv2-1000000-0.txt","tests/testv2-1000000-1.txt","tests/testv2-1000000-10.txt","tests/testv2-1000000-11.txt","tests/testv2-1000000-12.txt","tests/testv2-1000000-13.txt","tests/testv2-1000000-14.txt","tests/testv2-1000000-15.txt","tests/testv2-1000000-16.txt","tests/testv2-1000000-17.txt","tests/testv2-1000000-18.txt","tests/testv2-1000000-19.txt","tests/testv2-1000000-2.txt","tests/testv2-1000000-20.txt","tests/testv2-1000000-21.txt","tests/testv2-1000000-22.txt","tests/testv2-1000000-23.txt","tests/testv2-1000000-24.txt","tests/testv2-1000000-25.txt","tests/testv2-1000000-26.txt","tests/testv2-1000000-27.txt","tests/testv2-1000000-28.txt","tests/testv2-1000000-29.txt","tests/testv2-1000000-3.txt","tests/testv2-1000000-4.txt","tests/testv2-1000000-5.txt","tests/testv2-1000000-6.txt","tests/testv2-1000000-7.txt","tests/testv2-1000000-8.txt","tests/testv2-1000000-9.txt","tests/testv2-20-0.txt","tests/testv2-20-1.txt","tests/testv2-20-10.txt","tests/testv2-20-11.txt","tests/testv2-20-12.txt","tests/testv2-20-13.txt","tests/testv2-20-14.txt","tests/testv2-20-15.txt","tests/testv2-20-16.txt","tests/testv2-20-17.txt","tests/testv2-20-18.txt","tests/testv2-20-19.txt","tests/testv2-20-2.txt","tests/testv2-20-20.txt","tests/testv2-20-21.txt","tests/testv2-20-22.txt","tests/testv2-20-23.txt","tests/testv2-20-24.txt","tests/testv2-20-25.txt","tests/testv2-20-26.txt","tests/testv2-20-27.txt","tests/testv2-20-28.txt","tests/testv2-20-29.txt","tests/testv2-20-3.txt","tests/testv2-20-4.txt","tests/testv2-20-5.txt","tests/testv2-20-6.txt","tests/testv2-20-7.txt","tests/testv2-20-8.txt","tests/testv2-20-9.txt"};
int main(){
    outtable.open("output.txt");
    double beta = 0.3;
    int cnt = 0;
    for(string filename:filenames){
        std::ifstream input;
        input.open(filename);
        int n;
        {string s;
        stringstream ss;
        std::getline(input,s);
        ss << s;
        ss >> n;
        }
        vector<vector<int>> g(n,vector<int>());
        parlay::sequence<parlay::sequence<int>> g2(n,parlay::sequence<int>());
        for(int i =0;i<n;i++){
            string s;
            stringstream ss;
            std::getline(input,s);
            ss << s;
            while (ss){
                int neighbor;
                ss >> neighbor;
                if (!ss){
                    break;
                }
                g[i].push_back(neighbor);
                g[neighbor].push_back(i);
                g2[i].push_back(neighbor);
                g2[neighbor].push_back(i);
            }
        }
        outtable << filename << "," << test_parallel(g2,beta) 
            << "," << test_parallel_arb(g2,beta) << "," << test_sequential(g,beta) << "\n";
        cout << cnt << endl;
        cnt ++;
    }    
}