#include "Astar.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <Windows.h>

#include "Render/Renderer.h"
#include "Math/Vector2.h"
#include "Util/Util.h"

Astar::Astar()
{
}

Astar::~Astar()
{
   /* for (Node* node : openList)
    {
        SafeDelete(node);
    }
    openList.clear();

    for (Node* node : closedList)
    {
        SafeDelete(node);
    }
    closedList.clear();*/
    
    /*for (Node* node : nodeRegistry)
        SafeDelete(node);*/

}


std::vector<Node*> Astar::FindPath(Node* StartNode, Node* goalNode, std::vector<std::vector<int>>& grid, bool pathLine)
{
    if (StartNode == nullptr || goalNode == nullptr) 
        return {};
    
    if (nodeGrid.size() != grid.size()) 
        nodeGrid.resize(grid.size());

    for (int y = 0; y < (int)grid.size(); ++y) {
        if (nodeGrid[y].size() != grid[0].size()) {
            nodeGrid[y].resize(grid[0].size());
        }

        // 2. 루프 내부에서 직접 초기화 (Reset 호출)
        for (int x = 0; x < (int)grid[0].size(); ++x) {
            nodeGrid[y][x].Reset(x, y);
        }
    }

    openList.clear();

    if (!IsInRange(StartNode->position.x, StartNode->position.y, grid) || !IsInRange(goalNode->position.x, goalNode->position.y, grid))
    {
        return {}; // 범위를 벗어나면 즉시 종료
    }

    // 시작점 설정 (new가 아니라 nodeGrid의 주소를 사용)
    Node* startNode = &nodeGrid[StartNode->position.y][StartNode->position.x];
    Node* targetNode = &nodeGrid[goalNode->position.y][goalNode->position.x];
    this->goalNode = targetNode;

    startNode->gCost = 0;
    startNode->hCost = CalculateHeuristic(startNode, targetNode);
    startNode->fCost = startNode->gCost + startNode->hCost;
    startNode->isOpen = true;



    openList.emplace_back(startNode);
    const float diagonalcost = 1.41421345f;

    // 비용 계산에 사용할 변수 값 설정.
    std::vector<Direction>directions =
    {
        // 하상우좌 이동 -> 콘솔이기 때문에 아래와 오른쪽으로 이동할 확률이 더 높기 때문
        {0, 1, 1.0f}, {0, -1, 1.0f},{1, 0, 1.0f},{-1, 0, 1.0f} ,
        // 대각선 이동
        {1, 1, diagonalcost}, { 1, -1, diagonalcost }, { -1, 1, diagonalcost}, {-1, -1, diagonalcost},
    };

    while (!openList.empty()) {
        auto it = std::min_element(openList.begin(), openList.end(), [](Node* a, Node* b) {
            return a->fCost < b->fCost;
            });
        Node* currentNode = *it;
        openList.erase(it);
        currentNode->isClosed = true;

        if (IsDestination(currentNode)) {
            finalPath = ConstructPath(currentNode);
            if (pathLine) 
                DisplayGridWithPath(startNode, finalPath); // 매개변수 이름 확인 (startNode vs StartNode)
            return finalPath;
        }

        // openList에서 제거 및 closedList 추가
        // (이때도 SafeDelete 절대 금지! 객체는 nodeGrid에 살아있어야 함)

        for (const auto& dir : directions) {
            int nX = currentNode->position.x + dir.x;
            int nY = currentNode->position.y + dir.y;

            if (!IsInRange(nX, nY, grid) || grid[nY][nX] == 1) continue;

            // [변경점] new 대신 이미 존재하는 노드의 주소를 가져옴            
            Node* neighborNode = &nodeGrid[nY][nX];

            // 이미 닫힌 리스트에 있다면 스킵
            if (neighborNode->isClosed) continue;

            float newGCost = currentNode->gCost + dir.cost;

            // 새로운 경로가 더 짧거나, 아직 열린 리스트에 없다면
            if (newGCost < neighborNode->gCost) {
                neighborNode->parentNode = currentNode;
                neighborNode->gCost = newGCost;
                neighborNode->hCost = CalculateHeuristic(neighborNode, targetNode);
                neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

                // 아직 열린 리스트에 없다면 추가
                if (!neighborNode->isOpen) {
                    neighborNode->isOpen = true;
                    //openList.emplace_back(neighborNode);
                    openList.push_back(neighborNode);
                }
            }
        }
    }
    return {};
}








