#ifndef NWL_ECS_COMPONENT_H
#define NWL_ECS_COMPONENT_H

#include <nwl_core.hpp>
#include <nwl_memory.hpp>

namespace NWL
{
	/// Abstract Component class
	class NWL_API ACmp : public AMemUser
	{
		friend class CmpSys;
	protected:
		ACmp(UInt32 tId);
		ACmp(const ACmp& rCpy) = delete;
	public:
		virtual ~ACmp();
		// --getters
		inline UInt32 GetTypeId() const	{ return m_tId; }
		inline UInt32 GetEntId() const	{ return m_eId; }
		// --operators
		inline void operator=(const ACmp& rCpy) = delete;
	protected:
		const UInt32 m_tId;
		UInt32 m_eId;
	};
}
namespace NWL
{
	/// Templated Component class
	template <class CType>
	class NWL_API TCmp : public ACmp
	{
	protected:
		TCmp() : ACmp(TypeIndexator::GetId<CType>()) { }
	public:
		virtual ~TCmp() { }
	};
}

#endif	// NWL_ECS_COMPONENT_H