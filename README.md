# convex_hull_arastirma_odevi

# Konveks Zar Algoritmaları: Kapsamlı Bir İnceleme

Bu belge, hesaplamalı geometrinin temel problemlerinden biri olan konveks zar (convex hull) problemini ve bu problemi çözmek için geliştirilmiş başlıca algoritmaları ayrıntılı bir şekilde ele almaktadır. Konveks zar, verilen bir nokta kümesini içeren en küçük dışbükey (konveks) çokgen olarak tanımlanır ve bilgisayar grafikleri, görüntü işleme, örüntü tanıma, coğrafi bilgi sistemleri (CBS) ve robotik gibi birçok alanda önemli uygulamalara sahiptir.

## Konveks Zar Probleminin Tanımı

Düzlemde veya daha yüksek boyutlu uzaylarda verilen sonlu bir $S$ nokta kümesi için, konveks zar $CH(S)$, $S$ kümesindeki tüm noktaları içeren en küçük konveks kümedir. İki boyutlu düzlemde bu, $S$ kümesindeki tüm noktaları çevreleyen ve köşe noktaları $S$ kümesinden seçilen en küçük alanlı dışbükey çokgen anlamına gelir. Bir nokta kümesinin konveks zarı, lastik bir bandın bu noktaların etrafına gerilmesiyle oluşan şekle benzetilebilir.

## Konveks Zar Algoritmaları

Konveks zar problemini çözmek için çeşitli algoritmalar geliştirilmiştir. Bu algoritmalar, farklı yaklaşımlar kullanır ve performansları (zaman ve bellek karmaşıklığı) açısından farklılık gösterir. Başlıca algoritmalar şunlardır:

### 1. Brute Force (Kaba Kuvvet) Yöntemi

Kaba kuvvet yöntemi, problemin tanımını doğrudan kullanarak en basit çözümlerden birini sunar. İki boyutlu düzlemde, $n$ noktadan oluşan $S$ kümesi için, her olası $(p_i, p_j)$ nokta çiftinin konveks zarın bir kenarı olup olmadığını kontrol eder. Bir $(p_i, p_j)$ doğru parçasının konveks zarın bir kenarı olması için, geri kalan tüm $n-2$ noktanın bu doğru parçasının tanımladığı doğrunun aynı tarafında veya üzerinde yer alması gerekir. Bu kontrol, her nokta çifti için diğer tüm noktalar gezilerek yapılır.

Bu yaklaşımın zaman karmaşıklığı genellikle $O(n^3)$'tür, çünkü $O(n^2)$ sayıda olası kenar vardır ve her kenar için $O(n)$ işlemle diğer noktaların konumu kontrol edilir. Üç boyutlu uzayda ise her olası yüzey (üç nokta ile tanımlanan) için benzer bir kontrol yapılır ve karmaşıklık $O(n^4)$'e çıkar. Basit olmasına rağmen, nokta sayısı arttıkça verimsiz hale gelir.

### 2. Gift Wrapping (Hediye Paketleme / Jarvis March)

Gift Wrapping algoritması, 1973 yılında R.A. Jarvis tarafından önerilmiştir ve sezgisel olarak bir hediye paketini sarma işlemine benzer. Algoritma, konveks zarın bir köşe noktasından başlar (genellikle en düşük y koordinatına sahip nokta veya birden fazla varsa en soldaki). Bu noktadan itibaren, diğer tüm noktalara göre en küçük polar açıya sahip olan bir sonraki köşe noktası bulunur. Bu işlem, bir ipin noktaların etrafına sarılması gibi düşünülebilir; her adımda ip bir sonraki noktaya gerilir. Algoritma, başlangıç noktasına geri dönene kadar bu işlemi tekrarlar.

Her bir zar köşesini bulmak için, mevcut köşeden diğer tüm noktalara olan açılar hesaplanır ve minimum açıya sahip nokta seçilir. Bu işlem $O(n)$ zaman alır. Eğer konveks zar üzerinde $h$ adet köşe varsa, toplam zaman karmaşıklığı $O(nh)$ olur. Bu algoritma, zar üzerindeki nokta sayısı $h$'nin toplam nokta sayısı $n$'ye göre küçük olduğu durumlarda (örneğin, $h = O(\\log n)$) oldukça verimlidir. Ancak, en kötü durumda (tüm noktaların zar üzerinde olduğu durum, $h=n$), karmaşıklık $O(n^2)$'ye ulaşır.

### 3. Graham Scan Yöntemi

1972 yılında Ronald Graham tarafından geliştirilen bu algoritma, konveks zarı bulmak için daha verimli bir yaklaşım sunar. Algoritma, öncelikle en düşük y koordinatına sahip (veya eşitsizlik durumunda en soldaki) $p_0$ noktasını bulur. Ardından, diğer tüm noktaları $p_0$ noktasına göre polar açılarına göre sıralar. Eşit açılı noktalar durumunda, $p_0$'a daha yakın olan nokta önce gelir.

