#ifndef GAME_MATH_H
#define GAME_MATH_H

#include <math.h>
#include <ctype.h>
#include <stdbool.h>

// Converts an angle from radians to degrees.
#define RAD_TO_DEG(rad) (rad * (180 / M_PI))

// Converts an angle from degrees to radians.
#define DEG_TO_RAD(deg) (deg * (M_PI / 180))

// Raises a given expressiom to the second power.
#define SQUARE(expr) ((expr) * (expr))

// A two-dimensional vector point.
struct vector2d
{
    double x; // X co-ordinate of the object.
    double y; // Y co-ordinate of the object.
};

static inline float convert_to_angle(float x, float y)
{
    float angle_rad = atan2(y, x);
    return RAD_TO_DEG(angle_rad);
}

static inline float pythagoras(float x, float y)
{
    return sqrt(pow(x,2) + pow(y,2));
}

static inline struct vector2d direction_between_points(struct vector2d source, struct vector2d target)
{
    struct vector2d result;

    result.x = target.x - source.x;
    result.y = target.y - source.y;

    return result;
}

static inline struct vector2d vector2d_scalar_mult(struct vector2d *vec, float s)
{
    vec->x = vec->x * s; // Multiply the x co-ordinate by the scalar s
    vec->y = vec->y * s; // Multiply the y co-ordinate by the scalar s

    return *vec; // Return the updated vector.
}

static inline struct vector2d vector2d_addition(struct vector2d *vec, struct vector2d *vec2)
{
    struct vector2d result; // Instantiate a new vector to return since we dont want to update the existing one.

    result.x = vec->x + vec2->x; // Add both vector's x co-ordinates together and save them to the new vector.
    result.y = vec->y + vec2->y; // Add both vector's y co-ordinates together and save them to the new vector.

    return result; // Return the new vector.
}

#endif // GAME_MATH_H