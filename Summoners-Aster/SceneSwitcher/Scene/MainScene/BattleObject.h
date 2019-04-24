#ifndef BATTLE_OBJECT_H
#define BATTLE_OBJECT_H

#include <GameFramework.h>
namespace summonersaster
{
class BattleObject
{
public:
	BattleObject();
	virtual ~BattleObject();

	/// <summary>
	/// 矩形情報の設定
	/// </summary>
	/// <param name="center">矩形の中心</param>
	/// <param name="size">矩形の幅と高さ</param>
	/// <param name="color">矩形の色</param>
	void SetVertex(const D3DXVECTOR3& center, const gameframework::RectSize& size, const gameframework::Color& color);

	/// <summary>
	/// 矩形情報の設定
	/// </summary>
	/// <param name="center">矩形の中心</param>
	/// <param name="size">矩形の幅と高さ</param>
	/// <param name="color">矩形の色</param>
	/// <param name="textureUVs">UV情報</param>
	void SetVertex(const D3DXVECTOR3& center, const gameframework::RectSize& size, const gameframework::Color& color,const gameframework::TextureUVs& textureUVs);

	/// <summary>
	/// 画像の描画
	/// </summary>
	/// <param name="pTextureKey">テクスチャキー</param>
	void DrawTexture(const TCHAR* pTextureKey);

	/// <summary>
	/// 文字列をフォントで描画
	/// </summary>
	/// <param name="topLeft">左上の位置</param>
	/// <param name="fontKey">フォントキー</param>
	/// <param name="format">テキストフォーマット</param>
	void WriteWords(const D3DXVECTOR2 topLeft, const TCHAR* fontKey, int format);

	/// <summary>
	/// 文字列をフォントで描画
	/// </summary>
	/// <param name="topLeft">左上の位置</param>
	/// <param name="fontKey">フォントキー</param>
	/// <param name="format">テキストフォーマット</param>
	/// <param name="color">文字の色</param>
	void WriteWords(const D3DXVECTOR2 topLeft, const TCHAR* fontKey, int format, const gameframework::Color& color);

	/// <summary>
	/// 変数から文字列の設定
	/// </summary>
	/// <param name="words">文字列</param>
	/// <param name="variable">設定したい変数</param>
	template<typename BattleTmp>inline void SetString(const TCHAR* words, const BattleTmp variable)
	{
		const int ARRAY_SIZE = 128;
		TCHAR str[ARRAY_SIZE];
		_stprintf_s(str, ARRAY_SIZE, words, variable);
		SetString(str);
	};

	/// <summary>
	/// 文字列の設定
	/// </summary>
	/// <param name="words"></param>
	void SetString(const TCHAR* words);

protected:
	gameframework::RectSize m_PolygonSize;

	gameframework::Vertices* m_pRect = nullptr;
	gameframework::GameFramework& m_rGameFramework = gameframework::GameFramework::GetRef();
	gameframework::Stream* m_pStream = nullptr;
};
}
#endif
