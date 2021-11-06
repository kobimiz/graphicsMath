#include "../headers/vec3.h"

Vec3::Vec3() {
	this->x = this->y = this->z = 0.0f;
}
Vec3::Vec3(const Vec3& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}
Vec3::Vec3(Vec3&& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}
Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Vec3& Vec3::operator=(const Vec3& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
    return *this;
}
Vec3& Vec3::operator=(Vec3&& vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
    return *this;
}
Vec3 Vec3::operator+(const Vec3& vec) const {
    return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}
Vec3 Vec3::operator+(Vec3&& vec) const {
    return Vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}
Vec3 Vec3::operator-(const Vec3& vec) const {
    return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}
Vec3 Vec3::operator-(Vec3&& vec) const {
    return Vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}