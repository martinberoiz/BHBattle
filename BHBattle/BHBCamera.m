//
//  BHBCamera.m
//  BHBattle
//
//  Created by Martin Beroiz on 4/18/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

#import "BHBCamera.h"
#include <math.h>
#include <string.h>


void normalize(float v[3]);
void crossProd(float v1[3],float v2[3], float v3[3]);


void normalize(float v[3]) {
    float norm = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    if (norm != 0.) {
        v[0] /= norm;
        v[1] /= norm;
        v[2] /= norm;
    }
    
}

void crossProd(float v1[3],float v2[3], float v3[3]) {
    
    v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
    v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
    v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
    
}


@implementation BHBCamera 


- (id) init {
    if ((self = [super init])) {
        //Initialize camera with defaults in the eye-coord system.
        position[0] = 0.; position[1] = 0.; position[2] = 0.;
        looksAt[0] = 0.; looksAt[1] = 0.; looksAt[2] = -1.;
        upVector[0] = 0.; upVector[1] = 1.; upVector[2] = 0.;
    }
    return self;
}


- (float *)cameraPosition {
    return position;
}

- (void)setCameraPositionAtX:(float)x Y:(float)y Z:(float)z {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

- (void)lookAtX:(float)x Y:(float)y Z:(float)z {
    looksAt[0] = x;
    looksAt[1] = y;
    looksAt[2] = z;    
}

- (void)setUpVectorAtX:(float)x Y:(float)y Z:(float)z {
    upVector[0] = x;
    upVector[1] = y;
    upVector[2] = z;
}


- (void)translateCameraByX:(float)x Y:(float)y Z:(float)z {
    position[0] += x;
    position[1] += y;
    position[2] += z;
}


- (void)loadCameraMatrixInArray: (float *)viewMatrix {
    
    //this contains i', j', k' in world coordinates
    float prime[3][3];
    
    prime[2][0] = position[0] - looksAt[0];
    prime[2][1] = position[1] - looksAt[1];
    prime[2][2] = position[2] - looksAt[2];
    crossProd(upVector, prime[2], prime[0]);
    crossProd(prime[2], prime[0], prime[1]);
    normalize(prime[0]);
    normalize(prime[1]);
    normalize(prime[2]);
    
    //Create the rotation matrix - This can be optimized using properties
    //of rotation matrices, maybe.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            viewMatrix[i*4 + j] = prime[j][i];
        }
        viewMatrix[i*4 + 3] = 0.;
    }
    for (int i = 12; i < 15; i++) viewMatrix[i] = 0.;
    viewMatrix[15] = 1.;
    
    
    //Fast multiplication of transM * rotM.
    viewMatrix[12] = -position[0] * viewMatrix[0] \
    - position[1] * viewMatrix[4] \
    - position[2] * viewMatrix[8];
    
    viewMatrix[13] = -position[0] * viewMatrix[1] \
    - position[1] * viewMatrix[5] \
    - position[2] * viewMatrix[9];
    
    viewMatrix[14] = -position[0] * viewMatrix[2] \
    - position[1] * viewMatrix[6] \
    - position[2] * viewMatrix[10];
    
    
    /*//The fast multiplication of trasnM * rotM rolled in a loop.
     for (int i = 0; i < 3; i++) {
     for (int k = 0; k < 3; k++) {
     cameraMatrix[12 + i] += -position[k] * cameraMatrix[k * 4 + i];
     }
     }*/
    
}


- (void)attachCameraToModel: (float *)modelMatrix {
    
    float viewMatrix[16];
    float modelViewMatrix[16];
    [self loadCameraMatrixInArray:viewMatrix];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            modelViewMatrix[i * 4 + j] = 0.;
            for (int k = 0; k < 4; k++) {
                modelViewMatrix[i * 4 + j] += modelMatrix[i * 4 + k] * viewMatrix[k * 4 + j];
            }
        }
    }
    memcpy(modelMatrix, modelViewMatrix, 16*sizeof(*modelViewMatrix));
}



@end


