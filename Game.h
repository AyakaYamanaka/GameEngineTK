//
// Game.h
//

#pragma once

#include "StepTimer.h"
#include "DebugCamera.h"
#include "Camera.h"
#include "FollowCamera.h"
#include "Obj3d.h"
#include "Player.h"
#include "Enemy.h"

#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>
#include <Keyboard.h>
#include <vector>


// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game
{
public:

    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:
    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();
    void Present();

    void CreateDevice();
    void CreateResources();

    void OnDeviceLost();

    // Device resources.
    HWND                                            m_window;
    int                                             m_outputWidth;
    int                                             m_outputHeight;

    D3D_FEATURE_LEVEL                               m_featureLevel;
    Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice1;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext1;

    Microsoft::WRL::ComPtr<IDXGISwapChain>          m_swapChain;
    Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain1;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	std::unique_ptr<DirectX::BasicEffect> m_effect;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	//デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;
	//エフェクトファクトリー
	//std::unique_ptr<DirectX::EffectFactory> m_factory;
	//地面モデル
	Obj3d m_obj_ground;
	//天球モデル
	Obj3d m_obj_skydome;
	//球モデル
	std::unique_ptr<DirectX::Model> m_ball_model;
	//タンクモデル
	//std::unique_ptr<DirectX::Model> m_tank_model;
	//ティーポットモデル
	std::unique_ptr<DirectX::Model> m_tea_model;
	//ティーポットのワールド行列（外側）
	DirectX::SimpleMath::Matrix m_world_tea[20];
	//ティーポットの位置座標
	float rad[20];
	//原点からのティーポットの距離
	float distance[20];
	float rotate;
	float scale;

	//キーボード
	std::unique_ptr<DirectX::Keyboard> keyboard;

	//自機の座標
	//DirectX::SimpleMath::Matrix tank_world;
	//DirectX::SimpleMath::Matrix tank_world2;
	DirectX::SimpleMath::Vector3 tank_pos;

	float tank_rotate;

	//自機の３Dオブジェクト
	Obj3d m_ObjPlayer1;
	Obj3d m_ObjPlayer2;


	std::unique_ptr<Player>m_player;
	ENEMY* m_enemy[5];

	//エフェクトファクトリー
	std::unique_ptr<DirectX::EffectFactory> m_factory;


	//球のワールド行列
	DirectX::SimpleMath::Matrix m_worldBall;
	//球のワールド行列（内側）
	DirectX::SimpleMath::Matrix m_world_ball_in[10];
	//球のワールド行列（外側）
	DirectX::SimpleMath::Matrix m_world_ball_out[10];

	//カメラ
	std::unique_ptr<FollowCamera> m_Camera;

	int m_sinAngle;

	//bool m_attack;			//攻撃フラグ
	//int m_attack_cnt;		//攻撃カウント

	//bool m_defense;			//防御フラグ
	//int m_defense_cnt;		//防御カウント

	//bool m_jump;			//ジャンプフラグ
	//int m_jump_cnt;			//ジャンプカウント
	//float jumping;			//方向ベクトルの初期化
	//DirectX::SimpleMath::Vector3 vec;

};