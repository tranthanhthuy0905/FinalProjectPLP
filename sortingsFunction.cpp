#include "raylib.h"
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#define NORMAL 0
#define COMPARING 1
#define SORTED 2
#define SELECTED 3
#define MINIMUM 4
#define PIVOT 5
#define LEFT 6
#define RIGHT 7

// Size of the array
int NumberOfPillers = 50;

// Insertion Sort:
void Insertion_Sort(std::vector<std::pair<int, int> > &arr)
{

    arr[0].second = SORTED;
    for (int i = 1; i < arr.size(); i++)
    {
        // Drawing the bar
        BeginDrawing();

        // If choosing the next value to the ith element
        arr[i].second = SELECTED;
        int key = arr[i].first;

        // Sorting the arr
        int tmp = 0;
        int j = i - 1;
        while (arr[j].first > key && j >= 0)
        {

            // Swap the two pillers
            std::swap(arr[j + 1].first, arr[j].first);

            // Make the comparing piller
            arr[j].second = COMPARING;

            BeginDrawing();

            // Draw full array here
            // DrawArray(arr);

            // Make the Selected piller sorted again (it already was)
            arr[j].second = SORTED;

            EndDrawing();

            j--;
            tmp++;
        }

        if (tmp == 0)
        {
            BeginDrawing();

            // DrawArray(arr);

            EndDrawing();
        }

        // DE-Select the unnecesserry pillers
        // for (int k = 0; k < NumberOfPillers; k++)
        //     if (arr[k].second == SELECTED)
        //         arr[k].second = NORMAL;

        // // Color the sorted pillers
        // for (int k = i-1; k >= 0; k--)
        //     arr[k].second = SORTED;

        // arr[j+1].first = key;
        // arr[j+1].second = SORTED;

        EndDrawing();
    }

    // arr[NumberOfPillers-1].second = SORTED;
}

// Bubble Sort:
void Bubble_Sort(std::vector<std::pair<int, int> > &arr)
{

    int endingPoint = NumberOfPillers;

    bool swapped;
    do
    {
        swapped = false;

        for (int i = 0; i < endingPoint - 1; i++)
        {

            arr[i].second = SELECTED;

            if (arr[i] > arr[i + 1])
            {
                // arr[i+1].second = SELECTED;

                std::swap(arr[i], arr[i + 1]);

                swapped = true;
            }

            BeginDrawing();

            for (int k = NumberOfPillers - 1; k >= endingPoint; k--)
                arr[k].second = SORTED;

            // DrawArray(arr);

            for (int k = i; k >= 0; k--)
                arr[k].second = NORMAL;

            EndDrawing();
        }

        endingPoint--;

    } while (swapped);

    for (int k = NumberOfPillers - 1; k >= 0; k--)
        arr[k].second = SORTED;
}

// Merge Sort:
// TODO;
void Merge_Sort(std::vector<std::pair<int, int> > &arr)
{
    MergeSort_Finale(arr, 0, NumberOfPillers - 1);
}

void MergeSort_Finale(std::vector<std::pair<int, int> > &arr,
                      int leftIndex, int rightIndex)
{

    if (leftIndex >= rightIndex)
        return;

    int m = (leftIndex + rightIndex) / 2;

    MergeSort_Finale(arr, leftIndex, m);
    MergeSort_Finale(arr, m + 1, rightIndex);

    Merge(arr, leftIndex, m, rightIndex);
}

void Merge(std::vector<std::pair<int, int> > &arr,
           int leftIndex, int m, int rightIndex)
{

    int arrSizeLeft = m - leftIndex + 1;
    int arrSizeRight = rightIndex - m;

    int left[arrSizeLeft];
    for (int i = 0; i < arrSizeLeft; i++)
    {
        left[i] = arr[leftIndex + i].first;
        arr[leftIndex + i].second = LEFT;
    }

    int right[arrSizeRight];
    for (int i = 0; i < arrSizeRight; i++)
    {
        right[i] = arr[m + 1 + i].first;
        arr[m + 1 + i].second = RIGHT;
    }

    BeginDrawing();
    // ClearBackground(PURPLE);

    // DrawArray(arr);

    EndDrawing();

    int i = 0; // Left index
    int j = 0; // Right index

    int k = leftIndex; // New array index;

    while (i < arrSizeLeft && j < arrSizeRight)
    {
        if (left[i] <= right[j])
        {
            arr[k].first = left[i];
            i++;
        }
        else
        {
            arr[k].first = right[j];
            j++;
        }
        arr[k].second = SORTED;

        k++;
    }

    while (i < arrSizeLeft)
    {
        arr[k].first = left[i];
        arr[k].second = SORTED;

        i++;
        k++;
    }

    while (j < arrSizeRight)
    {
        arr[k].first = right[j];
        arr[k].second = SORTED;

        j++;
        k++;
    }
}

// Quick Sort:
void Quick_Sort(std::vector<std::pair<int, int> > &arr)
{
    Quick_Sort_Final(arr, 0, NumberOfPillers - 1);
}

void Quick_Sort_Final(std::vector<std::pair<int, int> > &arr, int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);

        Quick_Sort_Final(arr, low, pi - 1);
        Quick_Sort_Final(arr, pi + 1, high);
    }
    else
    {
        arr[low].second = SORTED;
        arr[high].second = SORTED;
    }
}

int Partition(std::vector<std::pair<int, int> > &arr, int low, int high)
{
    int pivot = arr[high].first;
    arr[high].second = PIVOT;

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        arr[j].second = COMPARING;

        if (arr[j].first < pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);

            arr[i].second = LEFT;
        }
        else
        {
            arr[j].second = RIGHT;
        }

        BeginDrawing();
        // ClearBackground(PURPLE);

        // DrawArray(arr);

        EndDrawing();

        for (int k = 0; k < NumberOfPillers; k++)
        {
            /* if (arr[k].second != SORTED && arr[k].second != PIVOT)
                arr[k].second = NORMAL; */

            if (arr[k].second == COMPARING)
                arr[k].second = NORMAL;
        }
    }

    arr[high].second = SORTED;

    i++;
    std::swap(arr[i], arr[high]);

    for (int k = 0; k < NumberOfPillers; k++)
    {
        if (arr[k].second != SORTED && arr[k].second != PIVOT)
            arr[k].second = NORMAL;
    }

    return i;
}
