#ifndef NW_ENGINE_STATE_H
#define NWL_ENGINE_STATE_H

#include <nwl_core.hpp>

namespace NWL
{
	/// CoreState class
	class NWL_API EngineState
	{
	public:
		virtual ~EngineState() = default;

		// --getters
		virtual inline const char* GetName() = 0;
		// --setters
		// --core_methods
		virtual bool Init() = 0;
		virtual void OnQuit() = 0;
		virtual void Update() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnEvent(MouseEvent& rmEvt) = 0;
		virtual void OnEvent(KeyboardEvent& rkEvt) = 0;
		virtual void OnEvent(WindowEvent& rwEvt) = 0;
	};
}
#endif	// NWL_ENGINE_STATE_H