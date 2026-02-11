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
	//LoadMap("Stage2.txt");
	LoadMap("Map.txt");
	LoadLine();
}

MainLevel::~MainLevel()
{

}

void MainLevel::Draw()
{

	int cameraX = Renderer::Get().GetCameraPosition().x;
	cameraX = 0;
	for (int ix = 0; ix < static_cast<int>(items.size()); ++ix)
	{
		Color textColor = (ix == currentIndex) ? selectedColor : unselectedColor;


		Renderer::Get().Submit(items[ix]->text, Vector2(Engine::Get().GetWidth() / 2+cameraX - strlen(items[ix]->text)
			, Engine::Get().GetHeight() / 2 + ix*4),textColor);

		//Util::SetConsoleTextColor(textColor);
	}

	for (const auto& item : mapData) {
		//char temp[2] = {item.character, '\0'};
		Renderer::Get().Submit(item.character.c_str(), item.pos, Color::Red);
	}
	for (const auto& item : mapData2) {
		Renderer::Get().Submit(item.character, item.pos, Color::Red);
	}
}

void MainLevel::LoadMap(const char* filename)
{

	char path[2048] = {};
	sprintf_s(path, 2048, "../Assets/%s", filename);

	// 파일 열기.
	FILE* file = nullptr;
	fopen_s(&file, path, "rt");

	if (!file){	__debugbreak();}

	// 맵 읽기.
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);


	// 파일에서 데이터를 읽어올 버퍼 생성.
	char* data = new char[fileSize + 1];
	size_t readSize = fread(data, sizeof(char), fileSize, file);

	// 읽어온 문자열을 분석(파싱-Parcing)해서 출력.
	int x = 0; //Engine::Get().GetWidth() / 2;
	int y = 0;//Engine::Get().GetHeight()/2;
	for (size_t i = 0; i < readSize; ++i) {

		if (data[i] == '\r') {
			continue;
		}

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

		if (data[i] != ' ') {
			mapData.push_back({std::string(1, data[i]), Vector2((float)x+ Engine::Get().GetWidth() / 5 , (float)y + 5.f) });
		}
		x++;
	}

	// 사용한 버퍼 해제.
	delete[] data;

	// 파일이 정상적으로 열렸으면 닫기.
	fclose(file);
}

void MainLevel::LoadLine()
{
	const int width = Engine::Get().GetWidth();
	const int height = Engine::Get().GetHeight();

	// ┌───────────────┐ (top)
	for (int x = 0; x < width; ++x)
	{
		mapData2.push_back({ "_", Vector2((float)x, 0.f) });
	}

	// │               │ (middle)
	for (int y = 1; y < height - 1; ++y)
	{
		mapData2.push_back({ "|", Vector2(0.f, (float)y) });
		mapData2.push_back({ "|", Vector2((float)(width - 1), (float)y) });
	}

	// └───────────────┘ (bottom)
	for (int x = 0; x < width; ++x)
	{
		mapData2.push_back({ "-", Vector2((float)x, (float)(height - 1)) });
	}
}

