#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class HazelEditor : public Application
	{
	public:
		HazelEditor()
			: Application("HazelEditor")
		{
			PushLayer(new EditorLayer());
		}

		~HazelEditor() { }

	};

	Application* CreateApplication()
	{	
		return new HazelEditor();
	}
}