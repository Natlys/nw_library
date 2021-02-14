#ifndef NWL_ENGINE_H
#define NWL_ENGINE_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>
#include <nwl_io.hpp>

#include <core/nwl_container.h>
#include <core/nwl_singleton.h>
#include <core/nwl_thread.h>

namespace NWL
{
	/// AEngineState class
	/// Description:
	/// -- This is the main interaction part for the engine.
	/// -- State handles Lua virtual machiene which allows to use Lua scripts
	class NWL_API AEngineState
	{
	public:
		AEngineState(const char* strName) : m_strName(strName) {}
		virtual ~AEngineState() = default;

		// --getters
		virtual inline const char* GetName() { return m_strName; }
		// --setters
		// --core_methods
		virtual bool Init() = 0;
		virtual void Quit() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(CursorEvent& rmEvt) = 0;
		virtual void OnEvent(KeyboardEvent& rkEvt) = 0;
		virtual void OnEvent(WindowEvent& rwEvt) = 0;
	protected:
		const char* m_strName;
	};
}
namespace NWL
{
	template<class EType, class SType = AEngineState>
	class AEngine : public ASingleton<EType>
	{
	public:
		using States = DArray<SType*>;
	public:
		AEngine() :
			m_thrRun(Thread()), m_bIsRunning(false),
			m_kbd(Keyboard()), m_crs(Cursor()) { }
		AEngine(const AEngine& rCpy) = delete;
		virtual ~AEngine() { }
		// --getters
		inline Thread& GetRunThread() { return m_thrRun; }
		inline States& GetStates() { return m_States; }
		inline SType* GetState(UInt32 unIdx) { return m_States[unIdx]; }
		// --setters
		inline void AddState(SType& rState);
		inline void RmvState(UInt32 unIdx);
		inline void StopRunning() { m_bIsRunning = false; }
		// --predicates
		inline Bit IsRunning() const { return m_bIsRunning; }
		// --core_methods
		void Run();
		bool Init();
		void Quit();
		void Update();
		void OnEvent(AEvent& rEvt);
	protected:
		Thread m_thrRun;
		Bit m_bIsRunning;
		States m_States;
		KeyboardT<KC_COUNT> m_kbd;
		CursorT<CRS_COUNT> m_crs;
	};
	// --setters
	template<class EType, class SType>
	inline void AEngine<EType, SType>::AddState(SType& rState) { m_States.push_back(&rState); }
	template<class EType, class SType>
	inline void AEngine<EType, SType>::RmvState(UInt32 unIdx) { if (m_States.size() <= unIdx) { return; } m_States.erase(m_States.begin() + unIdx); }
	// --core_methods
	template<class EType, class SType>
	void AEngine<EType, SType>::Run()
	{
		Init();
		if (!m_bIsRunning) { return; }
		if (m_States.empty()) { Quit(); }

		auto fnRunLoop = [this]()->void { while (m_bIsRunning) { Update(); } Quit(); };
		m_thrRun = Thread(fnRunLoop);
	};
	template<class EType, class SType>
	bool AEngine<EType, SType>::Init()
	{
		return true;
	}
	template<class EType, class SType>
	void AEngine<EType, SType>::Quit()
	{
	}
	template<class EType, class SType>
	void AEngine<EType, SType>::Update()
	{
	}
	template<class EType, class SType>
	void AEngine<EType, SType>::OnEvent(AEvent& rEvt)
	{
	}
}

#endif	// NWL_ENGINE_H