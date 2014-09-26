//
//  matrixMath.h
//
//  Created by Martin Beroiz on 4/17/12.
//  Copyright (c) 2012 Normandin-Beroiz. All rights reserved.
//

#ifndef openglTest_matrixMath_h
#define openglTest_matrixMath_h

// Populates matrix m with the translation of m by vector (x,y,z)
// m <- Transl * m
void translate(float x, float y, float z, float m[16]);


// These populate matrix m with the rotation of m by an angle 'angle' in degrees
// around x, y or z axis.
// m <- Rot * m
void rotatex(float angle, float m[16]);
void rotatey(float angle, float m[16]);
void rotatez(float angle, float m[16]);


// These populate matrix m with the rotation of m by an angle 'angle' in degrees
// around vector (x,y,z).
// m <- Rot * m
void rotatev(float angle, float x, float y, float z, float m[16]);


// Populates matrix m with the scale of m by vector (x,y,z)
// m <- Scale * m
void scale(float x, float y, float z, float m[16]);


// Populates matrix m with the projection matrix multiplying m.
// m <- Proj * m
void project(float near, float far, float fieldOfView, float aspect, float m[16]);


void loadIdentityMatrix(float m[16]);



#endif
