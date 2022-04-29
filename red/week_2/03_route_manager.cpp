// system includes
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <set>


class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    [[nodiscard]]
    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        if (reachable_lists_.find(start) == reachable_lists_.end())
            return result;
        
        const std::set<int>& reachable_stations = reachable_lists_.at(start);
        
        auto it = reachable_stations.lower_bound(finish);
        
        if (it == reachable_stations.end())  // if end, then last element is the closest
            return std::min(result, abs(finish - *std::prev(it)));
        
        // if not, need to look at both elements
        const int dist1 = abs(finish - *it);
        int dist2 = dist1;
        if(it != reachable_stations.begin())
            dist2 = abs(finish - *std::prev(it));
        
        return std::min(result, std::min(dist1, dist2));
    }
private:
    std::map<int, std::set<int>> reachable_lists_;
};

/*
7
ADD -2 5
ADD 10 4
ADD 5 8
GO 4 10
GO 4 -2
GO 5 0
GO 5 100

0
6
2
92
*/

int main() {
    RouteManager routes;
    
    int query_count;
    std::cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        int start, finish;
        std::cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        } else if (query_type == "GO") {
            std::cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }
    
    return 0;
}
