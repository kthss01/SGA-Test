// 전역 변수
float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vColor; // ambient color, 물체에 대한 색상
float3 vLightDir; // 광원의 방향
// 계산을 할 때 이녀석을 쓰냐 안쓰냐 차이가 잇음
float4x4 matInvWorld; // 월드에 대한 역행렬 

struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VS_OUTPUT
{
    float4 position : POSITION;
    float4 color : COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    output.position = mul(input.position, matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProjection);

    float3 localNormal = input.normal;

    // 월드 광원의 방향을 로컬로 변경
    float3 localLightDir = mul(vLightDir, (float3x3) matInvWorld);

    localLightDir = normalize(localLightDir);

    float3 toLocalLight = -localLightDir;

    // 램버트 내적
    float diffuse = dot(toLocalLight, localNormal);

    // saturate 0 ~ 1 사이로 짤라주는 녀석 clamp01과 같은 녀석이라고 보면됨
    diffuse = saturate(diffuse);

    if (diffuse > 0.0f)
        diffuse = 1.0f;

    output.color = vColor * diffuse;

    return output;
}

float4 PS(VS_OUTPUT input) : COLOR0
{
    return input.color;
}

technique LightShader
{
    pass P0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}