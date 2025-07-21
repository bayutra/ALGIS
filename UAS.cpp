#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <utility> // Untuk std::pair
using namespace std;

// ============================== KNAPSACK GREEDY ==============================
struct Item {
    double weight;
    double value;
    double density;
};

void fractionalKnapsack() {
    vector<Item> items = {
        {2, 3, 0}, {3, 5, 0}, {5, 3, 0}, 
        {3, 3, 0}, {7, 7, 0}, {7, 2, 0}
    };
    double capacity = 15;
    double totalValue = 0;
    
    // Hitung densitas
    for (auto& item : items) {
        item.density = item.value / item.weight;
    }
    
    // Urutkan berdasarkan densitas (descending)
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.density > b.density;
    });
    
    cout << "\nKnapsack Fractional (Greedy):\n";
    cout << "Item [Weight, Value, Density]:\n";
    for (const auto& item : items) {
        cout << "[" << item.weight << ", " << item.value << ", " 
             << fixed << setprecision(2) << item.density << "] ";
    }
    cout << "\n\nProses Pengisian:\n";
    
    // Proses pengisian knapsack
    vector<pair<Item, double>> solution;
    for (const auto& item : items) {
        if (capacity <= 0) break;
        
        if (item.weight <= capacity) {
            solution.push_back(make_pair(item, 1.0));
            totalValue += item.value;
            capacity -= item.weight;
            cout << "Ambil seluruh item (" << item.weight << ", " << item.value 
                 << ") | Kapasitas tersisa: " << capacity 
                 << " | Nilai total: " << totalValue << endl;
        } else {
            double fraction = capacity / item.weight;
            solution.push_back(make_pair(item, fraction));
            totalValue += item.value * fraction;
            cout << "Ambil " << fixed << setprecision(0) << fraction*100 
                 << "% item (" << item.weight << ", " << item.value 
                 << ") | Kapasitas tersisa: 0"
                 << " | Nilai total: " << totalValue << endl;
            capacity = 0;
            break;
        }
    }
    
    cout << "\nTotal Nilai: " << totalValue << endl;
    cout << "Solusi: ";
    for (const auto& sol : solution) {
        cout << fixed << setprecision(0) << sol.second*100 << "% (" 
             << sol.first.weight << "," << sol.first.value << ") ";
    }
    cout << "\n\n=======================================\n\n";
}

// ========================= MINIMASI WAKTU (SPT) =========================
void minimizeTimeSPT() {
    vector<int> jobs = {2, 3, 5, 3, 3, 7, 7, 2};
    int makespan = 0;
    int currentTime = 0;
    
    // Urutkan job berdasarkan processing time (ascending)
    sort(jobs.begin(), jobs.end());
    
    cout << "\nMinimasi Waktu Sistem (SPT - Greedy):\n";
    cout << "Job setelah diurutkan: ";
    for (int job : jobs) cout << job << " ";
    cout << "\n\nPenjadwalan:\n";
    
    // Proses penjadwalan
    vector<pair<int, pair<int, int>>> schedule;
    for (int i = 0; i < jobs.size(); ++i) {
        int start = currentTime;
        int end = currentTime + jobs[i];
        schedule.push_back(make_pair(jobs[i], make_pair(start, end)));
        currentTime = end;
        makespan = end;
        
        cout << "Job " << i+1 << " (time=" << jobs[i] << "): "
             << start << " - " << end << endl;
    }
    
    cout << "\nMakespan: " << makespan << endl;
    cout << "Urutan Eksekusi: ";
    for (const auto& s : schedule) {
        cout << s.first << " ";
    }
    cout << "\n\n=======================================\n\n";
}

// ========================= MERGE SORT (D&C) =========================
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;
    
    // Print current state
    string indent(depth * 4, ' ');
    cout << indent << "Divide: [";
    for (int i = left; i <= right; i++) {
        cout << arr[i];
        if (i < right) cout << ", ";
    }
    cout << "]" << endl;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid, depth + 1);
    mergeSort(arr, mid + 1, right, depth + 1);
    
    // Print before merge
    cout << indent << "Merge: [";
    for (int i = left; i <= mid; i++) {
        cout << arr[i];
        if (i < mid) cout << ", ";
    }
    cout << "] & [";
    for (int i = mid + 1; i <= right; i++) {
        cout << arr[i];
        if (i < right) cout << ", ";
    }
    cout << "]" << endl;

    merge(arr, left, mid, right);
    
    // Print after merge
    cout << indent << "Hasil: [";
    for (int i = left; i <= right; i++) {
        cout << arr[i];
        if (i < right) cout << ", ";
    }
    cout << "]" << endl;
}

void runMergeSort() {
    vector<int> arr = {2, 3, 5, 3, 3, 7, 7, 2};
    
    cout << "\nMerge Sort (Divide and Conquer):\n";
    cout << "Array awal: ";
    for (int num : arr) cout << num << " ";
    cout << "\n\nProses:\n";
    
    mergeSort(arr, 0, arr.size() - 1);
    
    cout << "\nHasil akhir: ";
    for (int num : arr) cout << num << " ";
    cout << "\n\n=======================================\n";
}

// ========================= MAIN MENU =========================
int main() {
    // Tampilkan identitas
    cout << "NAMA : BAYU SAPUTRA\n";
    cout << "NIM  : 23533772\n";
    cout << "KELAS: 4C\n";
    cout << "=======================================\n";
    cout << "ALGORITMA GREEDY DAN DIVIDE AND CONQUER\n";
    cout << "=======================================\n\n";

    int choice;
    do {
        cout << "Pilih algoritma:\n";
        cout << "1. Fractional Knapsack (Greedy)\n";
        cout << "2. Minimasi Waktu Sistem (SPT)\n";
        cout << "3. Merge Sort (Divide and Conquer)\n";
        cout << "4. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        cout << endl;

        switch(choice) {
            case 1:
                fractionalKnapsack();
                break;
            case 2:
                minimizeTimeSPT();
                break;
            case 3:
                runMergeSort();
                break;
            case 4:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n\n";
        }
    } while (choice != 4);

    return 0;
}