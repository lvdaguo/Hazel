#pragma once

// 预编译头文件，必须放在每个cpp文件的顶部
// 加快编译速度

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Hazel/Log.h"

#ifdef HZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif