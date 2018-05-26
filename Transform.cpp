/** this code imlements a crystal ball interface,
please note that this code does not work on it's own, this simply implements
the required rotations, the rest of the code is in the EDX computer graphics course, offered
by UC san diego, **//

#include "Transform.h"
#include <iostream>


// Helper rotation function.
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  //  implementation of the rodriguez rotation formula
	float rads = glm::radians(degrees);
	float c = cos(rads);
	float s = sin(rads);
	float t = 1 - c;
	vec3 vect = axis;

	mat3 rotation(t*vect.x*vect.x + c, t*vect.x*vect.y + vect.z*s, t*vect.x*vect.z - vect.y*s,
		t*vect.x*vect.y - vect.z*s, t*vect.y*vect.y + c, t*vect.y*vect.z + vect.x*s,
		t*vect.x*vect.z + vect.y*s, t*vect.y*vect.z - vect.x*s, t*vect.z*vect.z + c);


	return rotation;
}


void Transform::left(float degrees, vec3& eye, vec3& up) {
	/**
	thinking of this geometrically, a trotation to the left is really a
	rotation around the up vector
	**/
	mat3 rotation = rotate(-degrees, up);
	eye = eye * rotation;


}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
/**
similarly, a rotation to up(or bottom), will be around an axis pependicular to
both the eye location and the up vector, note that in the initial position this
simply gives the x axis, and this makes sense
**/
	vec3 ax = glm::normalize(glm::cross(eye, up));
	mat3 rotation = rotate(-degrees, vec3(ax.x,ax.y,ax.z));
	eye = eye * rotation;
	up = up * rotation;
}


mat4 Transform::lookAt(vec3 eye, vec3 up) {
/**
the lookat function, first finds f, the the vector that goes out of
the camera lens, so to speak, then, by taking the cross product with the up vector(s),
we will find the x axis, from the camera's point of view,
and by taking the cross product of  s and f, we find the up vector from the camera's
point of view, note that we are essentially creating a coordinate frame
    **/
	vec3 f = glm::normalize(-eye);
	vec3 UP = glm::normalize(up);
	vec3 s = glm::normalize(glm::cross(f,up));
	vec3 u = glm::cross(s, f);
	mat4 M(s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		0, 0, 0, 1);
		/**
		after doing all this, we have a coordinate frame, but we still need to move
		the camera to the needed position, which is done by this translation:
		**/
	mat4 translate(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-eye.x, -eye.y, -eye.z, 1);

	return M * translate;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
