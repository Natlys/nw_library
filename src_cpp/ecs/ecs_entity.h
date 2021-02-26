#ifndef NWL_ECS_ENTITY_H
#define NWL_ECS_ENTITY_H

#include <nwl_core.hpp>

#include <memory/mem_sys.h>
#include <core/nwl_id_stack.h>
#include <core/nwl_type.h>

namespace NWL
{
	/// Anstract Entity class
	class NWL_API Entity : public AMemUser
	{
	protected:
		Entity(unsigned int tId);
	public:
		Entity(const Entity& rCpy);
		virtual ~Entity();
		// --getters
		inline unsigned int GetEntId() const	{ return m_eId; }
		inline unsigned int GetTypeId() const	{ return m_tId; }
		virtual inline const char* GetTypeStr() const = 0;
		// --setters
		void SetEnabled(bool bIsEnabled);
		// --predicates
		inline bool IsEnabled() { return m_bIsEnabled; }
		// --predicates
		template<class EType> inline bool IsOfType() { return TypeIndexator<EType>() == GetTypeId(); }
		// --operators
		inline void operator=(const Entity& rCpy) = delete;
	protected:
		static inline IdStack& GetIdStack() { static IdStack s_idStack(1); return s_idStack; }
	protected:
		unsigned int m_eId;
		unsigned int m_tId;
		bool m_bIsEnabled;
	};
}
namespace NWL
{
	/// Templated Entity class
	template<class EType>
	class NWL_API TEntity : public Entity
	{
	protected:
		TEntity() : Entity(TypeIndexator::GetId()) { }
	public:
		virtual ~TEntity() { }
		// --getters
		virtual inline const char* GetTypeStr() const override { return typeid(EType).name(); }
	};
}
#endif	// NWL_ECS_ENTITY_H