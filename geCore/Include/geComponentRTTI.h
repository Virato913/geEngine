/*****************************************************************************/
/**
* @file    geComponentRTTI.h
* @author  Samuel Prince (samuel.prince.quezada@gmail.com)
* @date    2018/04/29
* @brief   RTTI Objects for geComponentRTTI.
*
* RTTI Objects for geGameObjectHandle.
*
* @bug     No known bugs.
*/
/*****************************************************************************/
#pragma once

/*****************************************************************************/
/**
* Includes
*/
/*****************************************************************************/
#include "gePrerequisitesCore.h"
#include "geComponent.h"
#include "geGameObjectRTTI.h"

#include <geRTTIType.h>

namespace geEngineSDK {
  using std::static_pointer_cast;

  class GE_CORE_EXPORT ComponentRTTI
    : public RTTIType<Component, GameObject, ComponentRTTI>
  {
   public:
    ComponentRTTI() = default;

    void
    onDeserializationEnded(IReflectable* obj,
                           const UnorderedMap<String, uint64>& /*params*/) override {
      Component* comp = static_cast<Component*>(obj);

      //It's possible we're just accessing the game object fields, in which
      //case the process below is not needed (it's only required for new
      //components).
      if (comp->m_rttiData.empty()) {
        return;
      }

      GODeserializationData&
        deserializationData = any_cast_ref<GODeserializationData>(comp->m_rttiData);

      //This shouldn't be null during normal deserialization but could be
      //during some other operations, like applying a binary diff.
      if (nullptr != deserializationData.ptr) {
        //Register the newly created SO with the GameObjectManager and provide
        //it with the original ID so that deserialized handles pointing to this
        //object can be resolved.
        SPtr<Component> compPtr = static_pointer_cast<Component>(deserializationData.ptr);
        GameObjectManager::instance().registerObject(compPtr, deserializationData.originalId);
      }

      comp->m_rttiData = nullptr;
    }

    const String&
    getRTTIName() override {
      static String name = "Component";
      return name;
    }

    uint32
    getRTTIId() override {
      return TYPEID_CORE::kID_Component;
    }

    SPtr<IReflectable>
    newRTTIObject() override {
      GE_EXCEPT(InternalErrorException,
                "Cannot instantiate an abstract class.");
      return nullptr;
    }
  };
}