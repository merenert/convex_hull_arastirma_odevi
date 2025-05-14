#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

struct Nokta {
    int x, y;
};

// Global referans noktası (en alt ve en sola yakın nokta)
Nokta referans;

// İki nokta arasındaki mesafenin karesi
int mesafeKaresi(Nokta a, Nokta b) {
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

// 3 noktanın yönü: 0 = düz, 1 = sağa, 2 = sola dönüş
int yon(Nokta a, Nokta b, Nokta c) {
    int deger = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
    if (deger == 0) return 0;
    return (deger > 0) ? 1 : 2;
}

// Açılara göre sıralama için karşılaştırıcı
bool karsilastir(Nokta a, Nokta b) {
    int o = yon(referans, a, b);
    if (o == 0)
        return mesafeKaresi(referans, a) < mesafeKaresi(referans, b);
    return o == 2;
}

// Dışbükey zarfı hesaplayan fonksiyon
vector<Nokta> disbukeyZarf(vector<Nokta>& noktalar) {
    int n = noktalar.size();
    if (n < 3) return {};

    // En alttaki ve en sola yakın noktayı bul
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if ((noktalar[i].y < noktalar[minIndex].y) ||
            (noktalar[i].y == noktalar[minIndex].y && noktalar[i].x < noktalar[minIndex].x)) {
            minIndex = i;
        }
    }

    // Referans noktasını en başa al
    swap(noktalar[0], noktalar[minIndex]);
    referans = noktalar[0];

    // Açılara göre sırala
    sort(noktalar.begin() + 1, noktalar.end(), karsilastir);

    // İlk 3 noktayı yığına ekle
    stack<Nokta> yigin;
    yigin.push(noktalar[0]);
    yigin.push(noktalar[1]);
    yigin.push(noktalar[2]);

    // Diğer noktaları sırayla işle
    for (int i = 3; i < n; i++) {
        while (yigin.size() >= 2) {
            Nokta ikinci = yigin.top(); yigin.pop();
            Nokta birinci = yigin.top();
            if (yon(birinci, ikinci, noktalar[i]) != 2) continue;
            yigin.push(ikinci);
            break;
        }
        yigin.push(noktalar[i]);
    }

    // Yığındaki noktaları vektöre al
    vector<Nokta> sonuc;
    while (!yigin.empty()) {
        sonuc.push_back(yigin.top());
        yigin.pop();
    }
    reverse(sonuc.begin(), sonuc.end());
    return sonuc;
}

int main() {
    // Noktaları tanımla
    vector<Nokta> noktalar = {
        {0, 3}, {1, 1}, {2, 2}, {4, 4},
        {0, 0}, {1, 2}, {3, 1}, {3, 3}
    };

    cout << "Orijinal Noktalar:\n";
    for (auto n : noktalar)
        cout << "(" << n.x << ", " << n.y << ") ";
    cout << "\n\n";

    // Zarfı hesapla
    vector<Nokta> zarf = disbukeyZarf(noktalar);

    cout << "Dışbükey Zarf (Graham Scan):\n";
    for (auto n : zarf)
        cout << "(" << n.x << ", " << n.y << ") ";
    cout << "\n";

    return 0;
}
