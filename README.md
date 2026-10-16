# Arena

C++23 ve [raylib](https://www.raylib.com) ile yazılan, Vampire Survivors tarzı bir arena survival oyunu. Asıl amaç oyun değil: aynı oyunu her aşamada farklı bir **programming paradigm** ile yeniden şekillendirip CS321'de işlenen trade-off'ları **ölçerek** öğrenmek.

Her aşamada tek metric değişmez: **frame time (ms)**. Bir değişikliğin iyi olup olmadığına "daha temiz görünüyor" diye değil, aynı koşullarda ölçülmüş before/after ile karar verilir.

## Kurulum

Gerekenler: CMake 3.25+, C++23 destekli bir derleyici (Clang 17+, GCC 13+ veya MSVC 2022), Git. raylib ilk configure sırasında otomatik indirilir; ayrıca kurmana gerek yok.

**Qt Creator:** File → Open File or Project → `CMakeLists.txt` → Configure Project → Run.

**Terminal:**

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/arena
```

Linux'ta raylib şu paketleri ister: `libgl1-mesa-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libasound2-dev`. macOS ve Windows'ta ek paket gerekmez.

**Kontroller:** WASD veya ok tuşları ile hareket, ESC ile çıkış.

## Yol haritası

Her aşama ayrı bir git tag'i (`stage-0`, `stage-1`...) ile kapanır; böylece aşamalar arasında `git diff` alıp ne değiştiğini görebilirsin.

| Aşama | Paradigm / konu | Oyunda eklenen | Ölçülecek soru |
|---|---|---|---|
| 0 ✅ | Procedural | Game loop, oyuncu hareketi, delta time | 60 FPS'te frame time kaç ms? |
| 1 | Procedural | Düşmanlar oyuncuya yürür, çarpışma, can, skor | Kaç düşmanda frame time 16,6 ms'yi aşar? |
| 2 | OOP | `Entity` base class, `virtual update()/draw()`, düşman türleri | Aşama 1'e göre aynı düşman sayısında fark ne? |
| 3 | Generics | `ObjectPool<T>`; silahlar `virtual` yerine `std::variant` + `std::visit` | Runtime vs compile-time dispatch farkı |
| 4 | Functional | Pure `update(state, input) -> state`, `std::ranges`, seed'li deterministic replay | Aynı seed iki kez aynı oyunu üretiyor mu? |
| 5 | Data-oriented / ECS | 5.000+ düşman, AoS → SoA | Aşama 2'deki OOP tasarımına göre kaç kat hızlı? |
| 6 | Agent-driven code | Claude refactor eder; clang-tidy + benchmark gate script'i kabul veya ret verir | Gate hangi değişikliği reddetti, neden? |
| 7 | Optimizasyon | `constexpr` tablolar, `-O2`/`-O3`, LTO | Her bayrak frame time'ı ne kadar değiştirdi? |

Teslim haftalarında (CS321 Phase 1: 23-27 Kasım, Phase 2: 21-25 Aralık) proje dondurulur.

## Aşama 1 görevi

`src/main.cpp` içinde, sınıf kullanmadan (henüz procedural aşamadayız):

1. Düşmanları bir `std::vector<Vector2>` içinde tut; her saniye ekranın kenarından yeni bir düşman doğsun.
2. Her düşman her frame oyuncuya doğru yürüsün (oyuncu hareketindeki normalize mantığını yeniden kullan).
3. Düşman oyuncuya değerse can azalsın; can bitince "Game Over" yazısı çıksın.
4. Ekranın köşesine düşman sayısını yaz.
5. Bonus: doğma hızını artırıp frame time'ın 16,6 ms'yi geçtiği düşman sayısını not et. Bu sayı Aşama 2 ve 5'te karşılaştırma noktamız olacak.

## Ölçüm notları

Ölçümleri buraya ekle: tarih, aşama, düşman sayısı, build tipi (Debug/Release), ortalama frame time.

| Tarih | Aşama | Düşman | Build | Frame time |
|---|---|---|---|---|
| | | | | |
