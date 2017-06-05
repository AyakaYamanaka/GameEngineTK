//∞----------------------------------------------------∞
//∞*ファイル名：Obj3d.cpp								∞
//∞*内容　　　：3Dオブジェクトのクラス					∞
//∞*制作者　　：Ayaka Yamanaka							∞
//∞*制作日時　：2017.05.22								∞
//∞----------------------------------------------------∞
#include "Obj3d.h"
//#include <d3d11_1.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

//デバイス
Microsoft::WRL::ComPtr<ID3D11Device>           Obj3d::m_d3dDevice;
//デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;
//カメラ
Camera* Obj3d::m_Camera;
//汎用描画ステート
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
//エフェクトファクトリー
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	m_states=std::make_unique<CommonStates>(m_d3dDevice.Get());

	//エフェクトファクトリー生成
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	//テクスチャの読み込みパス指定
	m_factory->SetDirectory(L"Resources");

}

Obj3d::Obj3d()
{
	//スケールは１倍がデフォルト
	m_scalemat = SimpleMath::Vector3(1, 1, 1);

	m_perent = nullptr;

}

void Obj3d::LoadModel(const wchar_t * filename)
{
	//モデルの読み込み
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(),filename, *m_factory);

}

void Obj3d::Update()
{
	//主に行列の計算
	SimpleMath::Matrix scalemat = SimpleMath::Matrix::CreateScale(m_scalemat);
	SimpleMath::Matrix rotmatZ = SimpleMath::Matrix::CreateRotationZ(m_rotmat.z);
	SimpleMath::Matrix rotmatX = SimpleMath::Matrix::CreateRotationX(m_rotmat.x);
	SimpleMath::Matrix rotmatY = SimpleMath::Matrix::CreateRotationY(m_rotmat.y);

	SimpleMath::Matrix rotmat = rotmatZ * rotmatX * rotmatY;
	SimpleMath::Matrix transmat = SimpleMath::Matrix::CreateTranslation(m_transmat);
	
	//ワールド行列を合成
	m_world = scalemat*rotmat*transmat;

	//親の行列をかける
	if (m_perent)
	{
		m_world *= m_perent->m_world;
	}

}

void Obj3d::Draw()
{
	assert(m_Camera);
	//モデルの描画
	if (m_model)
	{
		m_model->Draw(m_d3dContext.Get(),
			*m_states,
			m_world,
			m_Camera->GetViewMatrix(),
			m_Camera->GetProjectionMatrix());
	}
}

void Obj3d::Set_scale(DirectX::SimpleMath::Vector3 scalemat)
{
	m_scalemat = scalemat;
}

void Obj3d::Set_rotate(DirectX::SimpleMath::Vector3 rotmat)
{
	m_rotmat = rotmat;
}

void Obj3d::Set_trans(DirectX::SimpleMath::Vector3 transmat)
{
	m_transmat = transmat;
}

void Obj3d::Set_perant(Obj3d * perant)
{
	m_perent = perant;
}

DirectX::SimpleMath::Vector3 Obj3d::Get_scale()
{
	return m_scalemat;
}

DirectX::SimpleMath::Vector3 Obj3d::Get_rotate()
{
	return m_rotmat;
}

DirectX::SimpleMath::Vector3 Obj3d::Get_transmat()
{
	return m_transmat;
}

Obj3d * Obj3d::Get_perant()
{
	return m_perent;
}

DirectX::SimpleMath::Matrix Obj3d::Get_world()
{
	return m_world;
}


