#ifndef NWL_ENGINE_H
#define NWL_ENGINE_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>
#include <nwl_io.hpp>

#include <utility/nwl_container.h>
#include <utility/nwl_singleton.h>
#include <utility/nwl_thread.h>

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
		virtual void OnQuit() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(MouseEvent& rmEvt) = 0;
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
		AEngine() : m_thrRun(Thread()), m_Memory(nullptr, 0), m_bIsRunning(false) {}
		AEngine(const AEngine& rCpy) = delete;
		virtual ~AEngine() = default;

		// --getters
		inline AMemAllocator& GetMemory() { return m_Memory; }
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
		virtual void Run();
		virtual bool Init() = 0;
		virtual void Quit() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(AEvent& rEvt) = 0;
		// --memory_methods
		template <typename MType, typename...Args>
		inline MType* NewT(Args...Arguments) { return NWL::NewT<MType>(GetMemory(), Arguments...); }
		template <typename MType>
		inline MType* NewTArr(UInt64 unAlloc) { return NWL::NewTArr<MType>(GetMemory(), unAlloc); }
		template <typename MType>
		inline void DelT(MType* pBlock) { NWL::DelT<MType>(GetMemory(), pBlock); }
		template <typename MType>
		inline void DelTArr(MType* pBlock, UInt64 unDealloc) { NWL::DelTArr<MType>(GetMemory(), pBlock, unDealloc); }
	protected:
		Thread m_thrRun;
		Bit m_bIsRunning;
		MemArena m_Memory;
		States m_States;
	};
	// --setters
	template<class EType, class SType>
	inline void AEngine<EType, SType>::AddState(SType& rState) { m_States.push_back(&rState); }
	template<class EType, class SType>
	inline void AEngine<EType, SType>::RmvState(UInt32 unIdx) { if (m_States.size() <= unIdx) { return; } m_States.erase(m_States.begin() + unIdx); }
	// --core_methods
	template<class EType, class SType>
	void AEngine<EType, SType>::Run() {
		Init();
		if (!m_bIsRunning) { return; }
		if (m_States.empty()) { Quit(); }

		auto fnRunLoop = [this]()->void { while (m_bIsRunning) { Update(); } Quit(); };
		m_thrRun = Thread(fnRunLoop);
	};
}

#endif	// NWL_ENGINE_H