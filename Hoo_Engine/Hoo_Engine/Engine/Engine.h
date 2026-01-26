#pragma once

namespace Wanted 
{
	//Main game engine class
	class Engine
	{
		//데이터 
		struct KeyState {
			bool isKeyDown = false;
			bool wasKeyDown = false;
		};

	public :
		Engine();
		~Engine();

		void Run();
		void QuitEngine();

		//입력 확인 함수
		//이전에 입력이 X ,현재 입력이 됐으면 1번 호출
		bool GetKeyDown(int keyCode);
		//이전에 입력이 O ,현재 입력이 취소 됐으면 1번 호출
		bool GetKeyUp(int keyCode);
		//현재 눌려 있으면 호출
		bool GetKey(int keyCode);

		//새 레벨을 추가(설정)하는 함수
		void SetNewLevel(class Level* newLevel);

	private :
		//입력 처리 함수
		void ProcessInput();
		//게임 플레이 시작 함수
		void BeginPlay();

		void Tick(float deltaTime);
		void Draw();

	private : 
		bool isQuit = false;
		KeyState keyStates[255] = {};


		//메인 레벨
		class Level* mainLevel = nullptr;
	};


}
