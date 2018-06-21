
float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vColor;
float3 vLightDir;
float3 vEyePos; // 카메라의 대한 위치, specular 모양이 바뀌게 됨

struct VS_INPUT
{
    float4 position : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
};

struct VS_OUTPUT
{
    float4 position : POSITION;
    float4 color : COLOR0;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    // 카메라의 눈이랑 계산해줘야 되서
    float4 worldPos = mul(input.position, matWorld);

    output.position = mul(worldPos, matView);
    output.position = mul(output.position, matProjection);

    // 월드 기준 노말
    float3 worldNormal = mul(input.normal, (float3x3) matWorld);
    worldNormal = normalize(worldNormal);

    // xyz 스와질링 문법 (벡터 사이의 값에서 특정 값만 빼내서 쓰는거)
    // worldPos.xxx (float3이 되는거)
    // eyeDir 계산하기위해서 -붙이는 대신 반대로 빼준거
    float3 eyeDir = vEyePos - worldPos.xyz;
    eyeDir = normalize(eyeDir);

    // 정점으로부터 빛의 방향
    // diffuse color를 위해 쓸 녀석
    float3 toLightDir = normalize(-vLightDir);

    // 들어오는 빛의 방향
    // specular light를 위해 쓸 녀석
    float3 inLightDir = -toLightDir;

    // 빛의 반사 방향을 계산
    // 빛의 방향과 수직인 부분 밝게 아닐 수록 옅게 빛나게 하는 계산
    // 계산하는 공식과 함수 존재
    // 공식
    float3 lightReflect = 
    inLightDir + 2 * (dot(worldNormal, -inLightDir) * worldNormal);

    // 함수는 reflect라고 있음

    // 눈의 위치에 따라 변경을 해줘야함
    float spec = saturate(dot(eyeDir, lightReflect));

    // spec의 30제곱근 30번 곱한거
    // 30이 값이 커질수록 빛색에서 빛이 아닌색으로 넘어가는 값이 커짐
    // spec이 코사인 결과값이라서 빛색부분이 좁아짐
    // 제곱근 안하면 차이가 안나서 보통 30, 60정도 해줌
    spec = pow(spec, 30);

    // 램버트
    float diffuse = dot(-toLightDir, worldNormal);
    diffuse = saturate(diffuse);

    // vColor가 ambient color라고 보면 됨
    // spec이 specular power 라고 보면되며 얼마나 처리할지
    output.color = vColor * diffuse + float4(1, 1, 1, 1) * spec;

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