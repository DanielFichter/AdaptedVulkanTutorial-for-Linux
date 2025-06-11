struct CoarseVertex
{
    float3 normal;
    float2 uv;
    float3 worldPosition;
};


[[vk::binding(1)]]
Sampler2D texSampler;

struct UniformBufferObject {
    float4x4 model;
    float4x4 view;
    float4x4 proj;
};

ConstantBuffer<UniformBufferObject> gParams;

[shader("fragment")]
float4 fragmentMain(CoarseVertex coarseVertex : CoarseVertex) : SV_Target
{
    float3 lightPosition = { 20, 20, 20 };
    float4 lightColor = { .5, .5, .5, 1};
    float4x4 viewMatrix = gParams.view;
    float3 viewMatrixTranslation = { viewMatrix[0][3], viewMatrix[1][3], viewMatrix[2][3] };
    float3x3 viewMatrixRotation = float3x3(viewMatrix);
    float3 cameraPosition = mul(viewMatrixRotation, -viewMatrixTranslation);
    float3 worldPosition = coarseVertex.worldPosition;

    float3 viewDirection = normalize(cameraPosition - worldPosition);
    float3 lightDirection = normalize(lightPosition - worldPosition);
    float3 normal = normalize(coarseVertex.normal);
    float diffuseCoefficient = .5;
    float specularCoefficient = 1;
    float shininess = 10;
    
    float3 halfVector = normalize(viewDirection + lightDirection);

    float diffuseIntensity = diffuseCoefficient * mul(lightDirection, normal);
    float4 diffuseColor = diffuseIntensity * texSampler.Sample(coarseVertex.uv);
    float specularIntensity = specularCoefficient * pow(max(0, mul(normal, halfVector)), shininess) /* / max(0, mul(normal, lightDirection)) */;
    float4 specularColor = specularIntensity * lightColor;

    return diffuseColor +  specularColor;
}