Sıralama işleminden sonra, algoritma bir yığın (stack) veri yapısı kullanarak noktaları sırayla işler. İlk iki sıralı nokta ( $p_0$ ve $p_1$) yığına eklenir. Ardından, $i=2$'den $n-1$'e kadar her $p_i$ noktası için şu kontrol yapılır: Yığının tepesindeki iki nokta (Top ve Next-to-Top) ile $p_i$ noktasının oluşturduğu yönelim kontrol edilir. Eğer bu üç nokta bir "sağa dönüş" yapıyorsa (yani $p_i$ noktası, yığındaki son kenarın oluşturduğu yöne göre içe doğru bir dönüş yapıyorsa), bu durum konveksliği bozar ve yığının tepesindeki nokta (Top) yığından çıkarılır. Bu kontrol, sola dönüş sağlanana kadar tekrarlanır. Sola dönüş sağlandığında (veya yığında ikiden az nokta kaldığında), $p_i$ noktası yığına eklenir.

Tüm noktalar işlendikten sonra yığında kalan noktalar, konveks zarın köşelerini saat yönünün tersine sıralı olarak içerir. Algoritmanın karmaşıklığı, başlangıçtaki sıralama adımı tarafından domine edilir ve $O(n \\log n)$'dir.

### 4. QuickHull Yöntemi

QuickHull algoritması, ismini Quicksort algoritmasına olan benzerliğinden alır ve bir böl ve fethet stratejisi kullanır. 1977 yılında Preparata ve Hong tarafından önerilmiştir. Algoritma, öncelikle en soldaki ($A$) ve en sağdaki ($B$) noktaları bulur (veya en alttaki ve en üstteki). Bu iki nokta kesinlikle konveks zar üzerindedir ve $S$ kümesini $AB$ doğrusunun üstünde ve altında kalan iki alt kümeye ayırır.

Algoritma, bu iki alt küme için özyinelemeli olarak çalışır. Örneğin, $AB$ doğrusunun üstündeki $S_1$ alt kümesi için, $AB$ doğrusuna en uzak olan $C$ noktası bulunur. Bu $C$ noktası da konveks zar üzerindedir. $A$, $B$ ve $C$ noktaları bir üçgen oluşturur. $ABC$ üçgeninin içinde kalan noktalar konveks zarın parçası olamayacağı için atılır. Geriye kalan noktalar, $AC$ doğrusunun dışında ve $CB$ doğrusunun dışında kalan iki yeni alt kümeye ayrılır. Algoritma, bu yeni alt kümeler için özyinelemeli olarak tekrarlanır.

QuickHull'un ortalama zaman karmaşıklığı $O(n \\log n)$'dir. Ancak, en kötü durumda (örneğin, noktaların çoğu yaklaşık olarak bir çember üzerinde yer alıyorsa), karmaşıklık $O(n^2)$'ye ulaşabilir. Pratikte genellikle oldukça hızlı çalışır.

### 5. Divide & Conquer (Böl ve Fethet) Yöntemi

Bu yöntem, klasik böl ve fethet paradigmasını uygular. Nokta kümesi $S$, x koordinatlarına göre sıralanır ve yaklaşık olarak eşit büyüklükte iki alt kümeye ($S_L$ ve $S_R$) bölünür. Algoritma, özyinelemeli olarak $S_L$ ve $S_R$ için konveks zarları ($CH(S_L)$ ve $CH(S_R)$) bulur.

En kritik adım, bu iki alt konveks zarı birleştirmektir. Birleştirme işlemi, iki zar arasında "üst teğet" ve "alt teğet" olarak adlandırılan iki ortak teğet doğru parçasını bularak yapılır. Üst teğet, her iki zarın da altında kalan ve her iki zardan birer noktayı birleştiren doğru parçasıdır. Alt teğet ise benzer şekilde her iki zarın da üstünde kalır. Bu teğetler bulunduktan sonra, $CH(S_L)$ ve $CH(S_R)$'nin teğet noktaları arasındaki kısımları atılır ve teğetler yeni kenarlar olarak eklenerek nihai $CH(S)$ oluşturulur.

Teğetleri bulma işlemi $O(n)$ zamanda yapılabilir. Özyinelemeli denklemin çözümü $T(n) = 2T(n/2) + O(n)$ şeklindedir ve bu da toplam $O(n \\log n)$ zaman karmaşıklığı verir.

### 6. Monotone Chain (Andrew's Algorithm)

Monotone Chain algoritması, 1979 yılında A.M. Andrew tarafından önerilmiştir ve Graham Scan'e bir alternatif sunar. Graham Scan gibi polar açı sıralaması yerine, noktaları x koordinatlarına göre (eşitlik durumunda y koordinatlarına göre) sıralar. Bu sıralama, açı hesaplamalarından kaynaklanabilecek sayısal hassasiyet sorunlarını önler.

