// user includes
#include "test_runner.h"
// system includes
#include <numeric>
#include <iostream>
#include <vector>
#include <string>

template <typename Iterator>
class Paginator {
public:
    Paginator(Iterator iterator_begin, Iterator iterator_end, size_t page_size) {
        if (page_size <= 0 || iterator_begin == iterator_end)
            return;
        
        const size_t items = std::distance(iterator_begin, iterator_end);
        const size_t full_pages = items / page_size;
        const size_t items_last_page = items - page_size * full_pages;
        
        for (size_t i = 0; i < full_pages; ++i) {
            const auto cur_end = std::next(iterator_begin, page_size);
            pages.emplace_back(Page(iterator_begin, cur_end));
            iterator_begin = cur_end;
        }
        
        if (items_last_page != 0)
            pages.emplace_back(Page(iterator_begin, std::next(iterator_begin, items_last_page)));
    }
    [[nodiscard]] size_t size() const { return pages.size(); }
    [[nodiscard]] auto begin() const { return pages.begin(); }
    [[nodiscard]] auto end() const { return pages.end(); }
private:
    class Page {
    public:
        Page (Iterator begin_, Iterator end_) : i1(begin_), i2(end_), elems(std::distance(i1, i2)) {}
        [[nodiscard]] Iterator begin() const {return i1;}
        [[nodiscard]] Iterator end() const {return i2;}
        [[nodiscard]] size_t size() const {return elems;}
    private:
        const Iterator i1, i2;
        const size_t elems;
    };
    std::vector<Page> pages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
    return Paginator(c.begin(), c.end(), page_size);
}

void TestPageCounts() {
    
    {
        std::vector<int> v(15);
    
        ASSERT_EQUAL(Paginate(v, 0).size(), 0);
        ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
        ASSERT_EQUAL(Paginate(v, 2).size(), 8);
        ASSERT_EQUAL(Paginate(v, 3).size(), 5u);
        ASSERT_EQUAL(Paginate(v, 4).size(), 4u);
        ASSERT_EQUAL(Paginate(v, 5).size(), 3u);
        ASSERT_EQUAL(Paginate(v, 6).size(), 3u);
        ASSERT_EQUAL(Paginate(v, 7).size(), 3u);
        ASSERT_EQUAL(Paginate(v, 8).size(), 2u);
        ASSERT_EQUAL(Paginate(v, 14).size(), 2u);
        ASSERT_EQUAL(Paginate(v, 15).size(), 1u);
        ASSERT_EQUAL(Paginate(v, 150).size(), 1u);
    }
    
    {
        std::vector<int> v(1);
    
        ASSERT_EQUAL(Paginate(v, 0).size(), 0);
        ASSERT_EQUAL(Paginate(v, 1).size(), v.size());
        ASSERT_EQUAL(Paginate(v, 2).size(), 1);
        ASSERT_EQUAL(Paginate(v, 3).size(), 1);
        ASSERT_EQUAL(Paginate(v, 4).size(), 1);
        ASSERT_EQUAL(Paginate(v, 5).size(), 1);
        ASSERT_EQUAL(Paginate(v, 6).size(), 1);
        ASSERT_EQUAL(Paginate(v, 7).size(), 1);
        ASSERT_EQUAL(Paginate(v, 8).size(), 1);
        ASSERT_EQUAL(Paginate(v, 14).size(), 1);
        ASSERT_EQUAL(Paginate(v, 15).size(), 1);
        ASSERT_EQUAL(Paginate(v, 150).size(), 1);
    }
    
    {
        std::vector<int> v;
    
        ASSERT_EQUAL(Paginate(v, 0).size(), 0);
        ASSERT_EQUAL(Paginate(v, 1).size(), 0);
        ASSERT_EQUAL(Paginate(v, 2).size(), 0);
        ASSERT_EQUAL(Paginate(v, 3).size(), 0);
        ASSERT_EQUAL(Paginate(v, 4).size(), 0);
        ASSERT_EQUAL(Paginate(v, 5).size(), 0);
        ASSERT_EQUAL(Paginate(v, 6).size(), 0);
        ASSERT_EQUAL(Paginate(v, 7).size(), 0);
        ASSERT_EQUAL(Paginate(v, 8).size(), 0);
        ASSERT_EQUAL(Paginate(v, 14).size(), 0);
        ASSERT_EQUAL(Paginate(v, 15).size(), 0);
        ASSERT_EQUAL(Paginate(v, 150).size(), 0);
    }
}

void TestLooping() {
    std::vector<int> v(15);
    iota(begin(v), end(v), 1);
    
    Paginator<std::vector<int>::iterator> paginate_v(v.begin(), v.end(), 6);
    std::ostringstream os;
    for (const auto& page : paginate_v) {
        for (int x : page) {
            os << x << ' ';
        }
        os << '\n';
    }
    
    ASSERT_EQUAL(os.str(), "1 2 3 4 5 6 \n7 8 9 10 11 12 \n13 14 15 \n");
}

void TestModification() {
    std::vector<std::string> vs = {"one", "two", "three", "four", "five"};
    for (auto page : Paginate(vs, 2)) {
        for (auto& word : page) {
            word[0] = toupper(word[0]);
        }
    }
    
    const std::vector<std::string> expected = {"One", "Two", "Three", "Four", "Five"};
    ASSERT_EQUAL(vs, expected);
}

void TestPageSizes() {
    std::string letters(26, ' ');
    
    Paginator letters_pagination(letters.begin(), letters.end(), 11);
    std::vector<size_t> page_sizes;
    for (const auto& page : letters_pagination) {
        page_sizes.push_back(page.size());
    }
    
    const std::vector<size_t> expected = {11, 11, 4};
    ASSERT_EQUAL(page_sizes, expected);
}

void TestConstContainer() {
    const std::string letters = "abcdefghijklmnopqrstuvwxyz";
    
    std::vector<std::string> pages;
    for (const auto& page : Paginate(letters, 10)) {
        pages.push_back(std::string(page.begin(), page.end()));
    }
    
    const std::vector<std::string> expected = {"abcdefghij", "klmnopqrst", "uvwxyz"};
    ASSERT_EQUAL(pages, expected);
}

void TestPagePagination() {
    std::vector<int> v(22);
    iota(begin(v), end(v), 1);
    
    std::vector<std::vector<int>> lines;
    for (const auto& split_by_9 : Paginate(v, 9)) {
        for (const auto& split_by_4 : Paginate(split_by_9, 4)) {
            lines.push_back({});
            for (int item : split_by_4) {
                lines.back().push_back(item);
            }
        }
    }
    
    const std::vector<std::vector<int>> expected = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9},
        {10, 11, 12, 13},
        {14, 15, 16, 17},
        {18},
        {19, 20, 21, 22}
    };
    ASSERT_EQUAL(lines, expected);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPageCounts);
    RUN_TEST(tr, TestLooping);
    RUN_TEST(tr, TestModification);
    RUN_TEST(tr, TestPageSizes);
    RUN_TEST(tr, TestConstContainer);
    RUN_TEST(tr, TestPagePagination);
}
