#include <iostream>
#include <random>
#include <string>
#include <array>

template <typename T>
void swap(T &x, T &y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
T median(const T &x, const T &y, const T &z)
{
    if (x < y)
    {
        if (y < z)
        {
            return y;
        }
        else if (z < x)
        {
            return x;
        }
        else
        {
            return z;
        }
    }
    else
    {
        if (z < y)
        {
            return y;
        }
        else if (x < z)
        {
            return x;
        }
        else
        {
            return z;
        }
    }
}

template <typename T>
T getPivot(const T *array, const int &start, const int &end)
{
    return median(array[start], array[start + (end - start) / 2], array[end]);
}

template <typename T>
void bubbleSort(T *array, int size, int &step, int &swapCount)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 1; j < size - i; j++)
        {
            step++;
            if (array[j] < array[j - 1])
            {
                swap(array[j], array[j - 1]);
                ++swapCount;
            }
        }
    }
}

template <typename T>
void quickSort(T *array, int start, int end, int &step, int &swapCount)
{
    if (start < end)
    {
        int i = start;
        int j = end;
        T pivot = getPivot(array, start, end);

        while (true)
        {

            while (array[i] < pivot)
            {
                ++step;
                ++i;
            }
            ++step;

            while (pivot < array[j])
            {
                ++step;
                --j;
            }
            ++step;

            if (i >= j)
            {
                break;
            }

            swap(array[i], array[j]);
            ++swapCount;

            ++i;
            --j;
        }

        quickSort(array, start, i - 1, step, swapCount);
        quickSort(array, j + 1, end, step, swapCount);
    }
}

template <typename T>
void insertSort(T *array, const int &size, int &step, int &swapCount)
{
    for (int i = 1; i < size; i++)
    {
        for (int j = i; j > 0; j--)
        {
            ++step;
            if (array[j - 1] > array[j])
            {
                swap(array[j - 1], array[j]);
                ++swapCount;
            }
            else
            {
                break;
            }
        }
    }
}

void printArray(int *array, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << array[i] << " ";
    }
}

void makeArrayRandom(int *array, const int &size)
{
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::uniform_int_distribution<int> dist(1, 100000);

    for (int i = 0; i < size; i++)
    {
        array[i] = dist(engine);
    }
}

void makeArrayInverse(int *array, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = size - i;
    }
}

void makeArrayInput(int *array, const int &size)
{
    for (int i = 0; i < size; i++)
    {
        std::cin >> array[i];
    }
}

constexpr int ARRAY_SIZE = 40000;

int main()
{
    int *array = new int[ARRAY_SIZE];
    int *array2 = new int[ARRAY_SIZE];
    int *array3 = new int[ARRAY_SIZE];

    std::array<std::string, 3> sortNames = {"Bubble", "Quick", "Insert"};

    int step[3] = {0, 0, 0};
    int swapCount[3] = {0, 0, 0};

    // Inverse Array
    //    makeArrayInverse(array, ARRAY_SIZE);

    // Random Array
    makeArrayRandom(array, ARRAY_SIZE);

    // From input
    //    makeArrayInput(array, ARRAY_SIZE);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array2[i] = array3[i] = array[i];
    }

    std::cout << "Problem > ";
    printArray(array, ARRAY_SIZE);
    std::cout << std::endl;

    std::cout << "Computing bubble sort..." << std::endl;
    bubbleSort(array, ARRAY_SIZE, step[0], swapCount[0]);
    std::cout << "Finish bubble sort." << std::endl;

    std::cout << "Computing quick sort..." << std::endl;
    quickSort(array2, 0, ARRAY_SIZE - 1, step[1], swapCount[1]);
    std::cout << "Computing quick sort." << std::endl;

    std::cout << "Computing insert sort..." << std::endl;
    insertSort(array3, ARRAY_SIZE, step[2], swapCount[2]);
    std::cout << "Finish insert sort." << std::endl;

    std::cout << "Answer > " << std::endl;
    printArray(array, ARRAY_SIZE);
    std::cout << "\n\n";

    std::cout << "Result" << std::endl;
    std::cout << "Problem Size = " << ARRAY_SIZE << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << sortNames[i] << "-> step = " << step[i] << ", swap = " << swapCount[i] << "\n";
    }

    delete[] array;
    delete[] array2;
    delete[] array3;
}