Sıralanmış noktalar kullanılarak, önce konveks zarın "üst zinciri" (upper hull), sonra "alt zinciri" (lower hull) ayrı ayrı oluşturulur. Üst zincir oluşturulurken, noktalar soldan sağa doğru işlenir ve Graham Scan'dekine benzer bir yığın ve sola dönüş kontrolü kullanılır (sağa dönüş yapan noktalar atılır). Alt zincir oluşturulurken ise noktalar yine soldan sağa (veya bazen sağdan sola) işlenir ve bu kez sağa dönüş kontrolü yapılır (sola dönüş yapan noktalar atılır).

Son olarak, bulunan üst ve alt zincirler birleştirilerek (başlangıç ve bitiş noktaları hariç) tam konveks zar elde edilir. Algoritmanın zaman karmaşıklığı, başlangıçtaki sıralama adımı nedeniyle $O(n \\log n)$'dir.

### 7. Incremental Convex Hull (Artımlı Konveks Zar)

Artımlı yöntem, noktaları teker teker işleyerek konveks zarı aşamalı olarak oluşturur. Genellikle noktalar önce x koordinatlarına göre sıralanır. İlk üç nokta (doğrusal değilse) başlangıçtaki üçgen konveks zarı oluşturur.

Ardından, geri kalan noktalar ($p_4, p_5, ..., p_n$) sırayla eklenir. Her bir $p_i$ noktası eklendiğinde, bu noktanın mevcut konveks zar $CH_{i-1}$'in içinde mi yoksa dışında mı olduğu kontrol edilir. Eğer içindeyse, zar değişmez ($CH_i = CH_{i-1}$). Eğer dışındaysa, zarın güncellenmesi gerekir. Bu durumda, $p_i$ noktasından görülebilen zar kenarları bulunur ve kaldırılır. Kaldırılan kenarların uç noktaları ile $p_i$ noktası arasında yeni kenarlar eklenerek yeni konveks zar $CH_i$ oluşturulur.

Bir noktanın içerde/dışarda olup olmadığını kontrol etmek ve gerekirse zarı güncellemek genellikle $O(\\log h)$ veya $O(h)$ zaman alabilir (h mevcut zar köşesi sayısı). Sıralama ile birlikte toplam zaman karmaşıklığı genellikle $O(n \\log n)$ olur.

## Algoritmaların Karşılaştırılması ve Sonuç

| Algoritma          | Zaman Karmaşıklığı (Ortalama) | Zaman Karmaşıklığı (En Kötü) | Notlar                                       |
|--------------------|-------------------------------|------------------------------|----------------------------------------------|
| Brute Force        | $O(n^3)$                      | $O(n^3)$                     | Basit ama verimsiz                           |
| Gift Wrapping      | $O(nh)$                       | $O(n^2)$                     | $h$ küçükse verimli                          |
| Graham Scan        | $O(n \\log n)$                | $O(n \\log n)$               | Sıralama gerektirir, yığın kullanır          |
| QuickHull          | $O(n \\log n)$                | $O(n^2)$                     | Pratikte hızlı, Quicksort benzeri            |
| Divide & Conquer   | $O(n \\log n)$                | $O(n \\log n)$               | Klasik böl ve fethet                         |
| Monotone Chain     | $O(n \\log n)$                | $O(n \\log n)$               | Açı hesaplamaz, x-sıralaması kullanır      |
| Incremental        | $O(n \\log n)$                | $O(n \\log n)$               | Noktaları aşamalı ekler                      |

*n: toplam nokta sayısı, h: konveks zar üzerindeki nokta sayısı*

Konveks zar algoritması seçimi, uygulamanın özel gereksinimlerine ve veri kümesinin özelliklerine bağlıdır. Genel olarak, $O(n \\log n)$ karmaşıklığına sahip algoritmalar (Graham Scan, Monotone Chain, Divide & Conquer, Incremental) büyük veri kümeleri için daha uygun kabul edilir. Gift Wrapping, zar üzerindeki nokta sayısının az olması beklenen durumlar için iyi bir seçenek olabilir. QuickHull, ortalama performansı iyi olmasına rağmen en kötü durum karmaşıklığına dikkat edilmelidir. Brute force ise genellikle sadece küçük $n$ değerleri için veya eğitim amaçlı kullanılır.

## Kaynakça

*   Akgül, B., & Kutucu, H. (2015). Convex Hull Problemine Genel Bakış: Algoritmalar ve Karmaşıklıkları. Akademik Bilişim 2015. [https://ab.org.tr/ab15/kitap/473.pdf](https://ab.org.tr/ab15/kitap/473.pdf)


