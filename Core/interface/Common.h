/**
 *  Copyright 2020 juteman
 *
 *  This file is a part of Hawl
 *  see(https://github.com/juteman/Hawl)
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifdef _MSC_VER
#  define CDECL __cdecl
#else
#  define CDECL
#endif

namespace Hawl {
class Noncopyable
{
public:
  Noncopyable()  = default;
  ~Noncopyable() = default;

private:
  Noncopyable(const Noncopyable& other) = delete;
  Noncopyable& operator=(const Noncopyable& other) = delete;
};
}
