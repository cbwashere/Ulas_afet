#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;
HardwareSerial ss(2);  // UART2 -> RX=16, TX=17

bool donanimYok = true;  // Donanım yoksa true yap

void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, 16, 17);  // Baudrate, RX, TX

  Serial.println("GPS başlatılıyor...");
}

void loop() {
  if (donanimYok) {
    // Donanım yoksa sahte veri gönder
    const char *fakeGPS = "$GPGGA,123519,4100.000,N,02858.000,E,1,08,0.9,545.4,M,46.9,M,,*47\n";

    for (int i = 0; fakeGPS[i]; i++) {
      gps.encode(fakeGPS[i]);
    }

    if (gps.location.isUpdated()) {
      Serial.print("Simülasyon - Enlem: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Simülasyon - Boylam: ");
      Serial.println(gps.location.lng(), 6);
    }

    delay(2000);  // 2 saniyede bir göster
  } else {
    // Donanım varsa gerçek veriyi oku
    while (ss.available() > 0) {
      gps.encode(ss.read());

      if (gps.location.isUpdated()) {
        Serial.print("Gerçek - Enlem: ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Gerçek - Boylam: ");
        Serial.println(gps.location.lng(), 6);
      }
    }
  }
}
