import cv2
import numpy as np
import serial
import time

# Inisialisasi koneksi ke Arduino
arduino = serial.Serial('COM3', 9600)
time.sleep(2)

warna_config = {
    "Hijau": {
        "ranges": [([36, 100, 100], [85, 255, 255])],
        "color": (0, 255, 0)
    }
}

state = "idle"
sortir_timer = 0
sortir_durasi = 2  # durasi tunggu sebelum conveyor lanjut

# Awal: conveyor jalan
arduino.write(b"cw\n")
print(">> Conveyor mulai jalan")

def deteksi_warna(frame_hsv, frame_output, warna_nama, data):
    mask_total = None
    for lower, upper in data["ranges"]:
        mask = cv2.inRange(frame_hsv, np.array(lower), np.array(upper))
        mask_total = mask if mask_total is None else mask_total | mask

    contours, _ = cv2.findContours(mask_total, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    objek_terdeteksi = False

    for cnt in contours:
        if cv2.contourArea(cnt) > 500:
            x, y, w, h = cv2.boundingRect(cnt)
            cv2.rectangle(frame_output, (x, y), (x + w, y + h), data["color"], 2)
            cv2.putText(frame_output, warna_nama, (x, y - 10),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.6, data["color"], 2)
            objek_terdeteksi = True
            break
    return objek_terdeteksi

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
if not cap.isOpened():
    print("Kamera tidak terbuka.")
    exit()

while True:
    ret, frame = cap.read()
    if not ret:
        break

    frame = cv2.resize(frame, (320, 240))  # ukuran kecil untuk kecepatan
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    objek_hijau = deteksi_warna(hsv, frame, "Hijau", warna_config["Hijau"])
    now = time.time()

    if objek_hijau and state == "idle":
        print(">> Deteksi hijau! Kirim ss (stop + sortir)")
        arduino.write(b"ss\n")
        sortir_timer = now
        state = "sortir"

    elif state == "sortir" and (now - sortir_timer > sortir_durasi):
        arduino.write(b"cw\n")
        print(">> Conveyor lanjut")
        state = "idle"

    cv2.imshow("Deteksi Warna Hijau", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
