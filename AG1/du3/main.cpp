#include <iostream>
using namespace std;

struct Task
{
    int64_t id, start, finish, profit;
    
    bool operator< (const Task & j) {
        return finish < j.finish;
    }
    
    bool operator<= (const Task & j) {
        return finish <= j.finish;
    }
};

struct TableItem {
    int64_t id;
    int64_t profit;
    TableItem * node;
    
    bool operator< (const TableItem & t) {
        return profit < t.profit;
    }
};

int64_t binSearch(Task * tasks, int64_t index)
{
    int64_t low = 0, high = index - 1;
    
    while (low <= high)
    {
        int64_t mid = (low + high) / 2;
        if (tasks[mid].finish <= tasks[index].start)
        {
            if (tasks[mid + 1].finish <= tasks[index].start)
                low = mid + 1;
            else
                return mid;
        }
        else
            high = mid - 1;
    }
    
    return -1;
}

template <typename T>
void swapF(T* a, T* b)
{
    T t = *a;
    *a = *b;
    *b = t;
}

template <typename T>
T maxF(T a, T b) {
    return a < b ? b : a;
}

template <typename T>
int64_t partition (T *arr, int64_t low, int64_t high)
{
    T pivot = arr[high];
    int64_t i = (low - 1);
    
    for (int64_t j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swapF(&arr[i], &arr[j]);
        }
    }
    swapF(&arr[i + 1], &arr[high]);
    return (i + 1);
}

template <typename T>
void quickSort(T *arr, int64_t low, int64_t high)
{
    if (low < high)
    {
        int64_t pi = partition(arr, low, high);
        
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename T>
void merge(T * arr, int64_t l, int64_t m, int64_t r)
{
    int64_t i, j, k;
    int64_t n1 = m - l + 1;
    int64_t n2 = r - m;
    
    T * L = new T[n1];
    T * R = new T[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
    
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete [] L;
    delete [] R;
}

template <typename T>
void mergeSort(T * arr, int64_t l, int64_t r)
{
    if (l < r)
    {
        int64_t m = l+(r-l)/2;
        
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        
        merge(arr, l, m, r);
    }
}

TableItem * findMaxProfit(Task * arr, TableItem * table, int64_t n)
{
    TableItem node;
    node.id = arr[0].id;
    node.profit = arr[0].profit;
    node.node = nullptr;
    table[0] = node;
    
    for (int64_t i=1; i<n; i++)
    {
        TableItem newProfit;
        newProfit.id = arr[i].id;
        newProfit.profit = arr[i].profit;
        newProfit.node = nullptr;
        int64_t l = binSearch(arr, i);
        if (l != -1) {
            newProfit.profit += table[l].profit;
            newProfit.node = &(table[l]);
        }
        
        table[i] = maxF(newProfit, table[i-1]);
    }
    
    return table + n - 1;
}

int main()
{
    int64_t n;
    cin >> n;
    
    Task * arr = new Task[n];
    TableItem * table = new TableItem[n];
    
    for (int64_t i = 0; i < n; i++) {
        int64_t s, f, p;
        cin >> s >> f >> p;
        Task j;
        j.id = i;
        j.start = s;
        j.finish = f;
        j.profit = p;
        arr[i] = j;
    }
    
    mergeSort(arr, 0, n-1);
    TableItem * found = findMaxProfit(arr, table, n);
    cout << found->profit << endl;
    
    delete [] arr;
    int * ids = new int[n];
    int k = 0;
    while (found != nullptr) {
        ids[k++] = (int)found->id;
        found = found->node;
    }
    
    mergeSort(ids, 0, k-1);
    for (int64_t i = 0; i < k; i++) {
        cout << ids[i];
        if (i != k-1)
            cout << " ";
    }
    cout << endl;
    delete [] table;
    delete [] ids;
    
    return 0;
}
