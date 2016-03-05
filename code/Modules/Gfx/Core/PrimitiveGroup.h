#pragma once
//------------------------------------------------------------------------------
/**
    @class Oryol::PrimitiveGroup
    @ingroup Gfx
    @brief describes a group of primitives to be rendered
    
    A PrimitiveGroup object describes a range of primitive elements in
    a mesh, where elements are either vertices or indices.
*/
#include "Core/Types.h"
#include "Gfx/Core/Enums.h"

namespace Oryol {

class PrimitiveGroup {
public:
    int32 BaseElement;
    int32 NumElements;

    /// default constructor
    PrimitiveGroup() :
        BaseElement(0),
        NumElements(0) {
        // empty
    }
    /// construct for indexed or non-indexed
    PrimitiveGroup(int32 baseElement, int32 numElements) :
        BaseElement(baseElement),
        NumElements(numElements) {
        // empty
    }
};

} // namespace Oryol
 