void Astar::DisplayGridWithPath(Node* startNode, const std::vector<Node*>& path)
{
    Position currentPos = startNode->position;
    Position prevPos = startNode->position;

    const char* arrow = "*";
    if (!path.empty())
    {
        for (Node* open : path)
        {
           currentPos = open->position;

            int dx = currentPos.x - prevPos.x;
            int dy = currentPos.y - prevPos.y;

            if (dx < 0 && dy < 0) arrow = "\\";
            else if (dx > 0 && dy < 0) arrow = "/";
            else if (dx > 0 && dy > 0) arrow = "\\";
            else if (dx < 0 && dy > 0) arrow = "/";

            else if (dx > 0 && dy == 0) arrow = ">";
            else if (dx < 0 && dy == 0) arrow = "<";
            else if (dx == 0 && dy > 0) arrow = "V";
            else if (dx == 0 && dy < 0) arrow = "^";

            int bgYellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
            Wanted::Renderer::Get().Submit(arrow, Wanted::Vector2(currentPos.x, currentPos.y), Wanted::Color::YELLOW, 7);   // , bgYellow, true);
            prevPos = currentPos;
        } 
    }
}

std::vector<Node*> Astar::ConstructPath(Node* goalNode)
{
    // 경로를 저장할 배열 선언
    std::vector<Node*> path;

    // 역추적하면서 path에 채우기
    Node* currentNode = goalNode;
    int maxNodes = 5000;
    int safetyCounter = 0;
    while (currentNode!= nullptr && safetyCounter < maxNodes)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parentNode;
        safetyCounter++;
    }

    // 이렇게 얻은 결과는 순서가 거꾸로.
    // 그래서 거꾸로 다시 정렬이 필요함.
    std::reverse(path.begin(), path.end());

    return path;
}

float Astar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
    Position diff = *currentNode - *goalNode;
    return static_cast<float>(std::sqrt(diff.x * diff.x + diff.y * diff.y));
}

bool Astar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    // 예외 처리
    if (grid.empty() || grid[0].empty())
        return false;
    // x, y 범위가 벗어났는지 확인
    if (x < 0 || x >= static_cast<int>(grid[0].size())|| y < 0 || y >= static_cast<int>(grid.size()))
    {
        return false;

    }

    // 벗어나지 않았으면 true 반환.
    return true;
}

bool Astar::HasVisited(int x, int y, float gCost)
{
    for (const Node* const node : openList)
    {
        if (node->position.x == x && node->position.y == y && gCost >= node->gCost)
        {
            return true;
        }
    }

    // 닫힌 리스트에 이미 같은 위치가 있고,
    // 비용이 더 낮으면 방문했다고 판단
    for (const Node* const node : closedList)
    {
        if (node->position.x == x && node->position.y == y /*&& gCost >= node->gCost*/)
        {
            return true;
        }
    }

    return false;
}

bool Astar::IsDestination(const Node* const node)
{
    //return *node == *goalNode;
    return (node->position.x == goalNode->position.x && node->position.y == goalNode->position.y);
}

//void Astar::DisplayGrid(std::vector<std::vector<int>>& grid)
//{
//    // 좌표 변수
//    static COORD position = { 0, 0 };
//    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleCursorPosition(handle, position);
//
//    // 색상 값
//    static int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
//    static int green = FOREGROUND_GREEN;
//    static int red = FOREGROUND_RED;
//
//    // 맵 출력.
//    for (int y = 0; y < static_cast<int>(grid.size()); ++y)
//    {
//        for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
//        {
//            // 시작 위치 = 2
//            if (grid[y][x] == 2)
//            {
//                SetConsoleTextAttribute(handle, red);
//                std::cout << "S ";
//                continue;
//            }
//
//            // 목표 위치 = 3
//            if (grid[y][x] == 3)
//            {
//                SetConsoleTextAttribute(handle, red);
//                std::cout << "G ";
//                continue;
//            }
//
//            // 장애물 = 1
//            if (grid[y][x] == 1)
//            {
//                SetConsoleTextAttribute(handle, white);
//                std::cout << "1 ";
//                continue;
//            }
//
//            // 경로 = 5
//            if (grid[y][x] == 5)
//            {
//                SetConsoleTextAttribute(handle, green);
//                std::cout << "+ ";
//                continue;
//            }
//            // 빈 공간 = 0.
//            if (grid[y][x] == 0)
//            {
//                SetConsoleTextAttribute(handle, white);
//                std::cout << "0 ";
//                //continue;
//            }
//
//            if (grid[y][x] == 9)
//            {
//                SetConsoleTextAttribute(handle, red);
//                std::cout << "@ ";
//
//            }
//        }
//        // 개행
//        std::cout << "\n";
//    }
//
//    // 위치 초기화
//    position.X = 0;
//    position.Y = 0;
//
//}

