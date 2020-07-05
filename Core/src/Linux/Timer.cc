/*
 * Copyright (c) 2020 juteman
 *
 * This file is part of ReForge
 * (see https://github.com/juteman/Hawl).
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "Timer.h"
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

namespace Hawl {
UINT32
getMSec()
{
  LONG            ms;  // 毫秒
  time_t          Sec; // 秒
  struct timespec timeSpec;

  clock_gettime(CLOCK_REALTIME, &timeSpec); // 高精度时间函数，可精确到纳秒
  Sec = timeSpec.tv_sec;
  ms  = round(timeSpec.tv_nsec / 1.0e6); // 将纳秒转变为毫秒
  ms += Sec * 1000;

  return (UINT32)ms;
}

INT64
getUSec()
{
  timespec timeSpec;
  clock_gettime(CLOCK_REALTIME, &timeSpec);
  long us = (timeSpec.tv_nsec / 1000); // 将纳秒变为微秒
  us += timeSpec.tv_sec * 1e6;
  return us;
}

UINT32
getTimeSinceStart()
{
  return (UINT32)time(NULL);
}

INT64
getTimerFrequency()
{
  return 1000000LL;
}

/***************************************************
 * 低精度类型 LTimer 的实现
 ***************************************************/
LTimer::LTimer()
{
  Reset();
}

UINT32
LTimer::GetElapsedTime(bool reset)
{
  UINT32 currentTime = getMSec();
  UINT32 elapsedTime = currentTime - m_startTime;
  if (reset) {
    Reset();
  }
  return elapsedTime;
}

void
LTimer::Reset()
{
  m_startTime = getMSec();
}

/***************************************************
 * 高精度类型 HTimer 的实现
 ***************************************************/
HTimer::HTimer()
{
  memset(m_history, 0, sizeof(m_history));
  m_historyIndex = 0;
  Reset();
}

INT64
HTimer::GetElapsedTime(bool reset)
{
  INT64 currentTime = getUSec();
  INT64 elapsedTime = currentTime - m_startTime;

  // 如内部出现异常，修改时间
  if (elapsedTime < 0)
    elapsedTime = 0;

  if (reset)
    m_startTime = currentTime;

  m_history[m_historyIndex] = elapsedTime;
  m_historyIndex            = (m_historyIndex + 1) % LENGTH_OF_HISTORY;

  return elapsedTime;
}

INT64
HTimer::GetElapsedTimeAverage()
{
  INT64 elapsedTime = 0;
  for (UINT32 i = 0; i < LENGTH_OF_HISTORY; ++i)
    elapsedTime += m_history[i];
  elapsedTime /= LENGTH_OF_HISTORY;

  // 如内部出现异常，修改时间
  if (elapsedTime < 0)
    elapsedTime = 0;

  return elapsedTime;
}

FLOAT32
HTimer::GetSeconds(bool reset)
{
  return (FLOAT32)(GetElapsedTime(reset) / 1e6);
}

FLOAT32
HTimer::GetSecondsAverage()
{
  return (FLOAT32)(GetElapsedTimeAverage() / 1e6);
}

void
HTimer::Reset()
{
  m_startTime = getUSec();
}
}