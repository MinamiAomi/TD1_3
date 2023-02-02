#include "SnowBall.h"
#include "Resource.h"
#include "Model.h"
#include "TimeManager.h"
#include "Block.h"
#include "Input.h"

SnowBall::SnowBall()
{
}

SnowBall::~SnowBall()
{
}

void SnowBall::Initalize()
{
	m_transform.Initalize();
	m_transform.position = Vector3(0, 3, 0);
	m_transform.scale = Vector3(m_radius);

	normal = Vector2::Zero;
	
	m_goalItems[0] = {};
	m_goalItems[1] = {};
	m_goalItems[2] = {};

	m_isGameOver = false;
}

void SnowBall::Update()
{
	
	prePos = m_transform.position.xy();

	auto input = Input::GetInstance();

	if (input->IsKeyTrigger(DIK_R)) {
		m_transform.position = Vector3(0, 3, 0);
		m_velocity = Vector2::Zero;
	}

	Vector2 force;

	force += -Vector2::UnitY * m_gravity;

	if (normal.IsZero() == false) {
		force += -Dot(normal, Vector2::UnitY * m_gravity) * normal;
	}
	m_velocity += force / m_mass * Time::deltaTime();

	Vector3 pos = m_transform.position;

	pos += Vector3(m_velocity * Time::deltaTime(), 0);

	m_transform.position = pos;

	normal = Vector2::Zero;
}

void SnowBall::PreCollision()
{
	m_collider.center = m_transform.position.xy();
	m_collider.radius = m_radius;
}

void SnowBall::OnCollisionBlock(const Vector2& closestPoint, Block::Type blockType)
{

	if(Vector2(prePos - m_transform.position.xy()).Length() > 0.01f)
	switch (blockType)
	{
	case Block::kBlockTypeNone:
		m_radius -= 0.001f;
		break;
	case Block::kBlockTypeSnow:
	default:
		m_radius += 0.001f;
		break;
	}
	if (m_radius >= 2.0f) {
		m_isGameOver = true;
	}
	else if (m_radius <= 0.2f) {
		m_isGameOver = true;
	}

	m_transform.scale = Vector3(m_radius);

	Vector2 pos = m_transform.position.xy();
	if (pos != closestPoint) {
		normal = pos - closestPoint;
		normal = normal.Normalized();
		Vector2 newPos = closestPoint + normal * m_radius;
		pos = newPos;
		m_transform.position.xy(pos);
	}
		
	//m_velocity = Reflected(m_velocity, normal) * 0.8f;
	//m_velocity += -Dot(m_velocity, normal) * normal;
	m_velocity = WallSlided(m_velocity, normal);
	
}

void SnowBall::OnCollisionItem(Item::TypeId type)
{
	m_goalItems[type] = true;
}

void SnowBall::OnCollisionGoal()
{

	m_isGameClear = true;
}


void SnowBall::Draw()
{
	m_transform.UpdateMatrix();
	auto& model = Resource::GetInstance()->GetModel().sphere;

	model->Draw(&m_transform, m_camera);
}


void SnowBall::Collision(std::vector<std::unique_ptr<class Block>>& blocks)
{
//Vector2 pos = m_transform.position.xy();
//for (auto& it : blocks) {
//	Vector2 cp;
//	if (Collision2D::Hit_Circle_OBB(m_collider, it->GetCollider(), cp)) {
//		Vector2 normal = pos - cp;
//		normal = normal.Normalized();
//		m_velocity = Reflected(m_velocity, normal) * 0.8f;
//		Vector2 newPos = cp + normal * m_radius;
//		pos = newPos;
//	}
//}
//m_transform.position.xy(pos);
}
