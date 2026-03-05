#include "Astar.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <Windows.h>


Astar::Astar()
{
}

Astar::~Astar()
{
    for (Node* node : openList)
    {
        SafeDelete(node);
    }
    openList.clear();

    for (Node* node : closedList)
    {
        SafeDelete(node);
    }
    closedList.clear();
}


std::vector<Node*> Astar::FindPath(Node* StartNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
    this->startNode = StartNode;
    this->goalNode = goalNode;

    // 예외처리
    if (!this->startNode || !this->goalNode || grid.empty() || grid[0].empty())
    {
        // 빈 경로 반환(오류)
        return {};
    }

    // 시작 노드를 열린 리스트에 추가 및 탐색 시작
    openList.emplace_back(this->startNode);

    // 대각선 비용 상수
    const float diagonalcost = 1.41421345f;

    // 비용 계산에 사용할 변수 값 설정.
    std::vector<Direction>directions =
    {
        // 하상우좌 이동 -> 콘솔이기 때문에 아래와 오른쪽으로 이동할 확률이 더 높기 때문
        {0, 1, 1.0f}, {0, -1, 1.0f},{1, 0, 1.0f},{-1, 0, 1.0f} ,
        // 대각선 이동
        {1, 1, diagonalcost}, { 1, -1, diagonalcost }, { -1, 1, diagonalcost}, {-1, -1, diagonalcost},
    };


    // 탐색 가능한 위치가 있으면 계속 진행
    while (!openList.empty())
    {
        // 현재 열린 리스트에 있는 노드 중 fCost가 가장 낮은 노드 검색
        Node* lowestNode = openList[0];
        // 가장 비용이 작은 노드 검색 ( 선형 탐색 )
        for (Node* const node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        // fCost가 가장 낮은 노드를 현재 노드로 설정
        Node* currentNode = lowestNode;

        // 현재 노드가 목표 노드인지 확인
        if (IsDestination(currentNode))
        {
            // 경로 반환 후 종료
            return ConstructPath(currentNode);
        }

        // 방문 처리를 위해 열린 리스트에서 제거
        for (auto iterator = openList.begin(); iterator != openList.end(); ++iterator)
        {
            // iterator 위치의 노드가 currentNode인지 확인
            if ((*iterator) == currentNode)
            {
                openList.erase(iterator);
                break;
            }
        }

        // 현재 노드를 방문 노드에 추가
        closedList.emplace_back(currentNode);

        // 이웃 노드 방문(탐색)
        for (const Direction& direction : directions)
        {
            // 다음에 이동할 위치(이웃 노드의 위치)
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            // 유효성 검증 (새 위치가 이동 가능한지 확인)
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }

            // 새 위치가 이동 가능한 곳인지 확인
            // 장애물(못가는 곳) = 1
            if (grid[newY][newX] == 1) // 장애물을 1로 했기때문에
            {
                continue;
            }

            // 현재 노드를 기준으로 새 gCost 계산
            float newGCost = currentNode->gCost + direction.cost;

            // 갈 수는 있지만, 이미 방문한 곳인지 확인
            if (HasVisited(newX, newY, newGCost))
            {
               /* if (neighborNode)
                    SafeDelete(neighborNode);*/ //오류 해결 불가
                continue;
            }

            // 방문을 위한 이웃 노드 생성
            neighborNode = new Node(newX, newY, currentNode);

            // 비용 계산
            neighborNode->gCost = newGCost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, this->goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            // 이웃 노드가 열린 리스트에 있는지 확인
            Node* openListNode = nullptr;
            for (Node* const node : openList)
            {
                if (*node == *neighborNode)
                {
                    // 위치만 비교해서 열린 리스트에 넣을지 여부 확인
                    openListNode = node;
                    break;
                }
            }

            // 이웃 노드가 열린 리스트에 있으면 더 좋은 비용일 때만 처리
            if (openListNode)
            {
                // 비용 확인
                if (neighborNode->gCost < openListNode->gCost || neighborNode->fCost < openListNode->fCost)
                {
                    // 부모 노드 업데이트
                    openListNode->parentNode = neighborNode->parentNode;
                    // 비용 업데이트
                    openListNode->gCost = neighborNode->gCost;
                    openListNode->hCost = neighborNode->hCost;
                    openListNode->fCost = neighborNode->fCost;
                    // 왜 openListNode->hCost = neighborNode->fCost; 일때 더 적게 검사하는지 확인해보기
                }

                // 임시 노드 메모리 정리
                SafeDelete(neighborNode);
                continue;
            }

            // 방문할 목록에 추가
            // 이 노드가 이동 가능한지 확인
            // 이동 가능한 곳 = 0
            if (grid[newY][newX] == 0)
            {
                // 시각화를 위해 사용 안하는 값 정해서 설정
                grid[newY][newX] = 9;

            }

            // 열린 리스트에 추가
            openList.emplace_back(neighborNode);

            // 잠시 대기(옵션)
            //DisplayGrid(grid);
            //DWORD delay = static_cast<DWORD>(0.05f * 1000);
            //Sleep(delay);
        }
    }


    return std::vector<Node*>();    //아무 빈 파일 넘겨주기
}

void Astar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
}

std::vector<Node*> Astar::ConstructPath(Node* goalNode)
{
    // 경로를 저장할 배열 선언
    std::vector<Node*> path;

    // 역추적하면서 path에 채우기
    Node* currentNode = goalNode;
    while (currentNode)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parentNode;
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
    return *node == *goalNode;
}

void Astar::DisplayGrid(std::vector<std::vector<int>>& grid)
{
    // 좌표 변수
    static COORD position = { 0, 0 };
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, position);

    // 색상 값
    static int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    static int green = FOREGROUND_GREEN;
    static int red = FOREGROUND_RED;

    // 맵 출력.
    for (int y = 0; y < static_cast<int>(grid.size()); ++y)
    {
        for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
        {
            // 시작 위치 = 2
            if (grid[y][x] == 2)
            {
                SetConsoleTextAttribute(handle, red);
                std::cout << "S ";
                continue;
            }

            // 목표 위치 = 3
            if (grid[y][x] == 3)
            {
                SetConsoleTextAttribute(handle, red);
                std::cout << "G ";
                continue;
            }

            // 장애물 = 1
            if (grid[y][x] == 1)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
                continue;
            }

            // 경로 = 5
            if (grid[y][x] == 5)
            {
                SetConsoleTextAttribute(handle, green);
                std::cout << "+ ";
                continue;
            }
            // 빈 공간 = 0.
            if (grid[y][x] == 0)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
                //continue;
            }

            if (grid[y][x] == 9)
            {
                SetConsoleTextAttribute(handle, red);
                std::cout << "@ ";

            }
        }
        // 개행
        std::cout << "\n";
    }

    // 위치 초기화
    position.X = 0;
    position.Y = 0;

}
