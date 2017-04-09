//------------------------------------------------------------------------------
//  d3d11PipelineFactory.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "d3d11PipelineFactory.h"
#include "d3d11_impl.h"
#include "d3d11Types.h"
#include "Gfx/Core/renderer.h"
#include "Gfx/Resource/resourcePools.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
d3d11PipelineFactory::~d3d11PipelineFactory() {
    o_assert_dbg(nullptr == this->d3d11Device);
}

//------------------------------------------------------------------------------
void
d3d11PipelineFactory::Setup(const gfxPointers& ptrs) {
    o_assert_dbg(nullptr == this->d3d11Device);

    pipelineFactoryBase::Setup(ptrs);
    this->d3d11Device = this->pointers.renderer->d3d11Device;
    o_assert_dbg(nullptr != this->d3d11Device);
}

//------------------------------------------------------------------------------
void
d3d11PipelineFactory::Discard() {
    o_assert_dbg(nullptr != this->d3d11Device);
    this->d3d11Device = nullptr;
    pipelineFactoryBase::Discard();
}

//------------------------------------------------------------------------------
ResourceState::Code
d3d11PipelineFactory::SetupResource(pipeline& pip) {
    o_assert_dbg(nullptr != this->d3d11Device);
    o_assert_dbg(nullptr == pip.d3d11InputLayout);
    o_assert_dbg(nullptr == pip.d3d11RasterizerState);
    o_assert_dbg(nullptr == pip.d3d11BlendState);
    o_assert_dbg(nullptr == pip.d3d11DepthStencilState);
    HRESULT hr;

    pipelineFactoryBase::SetupResource(pip);
    o_assert_dbg(pip.shd);

    pip.d3d11InputLayout = this->createInputLayout(pip);
    pip.d3d11PrimTopology = d3d11Types::asPrimitiveTopology(pip.Setup.PrimType);
    o_assert_dbg(pip.d3d11InputLayout);

    // create state objects (NOTE: creating the same state will return
    // the same d3d11 state object, so no need to implement our own reuse)
    const RasterizerState& rastState = pip.Setup.RasterizerState;
    D3D11_RASTERIZER_DESC rastDesc = { };
    rastDesc.FillMode = D3D11_FILL_SOLID;
    rastDesc.CullMode = d3d11Types::asCullMode(rastState.CullFaceEnabled, rastState.CullFace);
    rastDesc.FrontCounterClockwise = FALSE;  // OpenGL convention
    rastDesc.DepthBias = 0;
    rastDesc.DepthBiasClamp = 0.0f;
    rastDesc.DepthClipEnable = TRUE;
    rastDesc.ScissorEnable = rastState.ScissorTestEnabled;
    rastDesc.MultisampleEnable = rastState.SampleCount > 1;
    rastDesc.AntialiasedLineEnable = FALSE;
    hr = this->d3d11Device->CreateRasterizerState(&rastDesc, &pip.d3d11RasterizerState);
    o_assert(SUCCEEDED(hr));
    o_assert_dbg(nullptr != pip.d3d11RasterizerState);

    const DepthStencilState& dsState = pip.Setup.DepthStencilState;
    D3D11_DEPTH_STENCIL_DESC dsDesc = { };
    dsDesc.DepthEnable = TRUE;      // FIXME: have DepthTestEnable in RasterizerState?
    dsDesc.DepthWriteMask = dsState.DepthWriteEnabled ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
    dsDesc.DepthFunc = d3d11Types::asComparisonFunc(dsState.DepthCmpFunc);
    dsDesc.StencilEnable    = dsState.StencilEnabled;
    dsDesc.StencilReadMask  = dsState.StencilReadMask;
    dsDesc.StencilWriteMask = dsState.StencilWriteMask;
    dsDesc.FrontFace.StencilFailOp = d3d11Types::asStencilOp(dsState.StencilFront.FailOp);
    dsDesc.FrontFace.StencilDepthFailOp = d3d11Types::asStencilOp(dsState.StencilFront.DepthFailOp);
    dsDesc.FrontFace.StencilPassOp = d3d11Types::asStencilOp(dsState.StencilFront.PassOp);
    dsDesc.FrontFace.StencilFunc = d3d11Types::asComparisonFunc(dsState.StencilFront.CmpFunc);
    dsDesc.BackFace.StencilFailOp = d3d11Types::asStencilOp(dsState.StencilBack.FailOp);
    dsDesc.BackFace.StencilDepthFailOp = d3d11Types::asStencilOp(dsState.StencilBack.DepthFailOp);
    dsDesc.BackFace.StencilPassOp = d3d11Types::asStencilOp(dsState.StencilBack.PassOp);
    dsDesc.BackFace.StencilFunc = d3d11Types::asComparisonFunc(dsState.StencilBack.CmpFunc);
    hr = this->d3d11Device->CreateDepthStencilState(&dsDesc, &pip.d3d11DepthStencilState);
    o_assert(SUCCEEDED(hr));
    o_assert_dbg(nullptr != pip.d3d11DepthStencilState);

    const BlendState& blendState = pip.Setup.BlendState;
    o_assert(blendState.MRTCount < GfxConfig::MaxNumColorAttachments);
    D3D11_BLEND_DESC blendDesc = { };
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = blendState.BlendEnabled;
    blendDesc.RenderTarget[0].SrcBlend = d3d11Types::asBlendFactor(blendState.SrcFactorRGB);
    blendDesc.RenderTarget[0].DestBlend = d3d11Types::asBlendFactor(blendState.DstFactorRGB);
    blendDesc.RenderTarget[0].BlendOp = d3d11Types::asBlendOp(blendState.OpRGB);
    blendDesc.RenderTarget[0].SrcBlendAlpha = d3d11Types::asBlendFactor(blendState.SrcFactorAlpha);
    blendDesc.RenderTarget[0].DestBlendAlpha = d3d11Types::asBlendFactor(blendState.DstFactorAlpha);
    blendDesc.RenderTarget[0].BlendOpAlpha = d3d11Types::asBlendOp(blendState.OpAlpha);
    blendDesc.RenderTarget[0].RenderTargetWriteMask = d3d11Types::asColorWriteMask(blendState.ColorWriteMask);
    hr = this->d3d11Device->CreateBlendState(&blendDesc, &pip.d3d11BlendState);
    o_assert(SUCCEEDED(hr));
    o_assert_dbg(nullptr != pip.d3d11BlendState);

    return ResourceState::Valid;
}

