//
//  BHBCamera.m
//  BHBattle
//
//  Created by Martin Beroiz on 4/18/12.
//  Copyright (c) 2012 UTB. All rights reserved.
//

#import "BHBCamera.h"
#include "matrixMath.h"
#include <math.h>


void normalize(float v[3]);
void crossProd(float v1[3],float v2[3], float v3[3]);
float angle(float v1[3], float v2[3]);


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

float angle(float v1[3], float v2[3]) {
    float norm1 = sqrtf(v1[0] * v1[0] + v1[1] * v1[1] + v1[2] * v1[2]);
    float norm2 = sqrtf(v2[0] * v2[0] + v2[1] * v2[1] + v2[2] * v2[2]);
    
    if (norm1 == 0. || norm2 == 0.) {
        return 0.;
    } else {
        return acosf((v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2])/(norm1 * norm2));
    }

}


@implementation BHBCamera 

@synthesize fieldOfView;


- (id) init {
    if ((self = [super init])) {
        //loadIdentityMatrix(cameraMatrix);
        fieldOfView = 45.;
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

- (void)lookAt:(float)x Y:(float)y Z:(float)z {
    looksAt[0] = x;
    looksAt[1] = y;
    looksAt[2] = z;    
}

- (void)setUpVectorX:(float)x Y:(float)y Z:(float)z {
    upVector[0] = x;
    upVector[1] = y;
    upVector[2] = z;
}

- (void)translateCameraByX:(float)x Y:(float)y Z:(float)z {
    position[0] += x;
    position[1] += y;
    position[2] += z;
}


- (void)loadCameraMatrixInArray: (float *)cameraMatrix {
    
    float pointingDirection[3];
    pointingDirection[0] = looksAt[0] - position[0];
    pointingDirection[1] = looksAt[1] - position[1];
    pointingDirection[2] = looksAt[2] - position[2];
        
    
    //This will set upVector to be perpendicular to pointingDirection
    //in case it's not already. And it also creates the 'left' versor.
    float leftVersor[3];
    crossProd(upVector, pointingDirection, leftVersor);
    crossProd(pointingDirection, leftVersor, upVector);
    
    loadIdentityMatrix(cameraMatrix);

    //Euler angles in the x convention (Goldstein's)
    float phi,theta,psi;
    
    //lineN is the line of nodes versor
    float lineN[3];
    lineN[0] = fabs(upVector[2]);
    lineN[1] = 0.;
    lineN[2] = -fabs(upVector[0]);

    
    float zv[] = {0.,0.,1.};
    float yv[] = {0.,1.,0.};
    float zpv[3];
    zpv[0] = -pointingDirection[0];
    zpv[1] = -pointingDirection[1];
    zpv[2] = -pointingDirection[2];
    
    phi = angle(lineN, zv) * 57.295779513;
    if (lineN[0] < 0.) phi = -phi;

    theta = angle(yv, upVector) * 57.295779513;
    if (upVector[2] < 0.) theta = -theta;
    
    psi = -angle(lineN, zpv) * 57.295779513;
    if (lineN[0] < 0.) psi = -psi;
    
    rotatey(-phi, cameraMatrix);
    rotatez(-theta, cameraMatrix);
    rotatey(-psi, cameraMatrix);

    translate(-position[0], -position[1], -position[2], cameraMatrix);


}


- (void)attachCameraToModel: (float *)modelMatrix {
    
    float cameraMatrix[16];
    float temp[16];
    [self loadCameraMatrixInArray:cameraMatrix];
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i * 4 + j] = 0.;
            for (int k = 0; k < 4; k++) {
                temp[i * 4 + j] += modelMatrix[i * 4 + k] * cameraMatrix[k * 4 + j];
            }
        }
    }
    memcpy(modelMatrix, temp, 16*sizeof(*temp));
}

/*- (void)rotateCameraBy:(float)degAngle aroundVector:(float *)vector {
    rotatev(degAngle, vector[0], vector[1], vector[2], cameraMatrix);
}*/




@end


