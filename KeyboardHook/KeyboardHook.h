
#ifdef KEY_HOOKED_EXPORTS
#define KEY_HOOKED_API __declspec(dllexport) 
#else
#define KEY_HOOKED_API __declspec(dllimport) 
#endif

namespace keyboard{
	class myKeyboard{
		public:
			static KEY_HOOKED_API bool SetHook();
			static KEY_HOOKED_API bool UnsetHook();
	};
}