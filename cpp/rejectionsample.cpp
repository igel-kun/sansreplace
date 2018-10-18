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
#include <unordered_set>

#include "randbelow.h"
#include "testfunc.h"

void rejectionsample(uint32_t n, uint32_t k, uint32_t* result) {
    std::unordered_set<uint32_t> done(2*k);
    for (uint32_t i = 0; i < k;) {
        uint32_t r = randbelow(n);
        if (done.find(r) == done.end()) {
            done.insert(r);
            result[i++] = r;
        }
    }
}
