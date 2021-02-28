#ifndef NWL_ECS_ENTITY_H
#define NWL_ECS_ENTITY_H

#include <nwl_core.hpp>
#include <core/nwl_id_stack.h>
#include <core/nwl_type.h>
#include <core/nwl_container.h>
#include <memory/mem_sys.h>
#include <ecs/ecs_component.h>

namespace NWL
{
	/// Abstract AEnt class
	/// --main object base class for complex objects;
	/// --allows to construct an object of different components;
	/// --takes responsibility for creation and destruction of all components
	class NWL_API AEnt : public AMemUser
	{
		friend class ACmp;
		using Cmps = HashMap<UInt32, RefKeeper<ACmp>>;
	protected:
		AEnt(UInt32 tId);
		AEnt(const AEnt& rCpy) = delete;
	public:
		virtual ~AEnt();
		// --getters
		inline UInt32 GetTypeId() const { return m_tId; }
		inline UInt32 GetEntId() const { return m_eId; }
		// --setters
		void SetEnabled(Bit bIsEnabled);
		// --predicates
		inline Bit IsEnabled() { return m_bIsEnabled; }
		// --predicates
		template<class EType> bool IsOfType() { return TypeIndexator<EType>() == GetTypeId(); }
		// --operators
		inline void operator=(const AEnt& rCpy) = delete;
	protected:
		const UInt32 m_tId;
		UInt32 m_eId;
		Bit m_bIsEnabled;
	private:
		static IdStack s_idStack;
	};
}
namespace NWL
{
	/// Templated AEnt class
	template<class EType>
	class NWL_API TEnt : public AEnt
	{
	protected:
		TEnt() : AEnt(TypeIndexator::GetId()) { }
	public:
		virtual ~TEnt() { }
	};
}
#endif	// NWL_ECS_ENTITY_H