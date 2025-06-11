
struct AssembledVertex
{
    float3 position : POSITION;
    float3 normal    : NORMAL;
    float2 uv       : UV;
};


struct CoarseVertex
{
    float3 normal;
    float2 uv;
    float3 worldPosition;
};


struct VertexStageOutput
{
    CoarseVertex coarseVertex : CoarseVertex;
    float4       sv_position  : SV_Position;
};


struct UniformBufferObject {
    float4x4 model;
    float4x4 view;
    float4x4 proj;
};

ParameterBlock<UniformBufferObject> gParams;


[shader("vertex")]
VertexStageOutput vertexMain(AssembledVertex assembledVertex)
{
    VertexStageOutput output;

    float3 position = assembledVertex.position;
    float3 normal    = assembledVertex.normal;
    float2 uv       = assembledVertex.uv;

    float3 worldPosition = mul(gParams.model, float4(position, 1.0)).xyz;
    float3 viewPosition = mul(gParams.view, float4(worldPosition, 1.0)).xyz;
    float3 worldNormal = mul(gParams.model, float4(normal, 1.0)).xyz;

    output.coarseVertex.normal   = worldNormal;
    output.coarseVertex.uv = uv;
    output.coarseVertex.worldPosition = worldPosition;
    output.sv_position = mul(gParams.proj, float4(viewPosition, 1.0));

    return output;
}





