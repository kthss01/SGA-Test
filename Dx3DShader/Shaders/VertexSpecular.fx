
float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vColor;
float3 vLightDir;
float3 vEyePos; // ī�޶��� ���� ��ġ, specular ����� �ٲ�� ��

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

    // ī�޶��� ���̶� �������� �Ǽ�
    float4 worldPos = mul(input.position, matWorld);

    output.position = mul(worldPos, matView);
    output.position = mul(output.position, matProjection);

    // ���� ���� �븻
    float3 worldNormal = mul(input.normal, (float3x3) matWorld);
    worldNormal = normalize(worldNormal);

    // xyz �������� ���� (���� ������ ������ Ư�� ���� ������ ���°�)
    // worldPos.xxx (float3�� �Ǵ°�)
    // eyeDir ����ϱ����ؼ� -���̴� ��� �ݴ�� ���ذ�
    float3 eyeDir = vEyePos - worldPos.xyz;
    eyeDir = normalize(eyeDir);

    // �������κ��� ���� ����
    // diffuse color�� ���� �� �༮
    float3 toLightDir = normalize(-vLightDir);

    // ������ ���� ����
    // specular light�� ���� �� �༮
    float3 inLightDir = -toLightDir;

    // ���� �ݻ� ������ ���
    // ���� ����� ������ �κ� ��� �ƴ� ���� ���� ������ �ϴ� ���
    // ����ϴ� ���İ� �Լ� ����
    // ����
    float3 lightReflect = 
    inLightDir + 2 * (dot(worldNormal, -inLightDir) * worldNormal);

    // �Լ��� reflect��� ����

    // ���� ��ġ�� ���� ������ �������
    float spec = saturate(dot(eyeDir, lightReflect));

    // spec�� 30������ 30�� ���Ѱ�
    // 30�� ���� Ŀ������ �������� ���� �ƴѻ����� �Ѿ�� ���� Ŀ��
    // spec�� �ڻ��� ������̶� �����κ��� ������
    // ������ ���ϸ� ���̰� �ȳ��� ���� 30, 60���� ����
    spec = pow(spec, 30);

    // ����Ʈ
    float diffuse = dot(-toLightDir, worldNormal);
    diffuse = saturate(diffuse);

    // vColor�� ambient color��� ���� ��
    // spec�� specular power ��� ����Ǹ� �󸶳� ó������
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