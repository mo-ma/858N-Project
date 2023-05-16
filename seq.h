#include<vector>
#include<queue>
std::pair<std::vector<int>,int> edge_map(std::vector<std::vector<int>>& g, std::vector<int> frontier, std::vector<int>& center){
    std::vector<int> new_frontier;
    int new_edges = 0;
    for(int v:frontier){
        for(int u:g[v]){
            if(center[u] == -1){
                new_frontier.push_back(u);
                center[u] = -2;
            }
            if(center[u] == -2){
                new_edges += 1;
            }
        }
    }
    return make_pair(new_frontier,new_edges);
}
void BFS(std::vector<std::vector<int>>& g, int source, std::vector<int>& center, double beta){
    std::vector<int> frontier;
    frontier.push_back(source);
    center[source] = source;
    int edges = 0;
    while (true){
        auto new_pair = edge_map(g,frontier,center);
        if (new_pair.second <= beta * edges){
            for(int u:new_pair.first){
                center[u]=-1;
            }
            return;
        }
        for(int u:new_pair.first){
            center[u]=source;
        }
        frontier = new_pair.first;
        edges += new_pair.second;
    }
}
std::vector<int> sequential_LDD(std::vector<std::vector<int>>& g, double beta){
    int n = g.size();
    std::vector<int> center(n,-1);
    for(int i =0;i<n;i++){
        if(center[i]==-1){
            BFS(g,i, center,beta);
        }
    }
    return center;
}