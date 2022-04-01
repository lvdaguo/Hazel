#pragma once

// For use by Hazel applications

#include "Hazel/Core/Core.h"

#include "Hazel/Application.h"
#include "Hazel/Core/Log.h"

#include "Hazel/Core/Timestep.h"

#include "Hazel/Core/Input.h"
#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Core/MouseCodes.h"
#include "Hazel/Renderer/OrthographicCameraController.h"

#include "Hazel/ImGui/ImGuiLayer.h"

// --- Renderer ------
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/FrameBuffer.h"
#include "Hazel/Renderer/Texture.h"
#include "Hazel/Renderer/VertexArray.h"

#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Renderer/RenderCommand.h"

#include "Hazel/Renderer/OrthographicCamera.h"
// -------------------

// --- Entry Point ---
//#include "Hazel/Core/EntryPoint.h"
// -------------------

// EntryPoint头文件为一段main函数，被用户程序包含后，作为程序的入口
// 用户只需继承Application类，实现其CreateApplication方法，即可运行游戏