#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H

#include <nwl_core.hpp>

#include <utility/nwl_id_stack.h>

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
		friend class AEntity;
		friend class CmpSys;
	protected:
		ACmp(UInt32 tId);
	public:
		virtual ~ACmp();
		// --getters
		inline UInt32 GetEntId() const { return m_eId; }
		inline UInt32 GetTypeId() const { return m_tId; }
		// --operators
		inline void operator delete(Ptr pBlock) = delete;
		inline void operator delete[](Ptr pBlock) = delete;
	protected:
		UInt32 m_eId;
		UInt32 m_tId;
	protected:
		static inline IdStack& GetIdStack() { static IdStack s_idStack; return s_idStack; }
	};
}

#endif	// NWL_ECS_COMPONENT_H