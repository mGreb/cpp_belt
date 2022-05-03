// user includes
#include "test_runner.h"
// system includes
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (deallocated.empty()) {  // create new object
            T* new_object = new T;
            allocated.insert(new_object);
            return new_object;
        }
        else {  // reuse free object
            T* object = deallocated.front();
            deallocated.pop();
            allocated.insert(object);
            return object;
        }
    }
    
    T* TryAllocate() {
        if (deallocated.empty())
            return nullptr;
        
        return Allocate();
    }
    
    void Deallocate(T* object) {
        const auto it = allocated.find(object);
        if (it == allocated.end())
            throw std::invalid_argument("Object is not allocated");
        
        allocated.erase(object);
        deallocated.push(object);
    }
    
    ~ObjectPool() {
        for (T* object : allocated)
            delete object;
        
        while (!deallocated.empty()) {
            T* object = deallocated.front();
            deallocated.pop();
            delete object;
        }
    }
    
private:
    std::set<T*> allocated;
    std::queue<T*> deallocated;
};

void TestObjectPool() {
    ObjectPool<std::string> pool;
    
    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();
    
    *p1 = "first";
    *p2 = "second";
    *p3 = "third";
    
    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");
    
    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");
    
    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
    return 0;
}
