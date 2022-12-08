#include "Camera2D.h"

Camera2D::Camera2D() {}

Camera2D::Camera2D(unsigned int width, unsigned int height) :
	windowWidth(width), windowHeight(height) {}

void Camera2D::SetUpMatrix() {
	projectionMat = Matrix44::CreateOrthoProjection(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
	transformMat = projectionMat;
}

/////////////////////////

Camera2DView::Camera2DView() {}
Camera2DView::Camera2DView(unsigned int width, unsigned int height) :
	Camera2D(width, height) {}

void Camera2DView::SetUpMatrix() {
	// �ˉe�s����Z�b�g
	Camera2D::SetUpMatrix();
	// �r���[�s����Z�b�g
	viewMat = Matrix44::Create2DView(anchorPoint, scroll, scale, rotation);
	// �r���[ * �ˉe
	SetTransformMatrix(viewMat * GetTransformMatrix());
}