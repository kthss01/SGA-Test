float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vDiffuseColor;
float4 vSpecularColor;

float3 vLightDir; // 광원의 방향 (정규화로 들어와줘야함)
float3 vEyePos; // 눈의 위치값 (카메라의 위치값)
float fPower; // 정반사 날카롭기

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

// TEXCOORD uv, 좌표, 또는 애매한것들은 이거 붙여서 보내면 됨
// TEXCOORD로 보낼 수 있는 갯수가 8개로 제한되어있음

struct VS_OUTPUT
{
    float4 position : POSITION; // 무조건 반환해야함
    float3 normal : TEXCOORD0; // 좌표값으로 사용할꺼면 texcoord로 넣어줘야함
    float3 eyeDir : TEXCOORD1; 
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    // 정점 월드 위치
    float4 worldPos = mul(float4(input.position, 1.0f), matWorld);

    output.position = mul(worldPos, matView);
    output.position = mul(output.position, matProjection);

    // 월드 노말
    // 방향으로 쓸 때는 normalize 꼭 해주자
    float3 worldNormal = mul(input.normal, (float3x3) matWorld);
    worldNormal = normalize(worldNormal);

    output.normal = worldNormal;
    
    // 눈의 방향
    float3 eyeDir = vEyePos - worldPos.xyz; // 스와질링 문법 특정값만 뽑아내는거
    eyeDir = normalize(eyeDir);

    output.eyeDir = eyeDir;

    return output;
}

float4 PS(VS_OUTPUT input) : COLOR0
{
    // 노멀라이즈 한번 더 한 이유
    // 노멀라이즈 하고 값이 넘어오더라도 
    // 픽셀의 좌표에 대해서 노멀라이즈된 상태로 들어온단 보장은 없음
    float3 normal = normalize(input.normal);
    float3 eyeDir = normalize(input.eyeDir);

    // 월드 광원 방향
    float3 toLight = -vLightDir;

    // Diffuse
    float diffuse = saturate(dot(toLight, normal));

    // Reflection - Specular를 만들기 위한 값임
    float3 inLight = -toLight;
    float3 lightReflect = inLight + 2 * (dot(-inLight, normal) * normal);
    lightReflect = normalize(lightReflect);

    // Specular
    float spec = saturate(dot(lightReflect, eyeDir));

    spec = pow(spec, fPower);

    // ambient color가 있다면 vDiffuseColor에 곱해주면됨

    // 색깔 섞어주는건 곱해주고 덮어씌우는건 더해주면 됨

    float4 finalColor =
        (vDiffuseColor * diffuse) + (vSpecularColor * spec);

    return finalColor;
}

technique LightShader
{
    pass p0
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}