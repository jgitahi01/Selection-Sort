#include <iostream>
#include <fstream>
#include <cstddef>
#include <ctype.h>

using namespace std;

struct statType
{
        char ascii;
        int weight;
/*
This is what you will be sorting by weight.

You may define any operators you need (or want) on these objects.
(I would think that, since we're sorting, the six relational operators
and assignment would come in real handy!)

I have written the printArr routine without using insertion on statType.
*/
};

const int ARR_BOUND=256;
void loadArr(statType*);
void printArr(statType*, string="");
void selectionSort(statType*);
void bubbleSort(statType*);
void insertionSort(statType*);
void heapSort(statType*);

int main()
{
        statType* dataArr;
        dataArr=new statType[ARR_BOUND];
        loadArr(dataArr);
        printArr(dataArr,"Unsorted Data");
        
        selectionSort(dataArr);
        printArr(dataArr,"Selection Sort"); 
        loadArr(dataArr);
        bubbleSort(dataArr);
        printArr(dataArr,"Bubble Sort");
        loadArr(dataArr);
        insertionSort(dataArr);
        printArr(dataArr,"Insertion Sort");
        loadArr(dataArr);
        heapSort(dataArr);
        printArr(dataArr,"Heap Sort");
        
        return 0;
}

// *************************************************

void loadArr(statType* arr)
{
        ifstream inFile;
        inFile.open("assignment2.input.txt"); // The input file must be in same directory as source file
        if( inFile.fail() )
        {
                cout<<"file error\n";
                cin.get();
                exit(1);
        }
        for(int i=0; i<ARR_BOUND; i++) // initialize the array
        {
                arr[i].ascii=(char)i;
                arr[i].weight=0;
        }
        char ch;
        while(true)
        {
                ch=inFile.get();
                cout<<ch; // stream to console (optional).        
                // Comment this line to suppress the echo print.
                if( inFile.eof() )
                        break;
                arr[(int)ch].weight++;
        }
        inFile.close();
        inFile.clear(); // resets the IO flags
}

// **************************************************

void printArr(statType* arr, string caption)
{
        int chCnt=0;
        cout<<"\n\n\t"<<caption<<'\n';
        for(int i=0; i<ARR_BOUND; i++)       
                if(arr[i].weight)
                {
                        cout<<"\t*\t"<<i<<'\t'<<arr[i].ascii<<'\t'<<arr[i].weight<<" ~\n";
                        chCnt+=arr[i].weight;
                }
        cout<<"\n\n\t"<<chCnt<<" characters processed.\n\tInput paused, press 'Enter'"; // I get 3946
        cin.get();
}

//***************************************************

void swap(struct statType *xp,struct statType *yp) 
{ 
    struct statType temp;
        
    temp = *xp; 
    *xp  = *yp; 
    *yp  = temp; 
} 

void selectionSort(statType* arr)
{
    int min_idx; 
        
    for (int i=0;i<ARR_BOUND-1;i++) 
    { 
        min_idx = i; 
        for (int j=i+1;j<ARR_BOUND;j++) 
        if (arr[j].weight<arr[min_idx].weight) 
            min_idx = j; 
  
        swap(&arr[min_idx], &arr[i]); 
    } 
}

void bubbleSort(statType* arr)
{
        struct statType temp;
        for(int i=0; i<ARR_BOUND; i++)
                for(int j=1; j<ARR_BOUND; j++)
                        if(arr[j].weight<arr[j-1].weight)
                        {
                                temp = arr[j];
                                arr[j] = arr[j-1];
                                arr[j-1] = temp;        
                        }
}

void insertionSort(statType* arr)
{
    for (int i=1;i<ARR_BOUND;i++)
    {
        struct statType key = arr[i];
                int j = i-1;
        while (j>=0 && arr[j].weight>key.weight)
        {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

void heapify(struct statType *arr,int n,int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
  
    if (l < ARR_BOUND && arr[l].weight > arr[largest].weight)
        largest = l;
  
    if (r < ARR_BOUND && arr[r].weight > arr[largest].weight)
        largest = r;
  
    if (largest != i) 
        {
        swap(arr[i],arr[largest]);
        heapify(arr,n,largest);
    }
}

void heapSort(statType* arr)
{
    for (int i=ARR_BOUND/2-1;i>=0;i--)
        heapify(arr,ARR_BOUND,i);
  
    for (int i=ARR_BOUND-1;i>=0;i--) 
        {
        swap(arr[0],arr[i]);
        heapify(arr,i,0);
    }
}