/*****************************************************************************/
/**
 * @file    geSerializedObject.h
 * @author  Samuel Prince (samuel.prince.quezada@gmail.com)
 * @date    2017/11/03
 * @brief   Base class for intermediate representations of objects that are
 *          being decoded with BinarySerializer.
 *
 * Base class for intermediate representations of objects that are being
 * decoded with BinarySerializer.
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
#include "gePrerequisitesUtil.h"
#include "geIReflectable.h"

namespace geEngineSDK {
  struct GE_UTILITY_EXPORT SerializedInstance : IReflectable
  {
    virtual ~SerializedInstance() {}

    /**
     * @brief Performs a deep clone of this object any any potential child
     *        objects.
     * @param[in] cloneData	If true the data contained by the objects will be
     *            cloned as well, instead of just meta-data. If false then both
     *            the original and the cloned instances will point to the same
     *            instances of data. The original will retain data ownership
     *            and it will go out of scope when the original does.
     */
    virtual SPtr<SerializedInstance>
    clone(bool cloneData = true) = 0;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedInstanceRTTI;
    
    static RTTITypeBase*
    getRTTIStatic();

    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief An intermediate serialized data for a single field in an object.
   */
  struct GE_UTILITY_EXPORT SerializedEntry : IReflectable
  {
    SerializedEntry() : fieldId(0), serialized(nullptr) {}

    uint32 fieldId;
    SPtr<SerializedInstance> serialized;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedEntryRTTI;

    static RTTITypeBase*
    getRTTIStatic();
    
    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief A serialized value representing a single entry in an array.
   */
  struct GE_UTILITY_EXPORT SerializedArrayEntry : IReflectable
  {
    SerializedArrayEntry() : index(0), serialized(nullptr) {}

    uint32 index;
    SPtr<SerializedInstance> serialized;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedArrayEntryRTTI;

    static RTTITypeBase*
    getRTTIStatic();

    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief A serialized portion of an object belonging to a specific class in
   *        a class hierarchy. Consists of multiple entries, one for each field
   */
  struct GE_UTILITY_EXPORT SerializedSubObject : IReflectable
  {
    SerializedSubObject() : typeId(0) {}

    uint32 typeId;
    UnorderedMap<uint32, SerializedEntry> entries;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedSubObjectRTTI;

    static RTTITypeBase*
    getRTTIStatic();
    
    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief A serialized object consisting of multiple sub-objects, one for
   *        each inherited class.
   */
  struct GE_UTILITY_EXPORT SerializedObject : SerializedInstance
  {
    /**
     * @brief Returns the RTTI type ID for the most-derived class of this
     *        object.
     */
    uint32
    getRootTypeId() const;

    /**
     * @copydoc SerializedInstance::clone
     */
    SPtr<SerializedInstance>
    clone(bool cloneData = true) override;

    Vector<SerializedSubObject> subObjects;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedObjectRTTI;
    
    static RTTITypeBase*
    getRTTIStatic();
    
    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief Contains data for a serialized value of a specific field or array
   *        entry.
   */
  struct GE_UTILITY_EXPORT SerializedField : SerializedInstance
  {
    SerializedField() : value(nullptr), size(0), ownsMemory(false) {}

    ~SerializedField() {
      if (nullptr != value && ownsMemory) {
        ge_free(value);
      }
    }

    /**
     * @copydoc SerializedInstance::clone
     */
    SPtr<SerializedInstance>
    clone(bool cloneData = true) override;

    uint8* value;
    uint32 size;
    bool ownsMemory;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedFieldRTTI;

    static RTTITypeBase*
    getRTTIStatic();

    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief Contains data for a serialized value of a data block field.
   */
  struct GE_UTILITY_EXPORT SerializedDataBlock : SerializedInstance
  {
    SerializedDataBlock() : offset(0), size(0) {}

    /**
     * @copydoc SerializedInstance::clone
     */
    SPtr<SerializedInstance>
    clone(bool cloneData = true) override;

    SPtr<DataStream> stream;
    uint32 offset;
    uint32 size;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedDataBlockRTTI;

    static RTTITypeBase*
    getRTTIStatic();

    RTTITypeBase*
    getRTTI() const override;
  };

  /**
   * @brief A serialized array containing a list of all its entries.
   */
  struct GE_UTILITY_EXPORT SerializedArray : SerializedInstance
  {
    SerializedArray() : numElements(0) {}

    /**
     * @copydoc SerializedInstance::clone
     */
    SPtr<SerializedInstance>
    clone(bool cloneData = true) override;

    UnorderedMap<uint32, SerializedArrayEntry> entries;
    uint32 numElements;

    /*************************************************************************/
    /**
     * RTTI
     */
    /*************************************************************************/
   public:
    friend class SerializedArrayRTTI;

    static RTTITypeBase*
    getRTTIStatic();

    RTTITypeBase*
    getRTTI() const override;
  };
}
