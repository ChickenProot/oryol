//------------------------------------------------------------------------------
//  glMeshFactory.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "glMeshFactory.h"
#include "Gfx/Resource/resourcePools.h"
#include "Gfx/Resource/resource.h"
#include "Gfx/gl/gl_impl.h"
#include "Gfx/Core/renderer.h"
#include "Gfx/gl/glTypes.h"
#include "Resource/ResourceState.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
glMeshFactory::~glMeshFactory() {
    o_assert_dbg(!this->isValid);
}

//------------------------------------------------------------------------------
void
glMeshFactory::Setup(const gfxPointers& ptrs) {
    o_assert_dbg(!this->isValid);
    this->pointers = ptrs;
    this->isValid = true;
}

//------------------------------------------------------------------------------
void
glMeshFactory::Discard() {
    o_assert_dbg(this->isValid);
    this->pointers = gfxPointers();
    this->isValid = false;
}

//------------------------------------------------------------------------------
bool
glMeshFactory::IsValid() const {
    return this->isValid;
}

//------------------------------------------------------------------------------
ResourceState::Code
glMeshFactory::SetupResource(mesh& msh) {
    o_assert_dbg(this->isValid);
    if (msh.Setup.ShouldSetupEmpty()) {
        return this->createEmptyMesh(msh);
    }
    else if (msh.Setup.ShouldSetupFullScreenQuad()) {
        return this->createFullscreenQuad(msh);
    }
    else {
        o_error("glMeshFactory::SetupResource(): don't know how to create mesh!");
        return ResourceState::InvalidState;
    }
}

//------------------------------------------------------------------------------
ResourceState::Code
glMeshFactory::SetupResource(mesh& msh, const void* data, int size) {
    o_assert_dbg(msh.Setup.ShouldSetupFromData());
    return this->createFromData(msh, data, size);
}

//------------------------------------------------------------------------------
void
glMeshFactory::DestroyResource(mesh& mesh) {
    this->pointers.renderer->invalidateMeshState();
    for (auto& buf : mesh.buffers) {
        for (int i = 0; i < buf.numSlots; i++) {
            GLuint glBuf = buf.glBuffers[i];
            if  (0 != glBuf) {
                ::glDeleteBuffers(1, &glBuf);
            }
        }
    }
    mesh.Clear();
}

//------------------------------------------------------------------------------
/**
 NOTE: this method can be called with a nullptr for vertexData, in this case
 an empty GL buffer object will be created with the requested size.
*/
GLuint
glMeshFactory::createVertexBuffer(const void* vertexData, uint32_t vertexDataSize, Usage::Code usage) {
    o_assert_dbg(vertexDataSize > 0);
    
    this->pointers.renderer->invalidateMeshState();
    GLuint vb = 0;
    ::glGenBuffers(1, &vb);
    ORYOL_GL_CHECK_ERROR();
    o_assert_dbg(0 != vb);
    this->pointers.renderer->bindVertexBuffer(vb);
    ::glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, glTypes::asGLBufferUsage(usage));
    ORYOL_GL_CHECK_ERROR();
    this->pointers.renderer->invalidateMeshState();
    return vb;
}

//------------------------------------------------------------------------------
/**
 NOTE: this method can be called with a nullptr for indexData, in this case
 an empty GL buffer object will be created with the requested size.
*/
GLuint
glMeshFactory::createIndexBuffer(const void* indexData, uint32_t indexDataSize, Usage::Code usage) {
    o_assert_dbg(indexDataSize > 0);
    
    this->pointers.renderer->invalidateMeshState();
    GLuint ib = 0;
    ::glGenBuffers(1, &ib);
    ORYOL_GL_CHECK_ERROR();
    o_assert_dbg(0 != ib);
    this->pointers.renderer->bindIndexBuffer(ib);
    ::glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, indexData, glTypes::asGLBufferUsage(usage));
    ORYOL_GL_CHECK_ERROR();
    this->pointers.renderer->invalidateMeshState();
    return ib;
}

