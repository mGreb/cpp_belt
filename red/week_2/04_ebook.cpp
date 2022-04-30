// system includes
#include <iomanip>
#include <iostream>
#include <vector>

class ReadingManager {
public:
    ReadingManager()
    : num_pages_user_read(MAX_USER_COUNT_ + 1, -1),
      num_users_reading_this_page(MAX_PAGES_COUNT_ + 1, 0) {}
    
    void Read(int user_id, int page_count) {
        if (num_pages_user_read[user_id] == -1) {
            ++total_users;
            num_pages_user_read[user_id] = page_count;
            num_users_reading_this_page[page_count] += 1;
        } else {
            const int old_pages = num_pages_user_read[user_id];
            num_users_reading_this_page[old_pages] -= 1;
            num_pages_user_read[user_id] = page_count;
            num_users_reading_this_page[page_count] += 1;
        }
    }
    
    [[nodiscard]]
    double Cheer(int user_id) const {
        if (num_pages_user_read[user_id] == -1)
            return 0;
        
        if (total_users == 1)
            return 1;
        
        int cnt = 0;
        for (int i = 1; i < num_pages_user_read[user_id]; ++i)
            cnt += num_users_reading_this_page[i];
        
        return (double) cnt / (total_users - 1);
    }
    
private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGES_COUNT_ = 1'000;
    
    std::vector<int> num_pages_user_read;  // number of pages user has read
    std::vector<int> num_users_reading_this_page;  // number of users that read this page
    int total_users = 0;
};


/*
12
CHEER 5
READ 1 10
CHEER 1
READ 2 5
READ 3 7
CHEER 2
CHEER 3
READ 3 10
CHEER 3
READ 3 11
CHEER 3
CHEER 1

0
1
0
0.5
0.5
1
0.5
*/

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    ReadingManager manager;
    
    int query_count;
    std::cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;
        
        if (query_type == "READ") {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    
    return 0;
}