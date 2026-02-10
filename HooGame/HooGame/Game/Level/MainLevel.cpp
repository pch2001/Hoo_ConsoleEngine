#include "MainLevel.h"
#include "Core/Input.h"
#include "Util/Util.h"
#include "Game/Game.h"
#include "Render/Renderer.h"

#include <iostream>
#include <fstream>
#include <vector>


MainLevel::MainLevel()
{
	items.emplace_back(new MenuItem("Start Game", []() { Game::Get().ToggleMenu(); }));

	items.emplace_back(new MenuItem("Quit Game", []() { Game::Get().QuitEngine(); }));
	LoadMap("Map.txt");
}

MainLevel::~MainLevel()
{
	for (MenuItem*& item : items)
	{
		delete item;
		item = nullptr;
	}
	items.clear();
}

void MainLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	static int length = static_cast<int>(items.size());
	if (Input::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1 + length) % length;
	}

	if (Input::Get().GetKeyDown(VK_RETURN))
	{
		items[currentIndex]->onselected();
	}

	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		Game::Get().ToggleMenu();
		currentIndex = 0;
	}


}

void MainLevel::Draw()
{

	int cameraX = Renderer::Get().GetCameraPosition().x;

	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;

		

		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 2+cameraX, Engine::Get().GetHeight() / 3 + ix*2),textColor);

		Util::SetConsoleTextColor(textColor);
	}

	for (const auto& item : mapData) {
        char temp[2] = { item.character, '\0' };
        Renderer::Get().Submit(temp, item.pos, Color::White);
    }

}

void MainLevel::LoadMap(const char* filename)
{
	// 파일 로드.
	// 최종 파일 경로 만들기. ("../Assets/filename")
	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	// 예외 처리.
	if (!file)
	{
		// 표준 오류 콘솔 활용.
		std::cerr << "Failed to open map file.\n";

		// 디버그 모드에서 중단점으로 중단해주는 기능.
		__debugbreak();
	}

	// 맵 읽기.
	// 맵 크기 파악: File Position 포인터를 파일의 끝으로 이동.
	fseek(file, 0, SEEK_END);

	// 이 위치 읽기.
	size_t fileSize = ftell(file);

	// File Position 처음으로 되돌리기.
	rewind(file);

	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];

	// 데이터 읽기.
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱-Parcing)해서 출력.

	// --- 데이터를 분석해서 Renderer에 등록하는 로직 추가 ---
	int x = 0;
	int y = 5; // 메뉴 위쪽에 출력하고 싶다면 적절한 y값 설정

	for (size_t i = 0; i < readSize; ++i) {
		// 1. 줄바꿈 처리 (\n)
		if (data[i] == '\n') {
			y++;
			x = 0;
			continue;
		}

		// 2. 무시할 문자들 (\r, \0 등)
		if (data[i] == '\r' || data[i] == '\0') {
			continue;
		}

		// 3. 공백 포함 모든 문자를 저장 (공백을 무시하면 맵 모양이 망가집니다)
		// 맵 파일의 모양을 그대로 유지하려면 공백(' ')도 좌표를 차지해야 합니다.
		if (data[i] != ' ') {
			mapData.push_back({ data[i], Vector2((float)x + 10, (float)y) });
		}

		// 4. 문자가 공백이든 뭐든 x 좌표는 무조건 증가시켜야 맵 형태가 유지됩니다.
		x++;
	}

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}