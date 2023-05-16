#include<bits/stdc++.h>
using namespace std;

const int MN = 1e6 + 100;
int maxn;
int average_deg;
bool mark[MN];
void generate_graph(int i){
    ofstream file;
    stringstream filestream;
    filestream<<"output/testv2-" << maxn << "-" << i << ".txt";
    string filename = filestream.str();
    file.open(filename);
    file << maxn << "\n";
    file << "\n";
    for(int i =1;i<maxn;i++){
        vector<int> neighbors;
        int par = -1;
        par = rand() % i;
        neighbors.push_back(par);
        mark[par] = true;
        while(rand() < 1.0 * RAND_MAX / average_deg){
            int neighbor = rand() % i;
            if (!mark[neighbor]){
                neighbors.push_back(neighbor);
                mark[neighbor] = true;
            }
        }
        for (int i = 0;i<neighbors.size();i++){
            int v = neighbors[i];
            mark[v] = false;
            if (i+1 < neighbors.size()){
                file << v << " ";
            }else{
                file << v;
            }
        }
        file << "\n";
    }
}
int main(){
    cin >> maxn >> average_deg;
    for (int i =0;i<30;i++){
        generate_graph(i);
    }
}