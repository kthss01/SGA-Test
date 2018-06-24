float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vDiffuseColor;
float4 vSpecularColor;

float3 vLightDir; // ������ ���� (����ȭ�� ���������)
float3 vEyePos; // ���� ��ġ�� (ī�޶��� ��ġ��)
float fPower; // ���ݻ� ��ī�ӱ�

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

// TEXCOORD uv, ��ǥ, �Ǵ� �ָ��Ѱ͵��� �̰� �ٿ��� ������ ��
// TEXCOORD�� ���� �� �ִ� ������ 8���� ���ѵǾ�����

struct VS_OUTPUT
{
    float4 position : POSITION; // ������ ��ȯ�ؾ���
    float3 normal : TEXCOORD0; // ��ǥ������ ����Ҳ��� texcoord�� �־������
    float3 eyeDir : TEXCOORD1; 
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;

    // ���� ���� ��ġ
    float4 worldPos = mul(float4(input.position, 1.0f), matWorld);

    output.position = mul(worldPos, matView);
    output.position = mul(output.position, matProjection);

    // ���� �븻
    // �������� �� ���� normalize �� ������
    float3 worldNormal = mul(input.normal, (float3x3) matWorld);
    worldNormal = normalize(worldNormal);

    output.normal = worldNormal;
    
    // ���� ����
    float3 eyeDir = vEyePos - worldPos.xyz; // �������� ���� Ư������ �̾Ƴ��°�
    eyeDir = normalize(eyeDir);

    output.eyeDir = eyeDir;

    return output;
}

float4 PS(VS_OUTPUT input) : COLOR0
{
    // ��ֶ����� �ѹ� �� �� ����
    // ��ֶ����� �ϰ� ���� �Ѿ������ 
    // �ȼ��� ��ǥ�� ���ؼ� ��ֶ������ ���·� ���´� ������ ����
    float3 normal = normalize(input.normal);
    float3 eyeDir = normalize(input.eyeDir);

    // ���� ���� ����
    float3 toLight = -vLightDir;

    // Diffuse
    float diffuse = saturate(dot(toLight, normal));

    // Reflection - Specular�� ����� ���� ����
    float3 inLight = -toLight;
    float3 lightReflect = inLight + 2 * (dot(-inLight, normal) * normal);
    lightReflect = normalize(lightReflect);

    // Specular
    float spec = saturate(dot(lightReflect, eyeDir));

    spec = pow(spec, fPower);

    // ambient color�� �ִٸ� vDiffuseColor�� �����ָ��

    // ���� �����ִ°� �����ְ� �����°� �����ָ� ��

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