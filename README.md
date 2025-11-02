# 🏥 Medi-Assist

## 📌 Overview
The **Medi-Assist** is a C-based console application designed to efficiently manage patients in a hospital.  
It uses **Queue** and **Heap (Priority Queue)** data structures to organize patients based on their condition (Normal or Emergency).  
The system also includes doctor assignment, discharge management, record updating, and file handling for data persistence.

---

## 🎯 Objectives
- To automate patient registration and queuing.
- To assign doctors dynamically based on diseases and specializations.
- To manage emergency patients using a **priority heap**.
- To allow discharge and update of patient records.
- To maintain persistent data through file handling.

---

## 🧠 Key Features
1. **Patient Registration**
   - Add new patients to either the normal or emergency queue.
   - Automatically calculates patient priority based on severity, age, and emergency level.

2. **Emergency Queue (Heap)**
   - Emergency patients are stored in a **max-heap** based on priority.
   - Highest-priority patients are attended first.

3. **Doctor Assignment**
   - Assigns doctors based on disease type from the `disease_map.txt` file.
   - Each doctor can handle up to 3 patients at a time.

4. **Patient Discharge**
   - Discharge patients from a doctor’s waiting list.
   - Automatically shifts the remaining patients forward.

5. **Update Patient Information**
   - Modify patient details in both normal and emergency queues.

6. **File Handling**
   - Patients and doctors are stored in text files:
     - `patients.txt` → Contains all patient data.
     - `doctors.txt` → Stores doctor details.
     - `disease_map.txt` → Maps diseases to their respective specialists.
   - Data is loaded automatically at program startup.

7. **Data Persistence**
   - Saves all records before exiting.
   - Loads previous data when the program restarts.

---

## 🧩 Data Structures Used
| Structure | Description |
|------------|-------------|
| **Queue (Linked List)** | Handles normal patients in FIFO order. |
| **Heap (Array-based)** | Manages emergency patients based on calculated priority. |
| **Struct** | Used for storing patient, doctor, and allocation mapping details. |

---

## 📂 File Descriptions

### 1. `patients.txt`
Stores details of all registered patients.
```
<ID>|<Name>|<Age>|<Disease>|<Emergency>|<Severity>|<Priority>
```

### 2. `doctors.txt`
Stores information of doctors.
```
<Name>|<Specialization>|<Available>|<Count>
```

### 3. `disease_map.txt`
Maps diseases to doctors.
```
cough,General Physician
cold,General Physician
fever,General Physician
sore throat,General Physician
fracture,Orthopedic
joint pain,Orthopedic
chest pain,Cardiologist
heart pain,Cardiologist
rashes,Dermatologist
allergy,Dermatologist
stomach pain,Gastroenterologist
food poisoning,Gastroenterologist
```

---

## 🖥️ Menu Options

| Option | Functionality |
|--------|----------------|
| 1 | Register a new patient |
| 2 | View all normal patients |
| 3 | View all emergency patients |
| 4 | Assign doctor to patients |
| 5 | View all doctors |
| 6 | Discharge a patient |
| 7 | Update patient details |
| 8 | Save all data |
| 9 | Exit program |

---

## 🧮 Priority Calculation Formula
```
Priority = (Emergency * 0.50) + (Severity * 0.30) + ((Age / 100) * 0.20)
```
Higher priority patients are served first.

---

## 📊 Expected Output Example

### Register Patient
```
Enter Patient ID: 101
Enter Patient Name: Rohan Sharma
Enter Age: 45
Enter Disease: fever
Is it an emergency? (1 for Yes / 0 for No): 1
Enter Severity Level (1-10): 8
Patient Registered Successfully!
Priority: 7.96
```

### Assign Doctor
```
Patient Rohan Sharma (ID=101) added to Dr. Mehta waiting list.
```

### Discharge Patient
```
Enter Patient ID to discharge: 101
Patient Rohan Sharma discharged from Dr. Mehta (General Physician)
✅ Discharge successful!
```

---

## ⚙️ File Handling Workflow
- On startup → loads patients and doctors from respective files.  
- On every registration → appends to `patients.txt`.  
- On exit → rewrites both `patients.txt` and `doctors.txt`.

---

## 💡 Advantages
- Efficient handling of emergency and normal patients.
- Persistent storage ensures no data loss.
- Dynamic mapping between disease and doctor.
- Modular code with clear structure.
- Realistic hospital management simulation.

---

## 🧾 References
- C Programming Tutorials – GeeksforGeeks, TutorialsPoint  
- Data Structures (Queue, Heap) – NPTEL, Javatpoint  
- Real-world hospital management logic inspired by MedAssist systems.

---

## 🛠️ Compilation
To compile and run the program:
```bash
gcc hospital_queue.c -o hospital_queue
./hospital_queue
```

---

## 📘 License
This project is created for educational purposes.  
Free to use, modify, and distribute with proper credit.
