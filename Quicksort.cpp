#include <iostream>
#include <raylib.h>
#include <vector>
#include <utility>
#include <random>
#include <chrono>
#include <thread>

const int ARRAY_SIZE = 250;

void displaySort(int highlightIndex, const std::vector<int>& arr)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        Rectangle rc;
        rc.x = i * 6;
        rc.y = 1200 - arr[i];
        rc.width = 5;
        rc.height = arr[i];
        Color color = (i == highlightIndex) ? GREEN : GRAY;

        DrawRectangle(rc.x, rc.y, rc.width, rc.height, color);
    }

    EndDrawing();

   
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int partition(std::vector<int>& arr, int start, int end)
{
    int pivot = arr[end];
    int i = start - 1;

    for (int j = start; j <= end - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
            displaySort(j, arr); 
        }
    }
    i++;
    std::swap(arr[i], arr[end]);
    displaySort(i, arr);  

    return i;
}

void quickSort(std::vector<int>& arr, int start, int end)
{
    if (end <= start) return;

    int pivot = partition(arr, start, end);

   
    quickSort(arr, start, pivot - 1);
    quickSort(arr, pivot + 1, end);
}

int main()
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 1200);

    std::vector<int> array;
    array.reserve(ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        array.push_back(dist(rng));
    }

    InitWindow(1200, 1200, "Quicksort Visualization");

   
    quickSort(array, 0, ARRAY_SIZE - 1);

  
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        displaySort(-1, array);  
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
