#ifndef TERM_2_VECTOR2_H
#define TERM_2_VECTOR2_H


class Vector2 {
public:
    float m_x = 0;
    float m_y = 0;


    Vector2() = default;

    Vector2(float x, float y);


    static Vector2 zero();

    static Vector2 down();

    static Vector2 left();

    static Vector2 one();

    static Vector2 right();

    static Vector2 up();


    [[nodiscard]] float magnitude() const;

    [[nodiscard]] Vector2 normalized() const;

    [[nodiscard]] float sqrMagnitude() const;


    [[nodiscard]] bool equals(const Vector2 &other) const;

    void normalize();

    void set(float newX, float newY);

    void set(const Vector2 &other);


    static float angle(const Vector2 &from, const Vector2 &to);

    static float distance(const Vector2 &a, const Vector2 &b);

    static float dot(const Vector2 &lhs, const Vector2 &rhs);

    static Vector2 lerp(const Vector2 &a, const Vector2 &b, float t);

    static Vector2 max(const Vector2 &lhs, const Vector2 &rhs);

    static Vector2 min(Vector2 lhs, Vector2 rhs);

    static Vector2 moveTowards(Vector2 current, Vector2 target, float maxDistanceDelta);

    static Vector2 scale(Vector2 a, Vector2 b);


    Vector2 &operator*=(const float &right);

    Vector2 &operator/=(const float &right);

    Vector2 &operator+=(const Vector2 &right);

    Vector2 &operator+=(const float &right);

    Vector2 &operator-=(const Vector2 &right);

    Vector2 &operator-=(const float &right);

    Vector2 operator*(const float &right);

    Vector2 operator/(const float &right);

    Vector2 operator+(const Vector2 &right);

    Vector2 operator+(const float &right);

    Vector2 operator-(const Vector2 &right);

    Vector2 operator-(const float &right);

    bool operator==(const Vector2 &right) const;

    bool operator!=(const Vector2 &right) const;

};

#endif //TERM_2_VECTOR2_H