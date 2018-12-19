/*
 * Copyright (c) 2013 Matt Fichman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, APEXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "coro/Common.hpp"
#include "coro/Event.hpp"
#include "coro/Hub.hpp"

namespace coro {


EventRecord::EventRecord(Ptr<Coroutine> coro) {
    coroutine_ = coro;
}

EventRecord::EventRecord() {
}

void Event::notifyAll() {
    std::vector<EventRecord> waiter;
    waiter.swap(waiter_);
    for (auto record : waiter) {
        if (record.coroutine()) {
            record.coroutine()->notify();
        }
    }
    assert(waiter_.size()==0);
}

void Event::wait() {
    waiter_.push_back(EventRecord(current()));
    current()->wait();
}

size_t Event::waitToken(Ptr<Coroutine> waiter) {
    waiter_.push_back(EventRecord(current()));
    return waiter_.size()-1;
}

bool Event::waitTokenValid(Ptr<Coroutine> waiter, EventWaitToken token) {
    if (token < waiter_.size()) {
        return waiter_[token].coroutine() == waiter;
    } else {
        return false;
    }
}

void Event::waitTokenDel(EventWaitToken token) {
    assert(size_t(token) < waiter_.size() && "invalid wait token");
    waiter_[token] = EventRecord();
}

}
