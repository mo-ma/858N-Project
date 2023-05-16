#include "parlay/parallel.h"
#include "parlay/primitives.h"
#include "parlay/sequence.h"
#include <iostream>
#include<atomic>

namespace lddarb{
    parlay::sequence<int> get_exps(int n, double beta) {
        parlay::random_generator gen;
        std::exponential_distribution<double> dis(beta);    
        auto result = parlay::tabulate(n, [&](size_t i) {
            auto r = gen[i];
            return int(dis(r));
        });
        return result;
    }

    template <typename T>
    void print_seq(parlay::sequence<T> seq) {
        for(auto x:seq) {
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
    }

    template <typename BinaryPredicate>
    parlay::sequence<size_t> edge_map(parlay::sequence<parlay::sequence<std::pair<size_t,size_t> > > &edges,
                parlay::sequence<size_t> &F, BinaryPredicate&& lambda) {
        
        auto cur_edges = parlay::map(F, [&] (size_t v) {
            return edges[v];
        });

        auto all_edges = parlay::flatten(cur_edges);

        all_edges = parlay::filter(all_edges, [&] (std::pair<size_t,size_t> edge) {
            return lambda(edge.first, edge.second);
        });
        
        auto new_vertices = parlay::map(all_edges, [&] (std::pair<size_t,size_t> edge) {
            return edge.second;
        });

        return new_vertices;
    }


    parlay::sequence<int> get_LDD(parlay::sequence<parlay::sequence<int>> &edges, double beta) {
        beta = beta/2;
        size_t n = edges.size();

        auto zipped_edges = parlay::map(parlay::iota(n), [&] (size_t u) {
            return parlay::map(edges[u], [&] (size_t v) {
                return std::make_pair(u, v);
            });
        });


        auto delta = get_exps(n, beta);
        auto t = parlay::sequence<int>(n);
        auto tf = parlay::sequence<std::pair<int,size_t> >(n);
        auto c = parlay::sequence<std::atomic<int>>(n);

        auto delta_max = parlay::reduce(delta, parlay::maximum<int>());

        parlay::parallel_for(0, n, [&] (size_t i) {
        t[i] = delta_max - delta[i];
        tf[i] = std::make_pair(int(t[i]),i);
        c[i] = -1;
        });

        auto sorted_ids = parlay::group_by_index(tf, delta_max + 1);

        size_t l = 0;
        size_t r = 0;

        auto F = parlay::sequence<size_t>();

        while(l < n) {
            auto new_vertices = parlay::filter(sorted_ids[r], [&] (size_t i) {
                if(c[i] == -1) {
                    c[i] = i;
                    return true;
                }
                return false;
            });
            r++;
            if(new_vertices.size() == 0 && F.size() == 0) continue;
            
            F = parlay::append(F, new_vertices);
            l += F.size();

            F  = edge_map(zipped_edges, F, [&] (size_t u, size_t v) {
                int expected = c[v];
                return expected == -1 && c[v].compare_exchange_strong(expected,c[u]);
            });
        }
        return parlay::map(c, [&] (int x) {
            return x;
        });
    }
}