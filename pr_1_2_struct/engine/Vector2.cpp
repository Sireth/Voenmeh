#include <cmath>
#include "Vector2.h"

Vector2::Vector2(float x, float y) : m_x(x), m_y(y) {}

Vector2 Vector2::zero() {
    return {0, 0};
}

Vector2 Vector2::down() {
    return {0, -1};
}

Vector2 Vector2::left() {
    return {-1, 0};
}

Vector2 Vector2::one() {
    return {1, 1};
}

Vector2 Vector2::right() {
    return {1, 0};
}

Vector2 Vector2::up() {
    return {0, 1};
}

float Vector2::magnitude() const {
    return sqrtf(m_x * m_x + m_y * m_y);
}

Vector2 Vector2::normalized() const {
    float temp = magnitude();
    if (temp == 0) {
        return zero();
    }
    return {m_x / temp, m_y / temp};
}

float Vector2::sqrMagnitude() const {
    return m_x * m_x + m_y * m_y;
}

bool Vector2::equals(const Vector2 &other) const {
    return (m_x == other.m_x) && (m_y == other.m_y);
}

void Vector2::normalize() {
    float temp = magnitude();
    if (temp == 0) {
        *this = zero();
        return;
    }
    this->m_x /= temp;
    this->m_y /= temp;
}

void Vector2::set(float newX, float newY) {
    this->m_x = newX;
    this->m_y = newY;
}

void Vector2::set(const Vector2 &other) {
    *this = other;
}

float Vector2::angle(const Vector2 &from, const Vector2 &to) {
    float scalar = dot(from, to);
    float fromMagnitude = from.magnitude();
    float toMagnitude = to.magnitude();
    if ((fromMagnitude * toMagnitude) == 0) return 0;
    float angleCos = scalar / (fromMagnitude * toMagnitude);
    return acosf(angleCos);
}

float Vector2::distance(const Vector2 &a, const Vector2 &b) {
    float x = a.m_x - b.m_x;
    float y = a.m_y - b.m_y;
    return sqrtf(x * x + y * y);
}

float Vector2::dot(const Vector2 &lhs, const Vector2 &rhs) {
    return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y;
}

Vector2 Vector2::lerp(const Vector2 &a, const Vector2 &b, float t) {
    return {a.m_x + t * (b.m_x - a.m_x), a.m_y + t * (b.m_y - a.m_y)};
}

Vector2 Vector2::max(const Vector2 &lhs, const Vector2 &rhs) {
    return {std::max(lhs.m_x, rhs.m_x), std::max(lhs.m_y, rhs.m_y)};
}

Vector2 Vector2::min(Vector2 lhs, Vector2 rhs) {
    return {std::min(lhs.m_x, rhs.m_x), std::min(lhs.m_y, rhs.m_y)};
}

Vector2 Vector2::moveTowards(Vector2 current, Vector2 target, float maxDistanceDelta) {
    Vector2 direction = target - current;
    float distance = direction.magnitude();

    if (distance <= maxDistanceDelta) {
        return target;
    }

    return current + direction.normalized() * maxDistanceDelta;
}

Vector2 Vector2::scale(Vector2 a, Vector2 b) {
    return {a.m_x * b.m_x, a.m_y * b.m_y};
}

Vector2 &Vector2::operator*=(const float &right) {
    this->m_x *= right;
    this->m_y *= right;
    return *this;
}

Vector2 &Vector2::operator/=(const float &right) {
    if(right == 0){
        *this = Vector2::zero();
        return *this;
    }
    this->m_x /= right;
    this->m_y /= right;
    return *this;
}

Vector2 &Vector2::operator+=(const Vector2 &right) {
    this->m_x += right.m_x;
    this->m_y += right.m_y;
    return *this;
}

Vector2 &Vector2::operator+=(const float &right) {
    this->m_x += right;
    this->m_y += right;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &right) {
    this->m_x -= right.m_x;
    this->m_y -= right.m_y;
    return *this;
}

Vector2 &Vector2::operator-=(const float &right) {
    this->m_x -= right;
    this->m_y -= right;
    return *this;
}

Vector2 Vector2::operator*(const float &right) {
    Vector2 temp = *this;
    temp.m_x *= right;
    temp.m_y *= right;
    return temp;
}

Vector2 Vector2::operator/(const float &right) {
    Vector2 temp = *this;
    if(right == 0){
        return Vector2::zero();
    }
    temp.m_x /= right;
    temp.m_y /= right;
    return temp;
}

Vector2 Vector2::operator+(const Vector2 &right) {
    Vector2 temp = *this;
    temp.m_x += right.m_x;
    temp.m_y += right.m_y;
    return temp;
}

Vector2 Vector2::operator+(const float &right) {
    Vector2 temp = *this;
    temp.m_x += right;
    temp.m_y += right;
    return temp;
}

Vector2 Vector2::operator-(const Vector2 &right) {
    Vector2 temp = *this;
    temp.m_x -= right.m_x;
    temp.m_y -= right.m_y;
    return temp;
}

Vector2 Vector2::operator-(const float &right) {
    Vector2 temp = *this;
    temp.m_x -= right;
    temp.m_y -= right;
    return temp;
}

bool Vector2::operator==(const Vector2 &right) const {
    float epsilon = 0.001f; // задаем малое значение, чтобы учесть погрешности
    return std::abs(m_x - right.m_x) <= epsilon && std::abs(m_y - right.m_y) <= epsilon;
}

bool Vector2::operator!=(const Vector2 &right) const {
    return !operator==(right);
}