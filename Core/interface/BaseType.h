﻿/**
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

#pragma once
#ifndef HAWL_BASETYPE_H
#  define HAWL_BASETYPE_H
#  include <cstddef>
#  include <cstdint>

namespace Hawl {
/// int 类型跨平台封装
typedef int     INT;
typedef int8_t  INT8;
typedef int16_t INT16;
typedef int32_t INT32;
typedef int64_t INT64;
typedef long    LONG;

///	unsigned int 类型跨平台封装
typedef unsigned int UINT;
typedef uint8_t      UINT8;
typedef uint16_t     UINT16;
typedef uint32_t     UINT32;
typedef uint64_t     UINT64;

/// 浮点类型封装
typedef float  FLOAT32;
typedef double FLOAT64;

/// bool类型封装
typedef bool BOOL;
// 这里使用 static 定义 FALSE 而不是
// 使用宏， 宏会与其他头文件中定义冲突
static BOOL FALSE = false;
static BOOL TRUE  = true;
// char 类型封装
typedef char CHAR;

/// size_t 空指针封装
typedef size_t      SIZETYPE;
typedef void*       PVOID;
typedef const void* CPVOID;

// 引用计数类型包装
typedef UINT64 RefCount;
}

#endif // !HAWL_BASE_TYPE