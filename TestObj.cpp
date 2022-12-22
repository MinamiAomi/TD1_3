#include "TestObj.h"
#include "CameraTransform.h"
#include "Model.h"
#include "Resource.h"

TestObj::TestObj()
{
}

TestObj::~TestObj()
{
}

void TestObj::Initalize()
{
	m_transform.Initalize();
	m_model = Resource::GetInstance()->GetModel().axis.get();
}

void TestObj::Update()
{
}

void TestObj::Draw(CameraTransform* camera)
{
	m_transform.UpdateMatrix();
	m_model->Draw(&m_transform, camera);
}
