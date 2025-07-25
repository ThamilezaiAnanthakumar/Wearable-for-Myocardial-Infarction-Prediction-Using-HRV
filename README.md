
# 💓 Wearable for Myocardial Infarction Prediction Using HRV

A compact wearable device that predicts **Myocardial Infarction (MI)** using **Heart Rate Variability (HRV)** extracted from **PPG signals** instead of ECG. Built on **ESP32-S3-WROOM-N16R8**, it runs a neural network model at the edge and gives **real-time LED alerts** based on MI prediction.

---

## 🩺 Why HRV Instead of ECG?

* HRV changes **before ECG abnormalities appear**.
* PPG is **non-invasive**, low-power, and **wearable-friendly**.
* Suitable for **early MI detection** from subtle autonomic signals.

---

## 🧠 ML Pipeline Overview

* **91 HRV features** extracted using [NeuroKit2](https://neurokit2.readthedocs.io/).
* Top **4 parameters** selected.
* **Neural Network model** trained and converted to TensorFlow Lite.
* Achieved **96.32% accuracy**.
* Deployed on ESP32-S3 and used for **on-device inference**.

---

## 💡 LED Indication Logic

| LED Color | Meaning              |
| --------- | -------------------- |
| 🔴 Red    | MI Risk Detected     |
| 🟢 Green  | Normal HRV / No Risk |

---

## 🧾 Hardware Used

* **ESP32-S3-WROOM-N16R8** (AI-capable MCU)
* **MAX30102** PPG sensor
* **RGB LED**
* Onboard regulator, USB-C interface

---

## 🖼️ PCB Design

<p align="center">
  <img src="https://github.com/ThamilezaiAnanthakumar/Wearable-for-Myocardial-Infarction-Prediction-Using-HRV/main/Assets/PCB.jpg" width="600" alt="PCB Preview"/>
</p>

