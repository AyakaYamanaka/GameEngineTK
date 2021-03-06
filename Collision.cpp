#include "pch.h"
#include "Collision.h"

using namespace DirectX::SimpleMath;

//∞----------------------------------------------------∞
//∞*func：球と球の当たり判定
//∞*arg：球A、球B（Sphere型）
//∞*return：当たっていたらtrue、当たっていなかったらfalse
//∞----------------------------------------------------∞
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	//球AとNの中心座標の差を計算する
	Vector3 sub = sphereB.Center - sphereA.Center;

	//三平方の定理でベクトルの長さを計算する
	//差分ベクトルの長さは、２点間の距離
	float distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	//半径の和の２乗
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	//距離が半径の和より大きければ当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}