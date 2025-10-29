#include <iostream> 
#include <stdexcept> 
using namespace std; 

class DynamicArray { 
private: 
    int* arr; 
    int size; 
public: 
    DynamicArray(int s) : size (s) { 
        arr = new int[size];
        for (int i = 0; i < size; i++) arr[i] = 0;
    } 
    ~DynamicArray() { 
        delete [] arr; 
    } 
    int& operator[] (int index) { 
        if (index < 0 || index >= size ) {
            throw out_of_range("Index out of bounds"); 
        }
        return arr[index];
    }
    int Size() const { 
        return size; 
    } 
    void ReSize(int sNew) { 
        int* pTmp = new int[sNew];
        for (int i = 0; i < size; i++ ) pTmp[i] = arr[i];
        size = sNew; 
        delete [] arr; 
        arr = pTmp;
    }
};

int main() {
    try {
        DynamicArray arr(5);

        for (int i = 0; i < arr.Size(); i++)
            arr[i] = i * 10;

        cout << "Original array: ";
        for (int i = 0; i < arr.Size(); i++)
            cout << arr[i] << " ";
        cout << endl;

        arr.ReSize(10);
        cout << "Resized array: ";
        for (int i = 0; i < arr.Size(); i++)
            cout << arr[i] << " ";
        cout << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
