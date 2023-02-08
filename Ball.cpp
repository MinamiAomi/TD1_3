#include "Ball.h"
#include "CameraTransform.h"
#include "Resources.h"
#include "Model.h"

Ball::Ball()
{
	m_transform.Initalize();
	for (auto& it : m_itemTrans) {
		it.Initalize();
	}
}

Ball::~Ball()
{
}

void Ball::Initalize()
{
	m_transform.position = { -6.5f,2.0f,-6.5f };
	m_transform.rotate = Quaternion::Identity;
	m_transform.scale = { 1.0f,1.0f,1.0f };
	m_velocity = Vector3::Zero;
	m_acceleration = Vector3::Zero;
	m_normal = Vector3::UnitY;
	m_inertia = 2.0f * m_mass * m_radius * m_radius / 5.0f;
	for (auto& it : m_itemFlag) {
		it = false;
	}
	for (auto& it : m_itemTrans) {
		it.parent = &m_transform;
	}
	m_itemTrans[ClearItem::kTypeCarrot].position = {0.0f,0.0f,-1.2f};
	m_itemTrans[ClearItem::kTypeCarrot].rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(180.0f), Vector3::UnitX);
	m_itemTrans[ClearItem::kTypeCarrot].scale = {0.2f,0.2f,0.2f};
	m_itemTrans[ClearItem::kTypeBucket].position = { 0.5f,1.1f,0.0f };
	m_itemTrans[ClearItem::kTypeBucket].rotate = Quaternion::CreateFromAngleAxis(Math::ToRadians(-20.0f), Vector3::UnitZ) * Quaternion::CreateFromAngleAxis(Math::ToRadians(180.0f), Vector3::UnitX);
	m_itemTrans[ClearItem::kTypeBucket].scale = { 1.0f,1.0f,1.0f };

	m_transform.UpdateMatrix();
}

void Ball::Update()
{
	constexpr float deltaTime = 1.0f / 60.0f;
	constexpr float miu = 0.1f;

	Vector3 gravityForce = m_gravityAcceleration * m_mass;
	Vector3 normalForce = m_normal * -Dot(gravityForce, m_normal);
	Vector3 frictionalForce = -m_velocity.Normalized() * miu * (-m_mass * m_gravityAcceleration).Length();

	Vector3 force;

	
	if (m_velocity.Length() > 0.01f) {
		force += frictionalForce;
	}

	force += gravityForce;
	force += normalForce;
	force.y = 0.0f;
	m_acceleration += force / m_mass;
		
	m_velocity += m_acceleration * deltaTime;
	m_transform.position += m_velocity * deltaTime;
	m_acceleration = Vector3::Zero;

	if (m_velocity.IsZero() == false) {
		m_transform.rotate = Quaternion::CreateFromAngleAxis(m_velocity.Length() * deltaTime / Math::Pi * 2.0f * m_radius, Cross(m_velocity, -Vector3::UnitY).Normalized()) * m_transform.rotate;

	}
	m_collider.center = m_transform.position.xz();
	m_collider.radius = m_radius;
}

void Ball::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	Resource::GetInstance()->GetModel().sphere->Draw(&m_transform, camera);

	if (m_itemFlag[ClearItem::kTypeCarrot] == true) {
		m_itemTrans[ClearItem::kTypeCarrot].UpdateMatrix();
		Resource::GetInstance()->GetModel().carrot->Draw(&m_itemTrans[ClearItem::kTypeCarrot], camera);
	}
	if (m_itemFlag[ClearItem::kTypeBucket] == true) {
		m_itemTrans[ClearItem::kTypeBucket].UpdateMatrix();
		Resource::GetInstance()->GetModel().bucket->Draw(&m_itemTrans[ClearItem::kTypeBucket], camera);
	}
}

void Ball::OnCollisionWall(const Vector2& closestPoint)
{
	constexpr float e = 0.8f;	// îΩî≠åWêî

	Vector2 normal = m_transform.position.xz() - closestPoint;
	normal = normal.Normalized();
	Vector2 newPos = closestPoint + normal * m_radius;
	m_transform.position.xz(newPos);
	

	//m_velocity = AlongWall(m_velocity, Vector3(normal.x,0.0f,normal.y).Normalized());
	
	m_velocity = Reflected(m_velocity, Vector3(normal.x,0.0f,normal.y).Normalized()) * e;
	//m_acceleration += Reflected(m_velocity, Vector3(normal.x,0.0f,normal.y).Normalized());
	
}

void Ball::OnCollisionItem(ClearItem::Type type)
{
	m_itemFlag[type] = true;
}
