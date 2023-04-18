/*
 * Rosalie's Mupen GUI - https://github.com/Rosalie241/RMG
 *  Copyright (C) 2020 Rosalie Wanders <rosalie@mailbox.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 3.
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */
#define CORE_INTERNAL
#include "Core.hpp"
#include "ConvertStringEncoding.hpp"

#include <iostream>

//
// Local Variables
//

static bool l_SetupCallbacks = false;
static std::function<void(enum CoreDebugMessageType, std::string, std::string)> l_DebugCallbackFunc;
static std::function<void(enum CoreStateCallbackType, int)> l_StateCallbackFunc;
static bool l_PrintCallbacks = false;

//
// Internal Functions
//

void CoreDebugCallback(void* context, int level, const char* message)
{
    if (!l_SetupCallbacks)
    {
        return;
    }

    std::string contextString((const char*)context);
    std::string messageString(message);

    // convert string encoding accordingly
    if (messageString.starts_with("IS64:"))
    {
        messageString = CoreConvertStringEncoding(message, CoreStringEncoding::EUC_JP);
    }
    else
    {
        messageString = CoreConvertStringEncoding(message, CoreStringEncoding::Shift_JIS);
    }

    if (l_PrintCallbacks)
    {
        std::cout << contextString << messageString << std::endl;
    }

    l_DebugCallbackFunc((CoreDebugMessageType)level, contextString, messageString);
}

void CoreStateCallback(void* context, m64p_core_param param, int value)
{
    if (!l_SetupCallbacks)
    {
        return;
    }

    l_StateCallbackFunc((CoreStateCallbackType)param, value);
}

//
// Exported Functions
//

bool CoreSetupCallbacks(std::function<void(enum CoreDebugMessageType, std::string, std::string)> debugCallbackFunc,
                        std::function<void(enum CoreStateCallbackType, int)> stateCallbackFunc)
{
    l_DebugCallbackFunc = debugCallbackFunc;
    l_StateCallbackFunc = stateCallbackFunc;
    l_SetupCallbacks = true;
    return true;
}

void CoreSetPrintDebugCallback(bool enabled)
{
    l_PrintCallbacks = enabled;
}
