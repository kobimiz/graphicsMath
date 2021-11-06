#ifndef VEC3_H
#define VEC3_H

// TODO benchmark stack vs heap allocation here (move)
class Vec3 {
public:
    float x, y, z;
    
    Vec3 ();
    Vec3 (Vec3&& vec);
    Vec3 (const Vec3& vec);
    Vec3 (float x, float y, float z);

    Vec3& operator=(const Vec3& vec);
    Vec3& operator=(Vec3&& vec);
    Vec3  operator+(const Vec3& vec) const;
    Vec3  operator+(Vec3&& vec) const;
    Vec3  operator-(const Vec3& vec) const;
    Vec3  operator-(Vec3&& vec) const;
};

#endif