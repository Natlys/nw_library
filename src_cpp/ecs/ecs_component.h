#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>

namespace NWL
{
	/// Abstract Component class
	/// Description:
	/// --provides basic interface, getters and setters for components
	/// --the only one derrived class can be used is templated component
	/// --templated component provides this static type index
	/// --because of that index we can get any component by simple array number
	/// --components cannot use only TCmp because only abstract one can be used
	/// via pointer/ref without explicit type declaration
	/// --only component system can set entity id
	/// because entity id is needed for component only for external access and
	/// explicit argument for constructor is pretty uncomfortable
	class NWL_API ACmp
	{
		friend class CmpEntity;
		friend class CmpSys;
	protected:
		ACmp(UInt32 tId) : m_tId(tId), m_eId(0) {}
	public:
		virtual ~ACmp();
		// --getters
		inline unsigned int GetEntId() const { return m_eId; }
		inline unsigned int GetTypeId() const { return m_tId; }
		// --operators
		inline void* operator new(Size szData) { return MemSys::Alloc(szData); }
		inline void* operator new[](Size szData) { return MemSys::Alloc(szData); }
		inline void operator delete(Ptr pData, Size szData) { MemSys::Dealloc(pData, szData); }
		inline void operator delete[](Ptr pData, Size szData) { MemSys::Dealloc(pData, szData); }
	protected:
		unsigned int m_eId;
		unsigned int m_tId;
	};
}

#endif	// NWL_ECS_COMPONENT_H