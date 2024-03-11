/**
 * @file Vector.h
 * @author Charles Owen
 *
 * Simple 2D vector class
 */

#pragma once

/**
 * Simple 2D vector class
 *
 * This class implements vector operations and operator overloading
 * to simplify the use of 2d vectors in a C++ program.
 */
class Vector {
public:
    Vector(double x, double y);

    Vector();

    ~Vector();

    Vector operator*(double d) const;

    Vector &operator+=(const Vector &a);

    Vector &operator*=(double d);

    Vector &operator/=(double d);

    /// Get the X value
    /// @return X
    double X() const { return mX; }

    /// Get the Y value
    /// @return Y
    double Y() const { return mY; }

    /// Set the vector
    /// @param x X value
    /// @param y Y value
    void Set(double x, double y) {
        mX = x;
        mY = y;
    }

    /// Set the vector from another vector
    /// @param x Other vector
    void Set(const Vector &x) {
        mX = x.mX;
        mY = x.mY;
    }

    /// Set the X component of the vector
    /// @param x X value
    void SetX(double x) { mX = x; }

    /// Set the Y component of the vector
    /// @param y Y value
    void SetY(double y) { mY = y; }

    double Length() const;

    double Distance(const Vector &other) const;

    std::shared_ptr<Vector> Normalize();

private:
    /// X component of vector
    double mX;

    /// Y component of vector
    double mY;
};

Vector operator+(const Vector &a, const Vector &b);
Vector operator-(const Vector &a, const Vector &b);
Vector operator/(const Vector &a, double d);

