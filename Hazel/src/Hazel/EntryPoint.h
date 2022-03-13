#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initilized log!");
	HZ_INFO("Initilized log!");

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
	return 0;
}
#endif