#include "kpCamera.h"
#include "../kpEngine.h"

JackFruitEngine::kpCamera::kpCamera(void)
{
}
JackFruitEngine::kpCamera::kpCamera(float fov, float aspect, float zNear, float zFar)
{
	m_projection = new kpMatrix4f();
	m_projection->identity();
	m_projection->initPerspective(fov, aspect, zNear, zFar);
}

JackFruitEngine::kpCamera::~kpCamera(void)
{
}
void JackFruitEngine::kpCamera::setAsMain()
{
	kpRenderEngine* tmp = kpEngine::getEngine()->getRenderer();
	tmp->setCamera(this);
}
JackFruitEngine::kpMatrix4f* JackFruitEngine::kpCamera::GetViewProjection() const
{
	kpMatrix4f *tmp = new kpMatrix4f();
	kpTransform *t = new kpTransform();
	kpMatrix4f camrot = t->getTransformedRot().conjugate().toRotationMatrix();
	kpMatrix4f cameraTranslation;
	cameraTranslation.initTranslation(t->getTransformedPos() * -1);
	//*tmp = m_projection;
	return &m_projection->mul(camrot.mul(cameraTranslation));
}
JackFruitEngine::kpMatrix4f* JackFruitEngine::kpCamera::GetViewProjection(kpGameObject* obj) const
{
	//kpMatrix4f camrot = obj->getTransform()->getTransformedRot()->conjugate()->toRotationMatrix();
	kpMatrix4f *tmp = new kpMatrix4f();
	//*tmp = m_projection;
	return m_projection;
}