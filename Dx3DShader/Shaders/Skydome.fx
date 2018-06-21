float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

float4 vApexColor; // SkyDome�� ����� �÷�
float4 vCenterColor; // SkyDome�� �߾Ӵ� �÷�

struct VS_OUTPUT
{
    float4 position : POSITION; // POSITION �ø�ƽ�̶�� �ϸ� ���� ������� ���ϴ°�
    float4 domePosition : TEXCOORD0;
};

VS_OUTPUT VS(float3 position : POSITION)
{
    VS_OUTPUT output;
    output.position = mul(float4(position, 1.0), matWorld);
    output.position = mul(output.position, matView);
    output.position = mul(output.position, matProjection);
    output.domePosition = mul(float4(position, 1.0), matWorld);

    return output;
}

float4 PS(VS_OUTPUT input) : COLOR0
{
    float height = input.domePosition.y;

    if (height < 0.0f)
        height = 0.0f;

    float4 finalColor = lerp(vCenterColor, vApexColor, height);

    //return float4(1, 0, 0, 1);
    return finalColor;
}

technique SkyDome
{
    pass PO
    {
        VertexShader = compile vs_3_0 VS();
        PixelShader = compile ps_3_0 PS();
    }
}