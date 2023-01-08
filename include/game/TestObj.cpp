#include "TestObj.h"
#include "CameraTransform.h"
#include "Model.h"
#include "Resource.h"
#include "Input.h"

TestObj::TestObj()
{
}

TestObj::~TestObj()
{
}

void TestObj::Initalize(CameraTransform* camera)
{
	m_transform.Initalize();
	m_transform2.Initalize();
	m_model = Resource::GetInstance()->GetModel().axis.get();
	m_transform.scale = { 10.0f,10.0f,10.0f };
	m_transform2.scale = { 10.0f,10.0f,10.0f };
	m_transform.position = { -10.0f,10.0f,10.0f };
	m_transform2.position = { -10.0f,10.0f,10.0f };
	m_camera = camera;
}

void TestObj::Update()
{

	Vector3 rotate;

	auto input = Input::GetInstance();

	int up = 0;

	if (input->IsKeyPressed(DIK_UP)) {
		up += 1;
	}
	if (input->IsKeyPressed(DIK_DOWN)) {
		up += -1;
	}


	Vector3 mouseFar = { input->GetMousePosition(), 1.0f};
	Vector3 mouseNear = { input->GetMousePosition(), 0.0f };
	
	Matrix44 viewportInv= Matrix44::CreateViewport(0, 0, 1280, 720).Inverse();
	Matrix44 projInv = m_camera->projMat.Inverse();
	Matrix44 viewInv = m_camera->viewMat.Inverse();

	Matrix44 invMat = viewportInv * projInv * viewInv;

	Vector4 farV4 = Vector4{ mouseFar, 1.0f } * invMat;
	Vector4 nearV4 = Vector4{ mouseNear, 1.0f } * invMat;

	mouseFar = farV4.xyz() / farV4.w;
	mouseNear = nearV4.xyz() / nearV4.w;

	
	
	Vector3 mouseRay = mouseFar - mouseNear;

	Vector3 wallNormal = -Vector3::UnitZ;

	float dot1 = Dot(Vector3::Zero - mouseNear, wallNormal);
	float dot2 = Dot(mouseFar - mouseNear, wallNormal);

	Vector3 inter = mouseNear + dot1 / dot2 * mouseRay;

	m_transform.position = mouseFar;
	m_transform2.position = inter;



	if (input->IsKeyPressed(DIK_X)) {
		rotate.x += Math::ToRadians(1.0f) * up;
	}
	if (input->IsKeyPressed(DIK_Y)) {
		rotate.y += Math::ToRadians(1.0f) * up;
	}
	if (input->IsKeyPressed(DIK_Z)) {
		rotate.z += Math::ToRadians(1.0f) * up;
	}
	
	rotation = Quaternion::CreateFromEuler(rotate) * rotation;

	//rotation = Quaternion::CreateFromAngleAxis(Math::ToRadians(up), Vector3::UnitY) * rotation;
}

void TestObj::Draw(CameraTransform* camera)
{
	//m_transform.UpdateMatrix();
	//m_transform.worldMatrix = Matrix44::CreateScaling(m_transform.scale) * Matrix44::CreateRotationFromQuaternion(rotation) * Matrix44::CreateTranslation(m_transform.position);
	m_transform2.worldMatrix = Matrix44::CreateScaling(m_transform2.scale) * Matrix44::CreateRotationFromQuaternion(rotation) * Matrix44::CreateTranslation(m_transform2.position);
	m_model->Draw(&m_transform, camera);
	m_model->Draw(&m_transform2, camera);
}
