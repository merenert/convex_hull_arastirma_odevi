#include <iostream>
#include <vector>
#include "convex_hull_kodu.cpp"

using namespace std;

// Ekrana bir vektördeki noktaları yazdıran yardımcı fonksiyon
void noktalarYazdir(const vector<Nokta>& noktalar) {
    for (const auto& n : noktalar) {
        cout << "(" << n.x << ", " << n.y << ") ";
    }
    cout << endl;
}

int main() {
    // Örnek giriş noktaları
    vector<Nokta> noktalar = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4},
        {0, 0}, {1, 2}, {3, 1}, {3, 3}
    };

    cout << "Giriş Noktaları:\n";
    noktalarYazdir(noktalar);
    cout << endl;

    // Algoritmayı çalıştır
    vector<Nokta> zarf = disbukeyZarf(noktalar);

    // Sonuçları yazdır
    cout << "Dışbükey Zarf (Convex Hull) Noktaları:\n";
    noktalarYazdir(zarf);

    return 0;
}
