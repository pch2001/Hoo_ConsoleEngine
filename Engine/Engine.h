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
		// 엔진 종료 플래그
		void QuitEngine();

		//입력 확인 함수
		//이전에 입력이 X ,현재 입력이 됐으면 1번 호출
		bool GetKeyDown(int keyCode);
		//이전에 입력이 O ,현재 입력이 취소 됐으면 1번 호출
		bool GetKeyUp(int keyCode);
		//현재 눌려 있으면 호출
		bool GetKey(int keyCode);

	private:
		void ProcessInput();
		void Tick(float deltaTime);
		void Draw();
	private :
		bool isQuit = false;

		//키 상태 저장용 배열
		KeyState keyStates[255] = {};

	};

}



