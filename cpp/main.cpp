/*
 * Copyright 2018 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

#include "randbelow.h"
#include "testfunc.h"

static std::chrono::duration<double> timefunc(int iters, int n, int k,
    void (*func)(int n, int k, int *result)) {
    auto result = std::vector<int>(n);
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < iters; i++) {
        func(n, k, &result[0]);
    }
    auto end = std::chrono::system_clock::now();
    return end - start;
}

static int choose_iters(
    std::chrono::duration<double> totake,
    int n, int k,
    void (*func)(int n, int k, int *result)) {
    int iters = 1;
    for (;;) {
        auto t = timefunc(iters, n, k, func);
        if (t * 10 >= totake) {
            return std::max(1, static_cast<int>(totake * iters / t));
        }
        iters *= 10;
    }
}

static std::chrono::duration<double> timefunc_for(
    std::chrono::duration<double> totake,
    int n, int k,
    void (*func)(int n, int k, int *result)) {
    int iters = choose_iters(totake, n, k, func);
    auto t = timefunc(iters, n, k, func);
    return t / iters;
}

struct timeable {
    std::string name;
    void (*func)(int n, int k, int *result);
};

struct timeable totime[] = {
//    {"donothing", donothing},
    {"fisheryates", fisheryates},
    {"floydf2", floydf2},
    {"iterativechoose", iterativechoose},
    {"rejectionsample", rejectionsample},
    {"selby_fy", selby_fy},
    {"", nullptr}
};

static void time_all(int n, int k) {
    std::chrono::seconds sec(1);
    auto base_time_s = timefunc_for(sec, n, k, cardchoose).count();
    std::cout << "cardchoose" << std::endl;
    std::cout << "    " << base_time_s << " s" << std::endl;
    std::cout << "    " << base_time_s/k << " s/k" << std::endl;
    std::cout << "    " << base_time_s/n << " s/n" << std::endl;

    struct timeable *tm;
    for (tm = totime; tm->func; tm++) {
        auto time_s = timefunc_for(sec, n, k, tm->func).count();
        std::cout << tm->name << std::endl;
        std::cout << "    " << time_s << " s" << std::endl;
        std::cout << "    " << time_s/k << " s/k" << std::endl;
        std::cout << "    " << time_s/n << " s/n" << std::endl;
        std::cout << "    " << time_s / base_time_s << " vs cardchoose" << std::endl;
    }
}

int main() {
    rand_init();
    for (int n = 10; n < 10000000; n *= 10) {
        for (int k = 8; k < n; k *= 10) {
            std::cout << "n, k = " << n << ", " << k << std::endl;
            time_all(n, k);
            std::cout << std::endl;
        }
    }
    return 0;
}
