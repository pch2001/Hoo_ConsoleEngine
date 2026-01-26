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

	private :
		//입력 처리 함수
		void ProcessInput();
		//게임 플레이 시작 함수
		void BeginPlay();

		void Tick(float deltaTime);
	private : 
		bool isQuit = false;
		KeyState keyStates[255] = {};



	};


}
