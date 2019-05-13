/// <summary>
/// �����p�}�g���N�X
/// </summary>
float4x4 g_blendingMatrix;

/// <summary>
/// �J���[���
/// </summary>
float4 g_color;	

/// <summary>
/// �e�N�X�`��
/// </summary>
texture g_texture;
sampler g_sampler = sampler_state
{
	Texture = <g_texture>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = NONE;

	AddressU = Clamp;
	AddressV = Clamp;
};

//���_�V�F�[�_����s�N�Z���V�F�[�_�ɓn���f�[�^
struct VSInfomationToPS
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 textureUV : TEXCOORD0;
};

/// <summary>
/// �ʏ�I���_�V�F�[�_
/// </summary>
//void ExecuteNormal_vs(float3 in_pos : POSITION, out float4 out_pos : POSITION,
//	out float4 out_color : COLOR0)
//{
//	//���W�ϊ�(���[�J�����W�Ɗ|�����킹)
//	out_pos = mul(float4(in_pos, 1.0f), g_blendingMatrix);
//
//	//���_�̐F�̌���(���̂܂܎g�p)
//	out_color = g_color;
//}

/// <summary>
/// ����т�h�����Z�����s�N�Z���V�F�[�_
/// </summary>
float4 ExecuteCustomAddition_ps(VSInfomationToPS In) : COLOR
{
	float4 color = tex2D(g_sampler, In.textureUV);

	color *= In.color.a;
	
	return color;
}

/// <summary>
/// GraphicEffect�ŗp����e�N�j�b�N
/// </summary>
technique GRAPHIC_EFFECT_TECHNIQUE
{
	/// <summary>
	/// ����т�h���V�F�[�_�p�X
	/// </summary>
	pass CUSTOM_ADDITION
	{
		//vertexShader = compile vs_3_0 ExecuteNormal_vs();
		pixelShader  = compile ps_3_0 ExecuteCustomAddition_ps();
		AlphaBlendEnable = true;
		SrcBlend = SRCALPHA;
		DestBlend = INVSRCALPHA;
	}
}
