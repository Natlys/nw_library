#ifndef NWL_AENGINE_H
#define NWL_AENGINE_H

#include <nwlib/nwl_singleton.h>
#include <nwlib/nwl_memory.h>
#include <nwlib/nwl_thread.h>

namespace NWL
{
	class AEngine : public ASingleton<AEngine>
	{
		friend class ASingleton<AEngine>;
	public:
		AEngine();
		AEngine(AEngine& rCpy) = delete;
		virtual ~AEngine();

		// --getters
		inline AMemAllocator& GetMemory() { return m_Memory; }
		inline Thread& GetRunThread() { return m_thrRun; }
		// --setters
		// --predicates
		inline Bit IsRunning() const { return m_bIsRunning; }
		// --core_methods
		virtual bool Init(Size szMemory) = 0;
		virtual void Quit() = 0;
		virtual void Update() = 0;
		inline void Run(Size szMemory);
	private:
		Thread m_thrRun;
		MemArena m_Memory;
		Bit m_bIsRunning;
	};
	inline void AEngine::Run(Size szMemory) {
		auto fnUpdate = [this](Size szMem)->void {
			m_bIsRunning = true;
			m_Memory = MemArena(new Byte[szMem], szMem);
			while (m_bIsRunning) { Update(); }
			delete[] m_Memory.GetDataBeg();
			m_Memory = MemArena(nullptr, 0);
			Quit();
		};
		m_thrRun = Thread(fnUpdate, szMemory);
	}
}

#endif	// NWL_AENGINE_H