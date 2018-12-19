/*
 * Copyright (c) 2014 Matt Fichman
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

#pragma once

#include "coro/Common.hpp"
#include "coro/Event.hpp"

namespace coro {

typedef std::function<void()> SelectorFunc;

class SelectorRecord {
public:
    SelectorRecord(Ptr<Event> event, SelectorFunc func, EventWaitToken token);

    Ptr<Event> event() const { return event_; }
    SelectorFunc func() const { return func_; }
    EventWaitToken token() const { return token_; }

private:
    Ptr<Event> event_;
    SelectorFunc func_; 
    EventWaitToken token_;
};

class Selector {
public:
    ~Selector();
    Selector& on(Ptr<Event> event, SelectorFunc func);

private:
    std::vector<SelectorRecord> record_; 
};


}
