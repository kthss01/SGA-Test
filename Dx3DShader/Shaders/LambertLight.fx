// ���� ����
float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vColor; // ambient color, ��ü�� ���� ����
float3 vLightDir; // ������ ����
// ����� �� �� �̳༮�� ���� �Ⱦ��� ���̰� ����
float4x4 matInvWorld; // ���忡 ���� ����� 

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

    // ���� ������ ������ ���÷� ����
    float3 localLightDir = mul(vLightDir, (float3x3) matInvWorld);

    localLightDir = normalize(localLightDir);

    float3 toLocalLight = -localLightDir;

    // ����Ʈ ����
    float diffuse = dot(toLocalLight, localNormal);

    // saturate 0 ~ 1 ���̷� ©���ִ� �༮ clamp01�� ���� �༮�̶�� �����
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