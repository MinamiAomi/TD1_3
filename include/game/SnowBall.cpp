#include "SnowBall.h"
#include "Resource.h"
#include "Model.h"
#include "TimeManager.h"
#include "Block.h"
#include "Input.h"

SnowBall::SnowBall()
{
	m_transform.Initalize();
}

SnowBall::~SnowBall()
{
}

void SnowBall::Initalize()
{
	m_transform.position = Vector3(0, 30, 0);
	m_transform.scale = Vector3(m_radius);
	
}

void SnowBall::Update()
{
	auto input = Input::GetInstance();

	if (input->IsKeyTrigger(DIK_R)) {
		m_transform.position = Vector3(0, 30, 0);
		m_velocity = Vector2::Zero;
	}

	Vector2 force;

	force += -Vector2::UnitY * m_gravity;

	m_velocity += force / m_mass * Time::deltaTime();

	Vector3 pos = m_transform.position;

	pos += Vector3(m_velocity * Time::deltaTime(), 0);

	m_transform.position = pos;
}

void SnowBall::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	auto& model = Resource::GetInstance()->GetModel().sphere;

	model->Draw(&m_transform, camera);
}

void SnowBall::SetCollider()
{
	m_collider.center = m_transform.position.xy();
	m_collider.radius = m_radius;
}

void SnowBall::Collision(std::vector<std::unique_ptr<class Block>>& blocks)
{
	Vector2 pos = m_transform.position.xy();
	for (auto& it : blocks) {
		Vector2 cp;
		if (Collision2D::Hit_Circle_OBB(m_collider, it->GetCollider(), cp)) {
			Vector2 normal = pos - cp;
			normal = normal.Normalized();
			m_velocity = Reflected(m_velocity, normal) * 0.8f;
			Vector2 newPos = cp + normal * m_radius;
			pos = newPos;
		}
	}
	m_transform.position.xy(pos);
}
