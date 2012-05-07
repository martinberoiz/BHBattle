//
//  matrixMath.c
//
//  Created by Martin Beroiz on 4/17/12.
//  Copyright (c) 2012 Normandin-Beroiz. All rights reserved.
//

#include <math.h>
#include <string.h>
#include "matrixMath.h"



// Populates matrix m with the translation of m by vector (x,y,z)
// m <- Transl * m
void translate(float x, float y, float z, float m[16]) {
    
    m[0] += x*m[3];
    m[1] += y*m[3];
    m[2] += z*m[3];

    m[4] += x*m[7];
    m[5] += y*m[7];
    m[6] += z*m[7];

    m[8] += x*m[11];
    m[9] += y*m[11];
    m[10] += z*m[11];

    m[12] += x*m[15];
    m[13] += y*m[15];
    m[14] += z*m[15];

}

// Populates matrix m with the scale of m by vector (x,y,z)
// m <- Scale * m
void scale(float x, float y, float z, float m[16]) {
    
    m[0] *= x;
    m[1] *= y;
    m[2] *= z;
    
    m[4] *= x;
    m[5] *= y;
    m[6] *= z;

    m[8] *= x;
    m[9] *= y;
    m[10] *= z;

    m[12] *= x;
    m[13] *= y;
    m[14] *= z;
    
}

// Populates matrix m with the rotation of m by an angle 'angle' in degrees
// around x axis.
// m <- Rot * m
void rotatex(float angle, float m[16]) {
    
    float temp;
    float cosAng = cosf(angle * 1.745329252E-2);
    float sinAng = sinf(angle * 1.745329252E-2);
    
    temp = cosAng * m[1] - sinAng * m[2];
    m[2] = sinAng * m[1] + cosAng * m[2];
    m[1] = temp;

    temp = cosAng * m[5] - sinAng * m[6];
    m[6] = sinAng * m[5] + cosAng * m[6];
    m[5] = temp;

    temp = cosAng * m[9] - sinAng * m[10];
    m[10] = sinAng * m[9] + cosAng * m[10];
    m[9] = temp;

    temp = cosAng * m[13] - sinAng * m[14];
    m[14] = sinAng * m[13] + cosAng * m[14];
    m[13] = temp;

    
}

// Populates matrix m with the rotation of m by an angle 'angle' in degrees
// around y axis.
// m <- Rot * m
void rotatey(float angle, float m[16]) {

    float temp;
    float cosAng = cosf(angle * 1.745329252E-2);
    float sinAng = sinf(angle * 1.745329252E-2);
    
    temp = cosAng*m[0] + sinAng*m[2];
    m[2] = -sinAng*m[0] + cosAng*m[2];
    m[0] = temp;
    
    temp = cosAng*m[4] + sinAng*m[6];
    m[6] = -sinAng*m[4] + cosAng*m[6];
    m[4] = temp;
    
    temp = cosAng*m[8] + sinAng*m[10];
    m[10] = -sinAng*m[8] + cosAng*m[10];
    m[8] = temp;
    
    temp = cosAng*m[12] + sinAng*m[14];
    m[14] = -sinAng*m[12] + cosAng*m[14];
    m[12] = temp;
    
    
}

// Populates matrix m with the rotation of m by an angle 'angle' in degrees
// around z axis.
// m <- Rot * m
void rotatez(float angle, float m[16]) {

    float temp;
    float cosAng = cosf(angle * 1.745329252E-2);
    float sinAng = sinf(angle * 1.745329252E-2);
    
    temp = cosAng*m[0] - sinAng*m[1];
    m[1] = sinAng*m[0] + cosAng*m[1];
    m[0] = temp;
    
    temp = cosAng*m[4] - sinAng*m[5];
    m[5] = sinAng*m[4] + cosAng*m[5];
    m[4] = temp;

    temp = cosAng*m[8] - sinAng*m[9];
    m[9] = sinAng*m[8] + cosAng*m[9];
    m[8] = temp;

    temp = cosAng*m[12] - sinAng*m[13];
    m[13] = sinAng*m[12] + cosAng*m[13];
    m[12] = temp;

}


void rotatev(float angle, float x, float y, float z, float m[16]) {
    
    float rotm[16];
    float cosAng = cosf(angle * 1.745329252E-2);
    float sinAng = sinf(angle * 1.745329252E-2);
    
    float norm = sqrtf(x*x + y*y + z*z);
    x /= norm; y /= norm; z /= norm;
    
    rotm[0] = cosAng + x * x * (1. - cosAng);
    rotm[1] = x * y * (1. - cosAng) + z * sinAng;
    rotm[2] = x * z * (1. - cosAng) - y * sinAng;
    rotm[3] = 0.;


    rotm[4] = x * y * (1. - cosAng) - z * sinAng;
    rotm[5] = cosAng + y * y * (1. - cosAng);
    rotm[6] = y * z * (1. - cosAng) + x * sinAng;
    rotm[7] = 0.;


    rotm[8] = z * x * (1. - cosAng) + y * sinAng;
    rotm[9] = z * y * (1. - cosAng) - x * sinAng;
    rotm[10] = cosAng + z * z * (1. - cosAng);
    rotm[11] = 0.;

    rotm[12] = 0.;
    rotm[13] = 0.;
    rotm[14] = 0.;
    rotm[15] = 1.;
    
    float tempM[16];
    memcpy(tempM, m, 16*sizeof(float));
    
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i * 4+ j] = 0.;
            for (int k = 0; k < 4; k++) {
                m[i * 4 + j] += tempM[i * 4 + k] * rotm[k * 4 + j];
            }
        }
    }
    
    

    
}


// Populates matrix m with the projection matrix multiplying m.
// m <- Proj * m
void project(float near, float far, float fieldOfView, float aspect, float m[16]) {
             
    // Some calculus before the formula.
    float angle = fieldOfView * 0.01745329252;
    float size = near * tanf(angle / 2.0);
    float left = -size, right = size, bottom = -size / aspect, top = size / aspect;
    
    float p0 = 2. * near / (right - left);
    float p1 = 2. * near / (top - bottom);
    float p2 = (right + left) / (right - left);
    float p3 = (top + bottom) / (top - bottom);
    float p4 = -(far + near) / (far - near);
    float p5 = -1.;
    float p6 = -(2. * far * near) / (far - near);
    
    
    m[0] = p0*m[0] + p2*m[2];
    m[4] = p0*m[4] + p2*m[6];
    m[8] = p0*m[8] + p2*m[10];
    m[12] = p0*m[12] + p2*m[14];
    
    m[1] = p1*m[1] + p3*m[2];
    m[5] = p1*m[5] + p3*m[6];
    m[9] = p1*m[9] + p3*m[10];
    m[13] = p1*m[13] + p3*m[14];
    
    float temp;
    temp = p4*m[2] + p6*m[3];
    m[3] = p5*m[2];
    m[2] = temp;
    
    temp = p4*m[6] + p6*m[7];
    m[7] = p5*m[6];
    m[6] = temp;
    
    temp = p4*m[10] + p6*m[11];
    m[11] = p5*m[10];
    m[10] = temp;

    temp = p4*m[14] + p6*m[15];
    m[15] = p5*m[14];
    m[14] = temp;

}


void loadIdentityMatrix(float m[16]) {
    
    m[0] = 1.;
    m[1] = m[2] = m[3] = 0.;

    m[4] = m[6] = m[7] = 0.;
    m[5] = 1.;
    
    m[8] = m[9] = m[11] = 0.;
    m[10] = 1.;

    m[12] = m[13] = m[14] = 0.;
    m[15] = 1.;
    
}

