#include <algorithm>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


void MergeSort(double a[], int l, int mid, int r) {
    int i = l, j = mid + 1;
    vector<double> temp;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            temp.push_back(a[i]);
            i++;
        } else {
            temp.push_back(a[j]);
            j++;
        }
    }

    while (i <= mid) {
        temp.push_back(a[i]);
        i++;
    }

    while (j <= r) {
        temp.push_back(a[j]);
        j++;
    }

    for (int k = l; k <= r; k++) {
        a[k] = temp[k - l];
    }
}

void MergeSort(double arr[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        MergeSort(arr, l, mid);
        MergeSort(arr, mid + 1, r);
        MergeSort(arr, l, mid, r);
    }
}


void Heapify(double a[], int n, int i) {
    int max = i;
    int childLeft = i * 2 + 1;
    int childRight = i * 2 + 2;

    if (childLeft < n && a[max] < a[childLeft])
        max = childLeft;

    if (childRight < n && a[max] < a[childRight])
        max = childRight;

    if (max != i) {
        swap(a[max], a[i]);
        Heapify(a, n, max);
    }
}

void buildHeap(double a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(a, n, i);
}

void HeapSort(double a[], int n) {
    buildHeap(a, n);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        Heapify(a, i, 0);
    }
}


void QuickSort(double a[], int left, int right) {
    int i, j;
    double pivot;

    pivot = a[(left + right) / 2];
    i = left;
    j = right;

    while (i <= j) {
        while (a[i] < pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i <= j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        QuickSort(a, left, j);

    if (i < right)
        QuickSort(a, i, right);
}


// HÀM HỖ TRỢ ĐỌC DỮ LIỆU: thuật toán nhận dữ liệu từ các file .bin.

bool readBinary(const string& filename, vector<double>& a) {
    ifstream in(filename, ios::binary);
    if (!in) {
        cerr << "Khong the mo file: " << filename << '\n';
        return false;
    }

    in.seekg(0, ios::end);
    const streamoff bytes = in.tellg();
    in.seekg(0, ios::beg);

    if (bytes <= 0 || bytes % static_cast<streamoff>(sizeof(double)) != 0) {
        cerr << "Kich thuoc file khong hop le: " << filename << '\n';
        return false;
    }

    const size_t n = static_cast<size_t>(bytes / static_cast<streamoff>(sizeof(double)));
    a.resize(n);

    in.read(reinterpret_cast<char*>(a.data()), static_cast<streamsize>(bytes));

    if (!in) {
        cerr << "Loi khi doc file: " << filename << '\n';
        return false;
    }

    return true;
}

// ĐO THỜI GIAN: lấy tg gốc của thuật toán sắp xếp chứ không phải toàn bộ của ctrinh.
template <typename SortFunction>
long long measureTime(vector<double>& a, SortFunction sortFunction) {
    const auto start = chrono::steady_clock::now();
    sortFunction(a);
    const auto finish = chrono::steady_clock::now();

    return chrono::duration_cast<chrono::milliseconds>(finish - start).count();
}

bool isSorted(const vector<double>& a) {
    return is_sorted(a.begin(), a.end());
}

int main() {
    const vector<string> files = {
        "data/d01_ascending.bin",
        "data/d02_descending.bin",
        "data/d03_random.bin",
        "data/d04_random.bin",
        "data/d05_random.bin",
        "data/d06_random.bin",
        "data/d07_random.bin",
        "data/d08_random.bin",
        "data/d09_random.bin",
        "data/d10_random.bin"
    };

    ofstream csv("results/results.csv");
    if (!csv) {
        cerr << "Khong the tao file results/results.csv\n";
        return 1;
    }

    csv << "Data,QuickSort,HeapSort,MergeSort,sort(C++)\n";

    long double sumQuick = 0;
    long double sumHeap = 0;
    long double sumMerge = 0;
    long double sumStd = 0;

    for (size_t idx = 0; idx < files.size(); idx++) {
        const string& filename = files[idx];
        cout << "\n=== Du lieu " << idx + 1 << " ===\n";
        cout << filename << '\n';

        // QuickSort: đọc lại dữ liệu gốc
        vector<double> a;
        if (!readBinary(filename, a)) return 1;
        const long long tQuick = measureTime(a, [](vector<double>& x) {
            if (!x.empty())
                QuickSort(x.data(), 0, static_cast<int>(x.size()) - 1);
        });
        const bool okQuick = isSorted(a);

        // HeapSort: đọc lại dữ liệu gốc
        a.clear();
        if (!readBinary(filename, a)) return 1;
        const long long tHeap = measureTime(a, [](vector<double>& x) {
            HeapSort(x.data(), static_cast<int>(x.size()));
        });
        const bool okHeap = isSorted(a);

        // MergeSort: đọc lại dữ liệu gốc
        a.clear();
        if (!readBinary(filename, a)) return 1;
        const long long tMerge = measureTime(a, [](vector<double>& x) {
            if (!x.empty())
                MergeSort(x.data(), 0, static_cast<int>(x.size()) - 1);
        });
        const bool okMerge = isSorted(a);

        // std::sort: đọc lại dữ liệu gốc
        a.clear();
        if (!readBinary(filename, a)) return 1;
        const long long tStd = measureTime(a, [](vector<double>& x) {
            sort(x.begin(), x.end());
        });
        const bool okStd = isSorted(a);

        if (!okQuick || !okHeap || !okMerge || !okStd) {
            cerr << "LOI: co thuat toan khong sap xep dung du lieu " << idx + 1 << '\n';
            return 1;
        }

        cout << "QuickSort : " << tQuick << " ms\n";
        cout << "HeapSort  : " << tHeap << " ms\n";
        cout << "MergeSort : " << tMerge << " ms\n";
        cout << "std::sort : " << tStd << " ms\n";

        csv << (idx + 1) << ','
            << tQuick << ','
            << tHeap << ','
            << tMerge << ','
            << tStd << '\n';

        sumQuick += tQuick;
        sumHeap += tHeap;
        sumMerge += tMerge;
        sumStd += tStd;
    }

    csv << fixed << setprecision(3);
    csv << "Trung binh,"
        << static_cast<double>(sumQuick / files.size()) << ','
        << static_cast<double>(sumHeap / files.size()) << ','
        << static_cast<double>(sumMerge / files.size()) << ','
        << static_cast<double>(sumStd / files.size()) << '\n';

    csv.close();

    cout << "\nDa hoan tat.\n";
    cout << "Ket qua duoc luu tai: results/results.csv\n";

    return 0;
}