//------------------------------------------------------------------------------
void
d3d11PipelineFactory::DestroyResource(pipeline& pip) {
    this->pointers.renderer->invalidatePipeline();
    if (nullptr != pip.d3d11InputLayout) {
        pip.d3d11InputLayout->Release();
    }
    if (nullptr != pip.d3d11RasterizerState) {
        pip.d3d11RasterizerState->Release();
    }
    if (nullptr != pip.d3d11BlendState) {
        pip.d3d11BlendState->Release();
    }
    if (nullptr != pip.d3d11DepthStencilState) {
        pip.d3d11DepthStencilState->Release();
    }
    pipelineFactoryBase::DestroyResource(pip);
}

//------------------------------------------------------------------------------
ID3D11InputLayout*
d3d11PipelineFactory::createInputLayout(const pipeline& pip) {
    o_assert_dbg(nullptr == pip.d3d11InputLayout);

    // create a new input layout object and add to cache
    D3D11_INPUT_ELEMENT_DESC d3d11Comps[VertexAttr::NumVertexAttrs] = { 0 };
    int d3d11CompIndex = 0;
    for (int mshSlotIndex = 0; mshSlotIndex < GfxConfig::MaxNumInputMeshes; mshSlotIndex++) {
        const VertexLayout& layout = pip.Setup.Layouts[mshSlotIndex];
        for (int compIndex = 0; compIndex < layout.NumComponents(); compIndex++, d3d11CompIndex++) {
            const auto& comp = layout.ComponentAt(compIndex);
            o_assert_dbg(d3d11CompIndex < VertexAttr::NumVertexAttrs);
            D3D11_INPUT_ELEMENT_DESC& d3d11Comp = d3d11Comps[d3d11CompIndex];
            d3d11Comp.SemanticName = d3d11Types::asSemanticName(comp.Attr);
            d3d11Comp.SemanticIndex = d3d11Types::asSemanticIndex(comp.Attr);
            d3d11Comp.Format = d3d11Types::asInputElementFormat(comp.Format);
            d3d11Comp.InputSlot = mshSlotIndex;
            d3d11Comp.AlignedByteOffset = layout.ComponentByteOffset(compIndex);
            d3d11Comp.InputSlotClass = d3d11Types::asInputClassification(layout.StepFunction);
            if (VertexStepFunction::PerVertex == layout.StepFunction) {
                d3d11Comp.InstanceDataStepRate = 0;
            }
            else {
                d3d11Comp.InstanceDataStepRate = layout.StepRate;
            }
        }
    }

    // lookup the vertex shader bytecode
    const void* vsByteCode = nullptr;
    uint32_t vsSize = 0;
    pip.shd->Setup.VertexShaderByteCode(ShaderLang::HLSL5, vsByteCode, vsSize);
    o_assert_dbg(vsByteCode && (vsSize > 0));

    // create d3d11 input layout object
    ID3D11InputLayout* d3d11InputLayout = nullptr;
    HRESULT hr = this->d3d11Device->CreateInputLayout(
        d3d11Comps,         // pInputElementDesc 
        d3d11CompIndex,     // NumElements
        vsByteCode,         // pShaderBytecodeWithInputSignature 
        vsSize,             // BytecodeLength
        &d3d11InputLayout);
    o_assert(SUCCEEDED(hr));
    o_assert_dbg(nullptr != d3d11InputLayout);

    return d3d11InputLayout;
}

} // namespace _priv
} // namespace Oryol