//------------------------------------------------------------------------------
ResourceState::Code
glMeshFactory::createFullscreenQuad(mesh& mesh) {

    o_assert_dbg(mesh.Setup.Layout.NumComponents() == 2);
    o_assert_dbg(mesh.Setup.Layout.ComponentAt(0).Attr == VertexAttr::Position);
    o_assert_dbg(mesh.Setup.Layout.ComponentAt(1).Attr == VertexAttr::TexCoord0);
    o_assert_dbg(mesh.Setup.Layout.ComponentAt(0).Format == VertexFormat::Float3);
    o_assert_dbg(mesh.Setup.Layout.ComponentAt(1).Format == VertexFormat::Float2);

    VertexBufferAttrs vbAttrs;
    vbAttrs.NumVertices = 4;
    vbAttrs.BufferUsage = Usage::Immutable;
    vbAttrs.Layout = mesh.Setup.Layout;
    mesh.vertexBufferAttrs = vbAttrs;

    IndexBufferAttrs ibAttrs;
    ibAttrs.NumIndices = 6;
    ibAttrs.Type = IndexType::Index16;
    ibAttrs.BufferUsage = Usage::Immutable;
    mesh.indexBufferAttrs = ibAttrs;

    mesh.numPrimGroups = 1;
    mesh.primGroups[0] = PrimitiveGroup(0, 6);

    // vertices
    const float topV = mesh.Setup.FullScreenQuadFlipV ? 0.0f : 1.0f;
    const float botV = mesh.Setup.FullScreenQuadFlipV ? 1.0f : 0.0f;
    float vertices[] = {
        -1.0f, +1.0f, 0.0f, 0.0f, topV,     // top-left corner
        +1.0f, +1.0f, 0.0f, 1.0f, topV,     // top-right corner
        +1.0f, -1.0f, 0.0f, 1.0f, botV,     // bottom-right corner
        -1.0f, -1.0f, 0.0f, 0.0f, botV      // bottom-left corner
    };

    // indices
    uint16_t indices[] = {
        0, 2, 1,            // topleft -> bottomright -> topright
        0, 3, 2,            // topleft -> bottomleft -> bottomright
    };
    
    // create vertex and index buffer
    o_assert_dbg(1 == mesh.buffers[mesh::vb].numSlots);
    o_assert_dbg(1 == mesh.buffers[mesh::ib].numSlots);
    mesh.buffers[mesh::vb].glBuffers[0] = this->createVertexBuffer(vertices, sizeof(vertices), mesh.vertexBufferAttrs.BufferUsage);
    mesh.buffers[mesh::ib].glBuffers[0] = this->createIndexBuffer(indices, sizeof(indices), mesh.indexBufferAttrs.BufferUsage);

    return ResourceState::Valid;
}

//------------------------------------------------------------------------------
void
glMeshFactory::setupAttrs(mesh& msh) {

    VertexBufferAttrs vbAttrs;
    vbAttrs.NumVertices = msh.Setup.NumVertices;
    vbAttrs.Layout = msh.Setup.Layout;
    vbAttrs.BufferUsage = msh.Setup.VertexUsage;
    msh.vertexBufferAttrs = vbAttrs;

    IndexBufferAttrs ibAttrs;
    ibAttrs.NumIndices = msh.Setup.NumIndices;
    ibAttrs.Type = msh.Setup.IndicesType;
    ibAttrs.BufferUsage = msh.Setup.IndexUsage;
    msh.indexBufferAttrs = ibAttrs;
}

