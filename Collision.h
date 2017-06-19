#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

//��
class Sphere
{
public:
	DirectX::SimpleMath::Vector3 Center;	//���S���W
	float Radius;		//���a

	//�R���X�g���N�^
	Sphere()
	{
		//���a�P���[�g��
		Radius = 1.0f;
	}
};

//����
class Segment
{
public:
	DirectX::SimpleMath::Vector3 Start;		//�n�_���W
	DirectX::SimpleMath::Vector3 End;		//�I�_���W
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);