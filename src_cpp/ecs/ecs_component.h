#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>

namespace NWL
{
	/// Abstract Component class
	class NWL_API ACmp : public AMemUser
	{
		friend class CmpEntity;
		friend class CmpSys;
	protected:
		ACmp(unsigned int tId);
	public:
		virtual ~ACmp();
		// --getters
		inline unsigned int GetEntId() const { return m_eId; }
		inline unsigned int GetTypeId() const { return m_tId; }
	protected:
		unsigned int m_eId;
		unsigned int m_tId;
	};
}

#endif	// NWL_ECS_COMPONENT_H