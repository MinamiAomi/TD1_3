#pragma once
#include "WorldTransform.h"
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "MathUtility.h"
#include <memory>
#include <wrl.h>
#include "Shape.h"
#include "jsonLoader.h"
#include "Collision2D.h"

class CameraTransform;

class Block
{
private:
	template<class TYPE>
	using ComPtr = Microsoft::WRL::ComPtr<TYPE>;

private:
	struct Vertex {
		Vector3 position;
		Vector3 normal;
	};

	struct ColorConstData {
		Vector4 color;
	};


	enum RootParameterIndex
	{
		kRootParameterIndexWorldTransform,			// ワールド行列
		kRootParameterIndexCameraTransform,		// カメラデータ（行列も含む）
		kRootParameterIndexColor,		// 色

		kRootParameterIndexCount
	};

public:
	enum Type {
		kBlockTypeNone,
		kBlockTypeSnow,

		kBlockTypeCount
	};



private:
	// Z軸方向の幅
	static float s_zWidth;
	// 共有カメラ
	static CameraTransform* s_camera;

	static ComPtr<ID3D12RootSignature> rootSignature; // ルートシグネチャ
	static ComPtr<ID3D12PipelineState> pipelineState; // パイプラインステート
	static VertexBuffer<Vertex> m_vertBuff;
	static IndexBuffer m_indexBuff;
	static std::vector<Vertex> m_vertcies;
	static std::vector<uint16_t> m_indcies;

public:
	static void StaticInitalize();
	static void StaticDraw(WorldTransform* trans, ConstBuffer<ColorConstData>& constData);

	static void zWidth(float zWidth) { s_zWidth = zWidth; }
	static float zWidth() { return s_zWidth; }
	static void camera(CameraTransform* camera) { s_camera = camera; }
private:

	Type m_type;

	Shape2D::RectAngle m_rect;
	// 3D用
	WorldTransform m_world;
	class Model* m_model;
	ConstBuffer<ColorConstData> m_constData;

	Collider2D::OBB m_collider;
	
	WorldTransform coll;
	float a;

public:
	Block();
	~Block();
	
	void type(int type) { m_type = static_cast<Type>(type); }
	void center(const Vector2& center) { m_rect.center = center; }
	void width(float width) { m_rect.width = width; }
	void height(float height) { m_rect.height = height; }
	void rotate(float rotate) { m_rect.rotate = rotate; }
	void parent(WorldTransform* parent) { m_world.parent = parent; }

	int type() const { return static_cast<int>(m_type); }
	const Vector2& center() const { return m_rect.center; }
	float width() const { return m_rect.width; }
	float height() const { return m_rect.height; }
	float rotate() const { return m_rect.rotate; }
	

	void Initalize(const BlockJsonData& data, float z_width, WorldTransform* parent);
	void Initalize();
	void Update();
	void PreCollision();
	void PreCollision1(float a);
	void PreCollision2();
	void Draw();
	
	const Collider2D::OBB& collider() const { return m_collider; }

	operator BlockJsonData() const;
};

