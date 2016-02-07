﻿//*********************************************
// 演算の拡張関数
// Last Update : 2013.11.29
// Yuta Komatsu
//*********************************************
#pragma once

#include <DirectXMath.h>

namespace KMT {

	class Vector3;
	class Quaternion;

	extern const Vector3 AXIS_X;
	extern const Vector3 AXIS_Y;
	extern const Vector3 AXIS_Z;

	// X軸周りの回転を表すクォータニオンを取得
	Quaternion RotationX(float angle);
	// Y軸周りの回転を表すクォータニオンを取得
	Quaternion RotationY(float angle);
	// Z軸周りの回転を表すクォータニオンを取得
	Quaternion RotationZ(float angle);

	// 線形補間
	// 結果のfloat値を生成
	// f=0のときa、f=1のときbとなる
	inline float Interpolate(float a, float b, float f)
	{
		return a * (1 - f) + b * f;
	}

	// 線形補間
	// 結果のCVector3を生成
	// 上記のfloat線形補間関数を使用
	Vector3 Interpolate(const Vector3 &v1, const Vector3 &v2, float f);

	// 球面線形補間
	// f = 0のときv1, f = 1のときv2
	// 機能は該当するコンストラクタと同等
	Quaternion Interpolate(const Quaternion& q1, const Quaternion& q2, float f);

	// クォータ二オンの差分
	// pQ1 : 
	// pQ2 : 
	// return : 演算結果のクォータニオン
	// tips1 : pQ1 -> pQ2 への差分
	// tips2 : この関数の戻り値はpOutの戻り値と同じである。別の関数の引数としても扱える。
	Quaternion* QuaternionDelta(Quaternion *pOut, const Quaternion *pQ1, const Quaternion *pQ2);

	// 点と平面の距離を出す
	// vPt : 点の座標
	// vPNml : 平面の法線
	// vPPt : 平面上の座標
	// return : 結果の距離
	float DistancePointPlane(D3DXVECTOR3 vPt, D3DXVECTOR3 vPNml, D3DXVECTOR3 vPPt);

}