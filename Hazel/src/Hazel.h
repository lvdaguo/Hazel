#pragma once

// For use by Hazel applications

#include "Hazel/Application.h"
#include "Hazel/Log.h"

#include "Hazel/Input.h"
#include "Hazel/KeyCodes.h"
#include "Hazel/MouseButtonCodes.h"

#include "Hazel/ImGui/ImGuiLayer.h"

// --- Entry Point ---
#include "Hazel/EntryPoint.h"
// -------------------

// EntryPoint头文件为一段main函数，被用户程序包含后，作为程序的入口
// 用户只需继承Application类，实现其CreateApplication方法，即可运行游戏