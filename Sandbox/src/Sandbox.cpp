#include "Hazel.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox() = default;
	~Sandbox() = default;
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}