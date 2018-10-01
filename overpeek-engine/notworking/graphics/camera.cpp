#include "camera.h"

namespace graphics {

	Camera::Camera(glm::vec3 pos, GLfloat pitch, GLfloat yaw, GLuint fov, GLfloat aspect) {
		mPos = pos; mPitch = pitch; mYaw = yaw; mFov = fov; mAspect = aspect;

		setProjection(mFov, mAspect);
		updateCamera();
	}

	void Camera::updateCamera() {
		glm::mat4 matPitch = glm::rotate(glm::mat4(1.0f), mPitch, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 matYaw = glm::rotate(glm::mat4(1.0f), mYaw, glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 rotation = matPitch * matYaw;
		glm::mat4 translation = glm::translate(glm::mat4(1.0f), -mPos);

		mViewMatrix = rotation * translation;
	}

	void Camera::setProjection(GLuint fov, GLfloat aspect) {
		mFov = fov; mAspect = aspect;
		mProjectionMatrix = glm::perspective(glm::radians(static_cast<float>(mFov)), mAspect, 0.1f, 100.0f);
	}

}