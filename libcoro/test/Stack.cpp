

#include <coro/Common.hpp>
#include <coro/coro.hpp>

using namespace coro;

void recurse(int n) {
    char data[10000];
    data[0] = char(n);
    if (n == 0) { return; }
    else { recurse(n-1); }
}


int main() {
    // Check that coroutines do not use too much stack mem
    std::vector<Ptr<Coroutine>> coros;

    for (auto i = 0; i < 10; ++i) {
        for (auto j = 0; j < 1000; ++j) {
            coros.push_back(coro::start(std::bind(recurse, 100)));
        }
        hub()->quiesce();
        coros.clear();
    }

    return 0;
}
