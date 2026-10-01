#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

static constexpr size_t N = 1'000'000;
static constexpr uint64_t BASE_SEED = 20261001ULL;

void writeBinary(const string& filename, const vector<double>& a) {
    ofstream out(filename, ios::binary);
    if (!out) {
        cerr << "Khong the mo file: " << filename << '\n';
        exit(1);
    }

    out.write(reinterpret_cast<const char*>(a.data()),
              static_cast<streamsize>(a.size() * sizeof(double)));
    if (!out) {
        cerr << "Loi khi ghi file: " << filename << '\n';
        exit(1);
    }
}

int main() {
    vector<double> base(N);

    mt19937_64 rng(BASE_SEED);
    uniform_real_distribution<double> dist(-1'000'000.0, 1'000'000.0);

    for (double& x : base) {
        x = dist(rng);
    }

    // D1: tang dan
    vector<double> d1 = base;
    sort(d1.begin(), d1.end());
    writeBinary("data/d1_ascending.bin", d1);

    // D2: giam dan
    vector<double> d2 = d1;
    reverse(d2.begin(), d2.end());
    writeBinary("data/d2_descending.bin", d2);

    // D3-D10: cung tap gia tri nhung xao tron voi cac seed khac nhau
    for (int id = 3; id <= 10; ++id) {
        vector<double> d = d1;
        mt19937_64 shuffle_rng(BASE_SEED + static_cast<uint64_t>(id));
        shuffle(d.begin(), d.end(), shuffle_rng);
        writeBinary("data/d" + to_string(id) + "_random.bin", d);
    }

    cout << "Da tao 10 day, moi day " << N << " phan tu double.\n";
    cout << "Kich thuoc ly thuyet moi file: "
         << N * sizeof(double) / (1024.0 * 1024.0) << " MiB.\n";
    return 0;
}
