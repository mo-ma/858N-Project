#include<bits/stdc++.h>
using namespace std;


int maxn;
double edge_sensitivity;
int average_deg;
void generate_graph(int i){
    ofstream file;
    stringstream filestream;
    filestream<<"output/test" << maxn << "-" << i << ".txt";
    string filename = filestream.str();
    file.open(filename);
    file << maxn << "\n";
    for(int i =0;i<maxn;i++){
        int par = -1;
        if (i > 0){
            par = rand() % i;
        }
        for(int j=0;j<i;j++){
            if (j == par || rand() < (edge_sensitivity * RAND_MAX)){
                file << j << " ";
            }
        }
        file << "\n";
    }
}
int main(){
    cin >> maxn >> average_deg;
    edge_sensitivity = 1.0 * average_deg / maxn;
    for (int i =0;i<30;i++){
        generate_graph(i);
    }
}