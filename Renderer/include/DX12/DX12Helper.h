/*
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
#include <comdef.h>
#include <string>
#include <windows.h>

/**
 * \brief This function convert string to wstring
 * \param str  standard string to be convert
 * \return return the string convert to wstring
 */
inline std::wstring AnsiToWString(const std::string &str)
{
    WCHAR buffer[512];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, buffer, 512);
    return std::wstring(buffer);
}

class DX12Exception
{
  public:
    DX12Exception() = default;
    DX12Exception(HRESULT             hr,
                  const std::wstring &functionName,
                  const std::wstring &filename,
                  int                 lineNumber);

    std::wstring ToString() const
    {
        return functionName + L" failed in " + fileName + L"; line " + std::to_wstring(lineNumber);
    }

    HRESULT      errCode = S_OK;
    std::wstring functionName;
    std::wstring fileName;
    INT32        lineNumber = -1;
};

inline DX12Exception::DX12Exception(HRESULT             hr,
                                    const std::wstring &functionName,
                                    const std::wstring &filename,
                                    int                 lineNumber)
    : errCode{hr}, functionName{functionName}, fileName{filename}, lineNumber{lineNumber}
{
}

#ifndef CHECK_DX12_RESULT
#define CHECK_DX12_RESULT(x)                                                                       \
    {                                                                                              \
        HRESULT hr = (x);                                                                          \
        if (FAILED(hr))                                                                            \
        {                                                                                          \
            std::wstring wfn = AnsiToWString(__FILE__);                                            \
            throw DX12Exception(hr, L#x, wfn, __LINE__);                                           \
        }                                                                                          \
    }
#endif