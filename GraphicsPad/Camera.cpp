#include "Camera.h"
#include <glm\gtx\transform.hpp>
 
Camera::Camera() : 
	//initialize camera view direction
	viewDirection (0.0f, 0.0f, -1.0f), 
	//initialize camera up direction
				UP(0.0f, 1.0f, 0.0f)
{

}

//use mouse to control camera rotation
void Camera::mouseUpdate(const glm::vec2& newMousePosition)
{
	//camera rotation about y
	glm::vec2 mouseDelta = newMousePosition - oldMousePostion;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePostion = newMousePosition;
		return;
	}
	const float ROTATIONAL_SPEED = 0.5f;
	viewDirection = glm::mat3(glm::rotate(-mouseDelta.x * 0.5f, UP)) * viewDirection;

	//cross product of UP and view direction
	glm::vec3 toRotateAround = glm::cross(viewDirection, UP);
	
	glm::mat4 rotator = glm::rotate(-mouseDelta.x * ROTATIONAL_SPEED, UP) * 
		glm::rotate(-mouseDelta.y * ROTATIONAL_SPEED, toRotateAround);

	viewDirection = glm::mat3(rotator) * viewDirection;

	oldMousePostion = newMousePosition;
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}
