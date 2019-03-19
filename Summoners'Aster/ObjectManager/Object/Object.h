#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
	~Object();

	virtual bool Initialize() = 0;
	virtual bool LoadResource() = 0;

	virtual void Finalize() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	inline float GetZ() const 
	{
		return m_z; 
	}
	
protected:
	Object(float z);

	//描画順をセットする為の変数
	float m_z = 1.0f;
};

#endif //!OBJECT_H
