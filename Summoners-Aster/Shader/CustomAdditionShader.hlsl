/// <summary>
/// 合成用マトリクス
/// </summary>
float4x4 g_blendingMatrix;

/// <summary>
/// カラー情報
/// </summary>
float4 g_color;	

/// <summary>
/// テクスチャ
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

//頂点シェーダからピクセルシェーダに渡すデータ
struct VSInfomationToPS
{
	float4 position : POSITION;
	float4 color : COLOR;
	float2 textureUV : TEXCOORD0;
};

/// <summary>
/// 通常的頂点シェーダ
/// </summary>
//void ExecuteNormal_vs(float3 in_pos : POSITION, out float4 out_pos : POSITION,
//	out float4 out_color : COLOR0)
//{
//	//座標変換(ローカル座標と掛け合わせ)
//	out_pos = mul(float4(in_pos, 1.0f), g_blendingMatrix);
//
//	//頂点の色の決定(そのまま使用)
//	out_color = g_color;
//}

/// <summary>
/// 白飛びを防ぐ加算合成ピクセルシェーダ
/// </summary>
float4 ExecuteCustomAddition_ps(VSInfomationToPS In) : COLOR
{
	float4 color = tex2D(g_sampler, In.textureUV);

	color *= In.color.a;
	
	return color;
}

/// <summary>
/// GraphicEffectで用いるテクニック
/// </summary>
technique GRAPHIC_EFFECT_TECHNIQUE
{
	/// <summary>
	/// 白飛びを防ぐシェーダパス
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
