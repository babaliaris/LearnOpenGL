#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

namespace Engine
{
	class Input
	{

		friend class Application;

	public:

		inline static Input& Get() { return *s_Instance; }

		bool KeyPress(int keycode);
		bool KeyRelease(int keycode);
		bool MousePress(int button);
		bool MouseRelease(int button);

		float GetMouseX();
		float GetMouseY();
		float GetScroll();




	private:
		static float s_scrollX, s_scrollY;
		static Input* s_Instance;

	};

}

#endif ENGINE_INPUT_H

