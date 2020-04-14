//
//  LucusQuaternion.cpp
//  LucusGame
//
//  Created by Alexander Kardakov on 01/04/2020.
//

#include "LucusQuaternion.h"
#include "LucusVector.h"
#include "LucusRotator.h"
#include "LucusMatrix.h"
#include "LucusMath.h"

using namespace LucusEngine;

const FQuaternion FQuaternion::Identity { 1.0f, 0.0f, 0.0f, 0.0f };

FQuaternion::FQuaternion(const float array[])
{
	x = array[0]; y = array[1]; z = array[2]; w = array[3];
}

FQuaternion::FQuaternion(const FVector3& axis, float angleRad) : w(1.0f), x(0.0f), y(0.0f), z(0.0f)
{
    RotateAroundAxis(axis, angleRad);
}

float FQuaternion::operator[] (u32 i) const
{
	return *(&w+i);
}
float& FQuaternion::operator[] (u32 i)
{
	return *(&w+i);
}

void FQuaternion::ToRotateMatrix(FMatrix4x4& mtx) const
{
    // SSE optimized version
    float x2 = x + x;
    float y2 = y + y;
    float z2 = z + z;
    float xx2 = x * x2;
    float yy2 = y * y2;
    float zz2 = z * z2;
    float wx2 = w * x2;
    float wy2 = w * y2;
    float wz2 = w * z2;
    float yx2 = y * x2;
    float zx2 = z * x2;
    float zy2 = z * y2;
    
    mtx.m[0][0] = 1.0f - (yy2 + zz2);
    mtx.m[0][1] = yx2 - wz2;
    mtx.m[0][2] = zx2 + wy2;
    
    mtx.m[1][0] = yx2 + wz2;
    mtx.m[1][1] = 1.0f - (xx2 + zz2);
    mtx.m[1][2] = zy2 - wx2;
    
    mtx.m[2][0] = zx2 - wy2;
    mtx.m[2][1] = zy2 + wx2;
    mtx.m[2][2] = 1.0f - (xx2 + yy2);
}

void FQuaternion::RotateAroundAxis(const FVector3& axis, float angleRad)
{
    // axis is unit length (normalized)
    // The Quaternion representing the rotation is
    // q = cos(a/2) + sin(a/2) * (x*i + y*j + z*k)
    
    float halfAngleRad (angleRad * 0.5f);
    w = FMath::Cos(halfAngleRad);
    float S = FMath::Sin(halfAngleRad);
    x = axis.x * S;
    y = axis.y * S;
    z = axis.z * S;
}

void FQuaternion::Set(const FRotator& rot)
{
	Set(rot.roll, rot.pitch, rot.yaw);
}

void FQuaternion::Set(float roll, float pitch, float yaw)
{
	float rollHalfRad = roll * D2R * 0.5f;
	float pitchHalfRad = pitch * D2R * 0.5f;
	float yawHalfRad = yaw * D2R * 0.5f;

	// float cx = FMath::Cos(rollHalfRad); //cr
	// float cy = FMath::Cos(pitchHalfRad); //cp
	// float cz = FMath::Cos(yawHalfRad); //cy
	// float sx = FMath::Sin(rollHalfRad); //sr
	// float sy = FMath::Sin(pitchHalfRad); //sp
	// float sz = FMath::Sin(yawHalfRad); //sy
    
    // This for z-yaw
//	w =  cr * cp * cy + sr * sp * sy;
//	x =  cr * sp * sy - sr * cp * cy;
//	y = -cr * sp * cy - sr * cp * sy;
//	z =  cr * cp * sy - sr * sp * cy;
    
    // This where z is pitch
//    float cycz = cy * cz;
//    float sysz = sy * sz;
//    float sycz = sy * cz;
//    float cysz = cy * sz;
//    w    = ( cx * cycz ) - ( sx * sysz );
//    x    = ( sx * sycz ) + ( cx * cysz );
//    y    = ( sx * cycz ) + ( cx * sysz );
//    z    = ( cx * sycz ) - ( sx * cysz );
    
    // X+ right Y+ top Z+ forward
    float cr = FMath::Cos(rollHalfRad); // roll or bank
    float cp = FMath::Cos(pitchHalfRad); // pitch or attitude
    float cy = FMath::Cos(yawHalfRad); // yaw or heading
    float sr = FMath::Sin(rollHalfRad);
    float sp = FMath::Sin(pitchHalfRad);
    float sy = FMath::Sin(yawHalfRad);

    w = cy * cp * cr - sy * sp * sr;
    x = sy * sp * cr + cy * cp * sr;
    y = sy * cp * cr + cy * sp * sr;
    z = cy * sp * cr - sy * cp * sr;
}
