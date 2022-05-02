// user includes
#include "test_runner.h"
// system includes
#include <queue>

class Booking {
public:
    void book(long long int time, const std::string &hotel_name, size_t client_id, size_t room_count) {
        q.push({time, client_id, room_count, hotel_name});
        hotels[hotel_name].rooms += room_count;
        hotels[hotel_name].clients_rooms[client_id] += room_count;
        
        while (!q.empty() && std::abs(q.front().time - q.back().time) >= seconds_in_day) {  // O(Q * L * logQ)
            Record &r = q.front();
            auto &hotel_data = hotels[r.hotel_name];
            hotel_data.rooms -= r.room_count;
            
            if (hotel_data.clients_rooms[r.client_id] == r.room_count)
                hotel_data.clients_rooms.erase(r.client_id);
            else
                hotel_data.clients_rooms[r.client_id] -= r.room_count;
            
            
            q.pop();
        }
    }
    
    size_t clients(const std::string &hotel_name) {  // O(L * logQ)
        const auto it = hotels.find(hotel_name);
        if (it != hotels.end())
            return it->second.clients_rooms.size();
        return 0;
    }
    
    size_t rooms(const std::string &hotel_name) {  // O(L * logQ)
        const auto it = hotels.find(hotel_name);
        if (it != hotels.end())
            return it->second.rooms;
        return 0;
    }
private:
    long long int seconds_in_day = 86400;
    struct Record {
        long long int time = 0;
        size_t client_id = 0;
        size_t room_count = 0;
        std::string hotel_name;
    };
    std::queue<Record> q;
    struct RoomsClients {
        size_t rooms = 0;  // total booked rooms
        std::map<size_t, size_t> clients_rooms;  // how many rooms this client booked
    };
    std::map<std::string, RoomsClients> hotels;
};

void TestCoursera() {
    Booking b;
    
    ASSERT_EQUAL(b.clients("Marriott"), 0);
    ASSERT_EQUAL(b.rooms("Marriott"), 0);
    b.book(10, "FourSeasons", 1, 2);
    b.book(10, "Marriott", 1, 1);
    b.book(86409, "FourSeasons", 2, 1);
    AssertEqual(b.clients("FourSeasons"), 2);
    AssertEqual(b.rooms("FourSeasons"), 3);
    AssertEqual(b.clients("Marriott"), 1);
    b.book(86410, "Marriott", 2, 10);
    AssertEqual(b.rooms("FourSeasons"), 1);
    AssertEqual(b.rooms("Marriott"), 10);
}

void TestOneClient() {
    Booking b;
    
    b.book(-10, "Tango", 1, 10);
    b.book(-10, "Delta", 1, 10);
    ASSERT_EQUAL(b.clients("Tango"), 1);
    ASSERT_EQUAL(b.rooms("Tango"), 10);
    b.book(100000, "Tango", 1, 2);
    ASSERT_EQUAL(b.clients("Tango"), 1);
    ASSERT_EQUAL(b.clients("Delta"), 0);
    ASSERT_EQUAL(b.rooms("Tango"), 2);
}

void RunTests() {
    TestRunner tr;
    tr.RunTest(TestCoursera, "TestCoursera");
    tr.RunTest(TestOneClient, "TestOneClient");
}

int main() {
//    RunTests(); return 0;
    Booking b;
    size_t n = 0;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "BOOK") {
            long long int time = 0;
            std::cin >> time;
            std::string hotel_name;
            std::cin >> hotel_name;
            size_t client_id;
            std::cin >> client_id;
            size_t room_count;
            std::cin >> room_count;
            b.book(time, hotel_name, client_id, room_count);
        } else if (command == "CLIENTS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << b.clients(hotel_name) << "\n";
        } else if (command == "ROOMS") {
            std::string hotel_name;
            std::cin >> hotel_name;
            std::cout << b.rooms(hotel_name) << "\n";
        }
    }
    return 0;
}