//------------------------------------------------------------------------------
void
glMeshFactory::setupPrimGroups(mesh& msh) {
    msh.numPrimGroups = msh.Setup.NumPrimitiveGroups();
    o_assert_dbg(msh.numPrimGroups < GfxConfig::MaxNumPrimGroups);
    for (int i = 0; i < msh.numPrimGroups; i++) {
        msh.primGroups[i] = msh.Setup.PrimitiveGroup(i);
    }
}
//------------------------------------------------------------------------------
ResourceState::Code
glMeshFactory::createEmptyMesh(mesh& mesh) {
    o_assert_dbg(0 == mesh.buffers[mesh::vb].glBuffers[0]);
    o_assert_dbg(0 == mesh.buffers[mesh::ib].glBuffers[0]);

    this->setupAttrs(mesh);
    this->setupPrimGroups(mesh);
    const auto& vbAttrs = mesh.vertexBufferAttrs;
    const auto& ibAttrs = mesh.indexBufferAttrs;

    // create vertex buffer(s)
    if (mesh.Setup.NumVertices > 0) {
        const int vbSize = vbAttrs.NumVertices * vbAttrs.Layout.ByteSize();
        mesh.buffers[mesh::vb].numSlots = Usage::Stream == vbAttrs.BufferUsage ? 2 : 1;
        for (uint8_t slotIndex = 0; slotIndex < mesh.buffers[mesh::vb].numSlots; slotIndex++) {
            mesh.buffers[mesh::vb].glBuffers[slotIndex] = this->createVertexBuffer(nullptr, vbSize, vbAttrs.BufferUsage);
        }
    }

    // create optional index buffer(s)
    if (IndexType::None != ibAttrs.Type) {
        mesh.buffers[mesh::ib].numSlots = Usage::Stream == ibAttrs.BufferUsage ? 2 : 1;
        const int ibSize = ibAttrs.NumIndices * IndexType::ByteSize(ibAttrs.Type);
        for (uint8_t slotIndex = 0; slotIndex < mesh.buffers[mesh::ib].numSlots; slotIndex++) {
            mesh.buffers[mesh::ib].glBuffers[slotIndex] = this->createIndexBuffer(nullptr, ibSize, ibAttrs.BufferUsage);
        }
    }

    return ResourceState::Valid;
}
    
//------------------------------------------------------------------------------
ResourceState::Code
glMeshFactory::createFromData(mesh& mesh, const void* data, int size) {
    o_assert_dbg(0 == mesh.buffers[mesh::vb].glBuffers[0]);
    o_assert_dbg(0 == mesh.buffers[mesh::ib].glBuffers[0]);
    o_assert_dbg(1 == mesh.buffers[mesh::vb].numSlots);
    o_assert_dbg(1 == mesh.buffers[mesh::ib].numSlots);
    o_assert_dbg(nullptr != data);
    o_assert_dbg(size > 0);

    this->setupAttrs(mesh);
    this->setupPrimGroups(mesh);
    const auto& vbAttrs = mesh.vertexBufferAttrs;
    const auto& ibAttrs = mesh.indexBufferAttrs;
    const uint8_t* ptr = (const uint8_t*)data;

    // create vertex buffer(s)
    if (mesh.Setup.NumVertices > 0) {
        const int vbSize = vbAttrs.NumVertices * vbAttrs.Layout.ByteSize();
        mesh.buffers[mesh::vb].numSlots = Usage::Stream == vbAttrs.BufferUsage ? 2 : 1;
        const uint8_t* vertices = nullptr;
        if (InvalidIndex != mesh.Setup.DataVertexOffset) {
            vertices = ptr + mesh.Setup.DataVertexOffset;
            o_assert_dbg((ptr + size) >= (vertices + vbSize));
        }
        for (uint8_t slotIndex = 0; slotIndex < mesh.buffers[mesh::vb].numSlots; slotIndex++) {
            mesh.buffers[mesh::vb].glBuffers[slotIndex] = this->createVertexBuffer(vertices, vbSize, vbAttrs.BufferUsage);
            o_assert_dbg(0 != mesh.buffers[mesh::vb].glBuffers[slotIndex]);
        }
    }

    // create optional index buffer(s)
    if (ibAttrs.Type != IndexType::None) {
        const int ibSize = ibAttrs.NumIndices * IndexType::ByteSize(ibAttrs.Type);
        mesh.buffers[mesh::ib].numSlots = Usage::Stream == ibAttrs.BufferUsage ? 2 : 1;
        const uint8_t* indices = nullptr;
        if (InvalidIndex != mesh.Setup.DataIndexOffset) {
            indices = ptr + mesh.Setup.DataIndexOffset;
            o_assert_dbg((ptr + size) >= (indices + ibSize));
        }
        for (uint8_t slotIndex = 0; slotIndex < mesh.buffers[mesh::ib].numSlots; slotIndex++) {
            mesh.buffers[mesh::ib].glBuffers[slotIndex] = this->createIndexBuffer(indices, ibSize, ibAttrs.BufferUsage);
            o_assert_dbg(0 != mesh.buffers[mesh::ib].glBuffers[slotIndex]);
        }
    }
    
    return ResourceState::Valid;
}

} // namespace _priv
} // namespace Oryol
