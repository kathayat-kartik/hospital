# 🏥 Medi Assist  (C Project)

## 📘 Overview

**Medi Assist** is implemented in **C language**, designed to streamline patient registration, doctor assignment, and emergency case management.  
It enables hospitals to efficiently manage incoming patients, assign doctors automatically based on disease specialization, and maintain patient and doctor data persistently through file handling.

This project demonstrates the use of **linked lists**, **file I/O**, **data structures**, **modular programming**, and **string processing** in C.

---

## 🎯 Objectives

- To efficiently manage patient queues in hospitals.
- To automatically assign doctors based on disease specialization.
- To handle both normal and emergency patient cases.
- To store and retrieve data using file handling.
- To update and discharge patients effectively.
- To reduce manual administrative workload.

---

## ⚙️ Features Implemented

1. **Patient Registration**
2. **View Patients**
3. **View Emergency Patients**
4. **Assign Doctor to Patient**
5. **Doctor Management**
6. **Update or Discharge Patient**
7. **View Assigned Doctors**
8. **File Handling**
9. **Cross-Platform Support**

---

## 🧩 Data Structures Used

### Doctor Structure
```c
typedef struct Doctor {
    int id;
    char name[50];
    char specialization[50];
    char diseases[200];
    struct Doctor *next;
} Doctor;
```

### Patient Structure
```c
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int emergency;
    int severity;
    char assignedDoctor[50];
    struct Patient *next;
} Patient;
```

---

## 📁 File Management

### `doctors.txt`
```
---------------------------------------------
Doctor ID        : 1
Name             : Dr. Meena Sharma
Specialization   : Cardiologist
Diseases Treated : Heart Disease, Hypertension
---------------------------------------------
```

### `patients.txt`
```
---------------------------------------------
Patient ID     : 1
Name           : Rajesh Kumar
Age            : 42
Disease        : Heart Disease
Emergency Case : Yes
Severity Level : 8
Assigned Doctor: Dr. Meena Sharma
---------------------------------------------
```

---

## 🚀 How to Run

```bash
gcc hospital_queue.c -o hospital_queue
./hospital_queue
```

---

## 💡 Advantages

- Modular and easy-to-understand C code.
- Uses **linked lists** for dynamic memory allocation.
- Portable across operating systems.
- Persistent storage with file handling.
- Can be extended to integrate database or GUI.

---

## 🔍 Scope for Improvement

1. Add doctor and patient search functionality.
2. Introduce priority queue based on severity and emergency.
3. Integrate database (MySQL or SQLite) instead of text files.
4. Build GUI or web-based version.
5. Add authentication and analytics.

---

## 📚 References

- *Let Us C* by Yashavant Kanetkar  
- *Programming in ANSI C* by E. Balagurusamy  
- [https://en.cppreference.com/w/c](https://en.cppreference.com/w/c)  
- [https://www.geeksforgeeks.org](https://www.geeksforgeeks.org)
