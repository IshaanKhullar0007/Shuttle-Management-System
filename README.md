# Shuttle-Management-System
# 🚌 Shuttle Bhuttle - University Shuttle Booking System

**A C++ based shuttle management system for efficient campus transportation!**  

## 🚀 Features

### 👨🎓 **Student Features**
- **Book Shuttle**: Find the 3 shortest paths between locations with fare calculation.
- **Add Funds**: Top up points (max balance: 1000 points).
- **Password Update**: Secure password change functionality.
- **Balance Check**: View current points.
- **Travel History**: Track bookings with timestamps, routes, and balances.
- **Account Security**: Block/unblock mechanism for suspicious activity.

### 👨💼 **Admin Features**
- **Route Management**: Add/remove routes and update fares.
- **Student Management**: Add/remove students, block/unblock accounts.
- **Points Control**: Credit/debit student points manually.
- **View All Students**: Access student details (name, email, balance).

## 🛠️ Technologies Used
- **C++17** 
- **STL Libraries**: 
  - `unordered_map` for O(1) user lookups
  - `priority_queue` for Dijkstra's algorithm
  - `vector` for dynamic data storage
- **Graph Theory**: Bidirectional weighted graph for route management

## 📊 Data Structures & Algorithms
- **Adjacency List**: Stores locations and fares (`adjList[src][dest] = points`)
- **Dijkstra's Algorithm**: Modified to find **top 3 shortest paths** using:
  ```cpp
  priority_queue<pair<int, vector<int>>, ..., greater<>> pq;

## 🏫 Predefined Locations
0: Main Gate        
1: CSE Block        
2: Hospital         
3: Food Court       
4: Sports Complex   
5: Boys Hostel            
6: Girls Hostel       
7: Apparments       
8: Mall          
9: Biotech Block           

![Shuttle Service](https://media-hosting.imagekit.io//12b7a560a8924938/Screenshot%202025-02-15%20175950.png?Expires=1834262684&Key-Pair-Id=K2ZIVPTIP2VGHC&Signature=CtZjCSKsyROwTTz2Nk8gRk870pxLYEgXLoiOKemUIVrY7~3q1VgMbdMH67MgFUMEKo57iCtRN-VXwN2ytIfxr-WMqPzysoSMZ0TpGAjaaASsqtOKJkv~-gUzaWo8rwj0pTaFjQthVQNLMgWuGgOmvlH8JwUJo~SWCmWu0uh8B4GtayHaLb~ncrG03R6Qqk9y2vpPczKzCh1tGukWLofUowgOmshZjyIx1e1Mi3H0ecNfuDzW5LnX0NQrc-07~L9TIBXX1whmKKhjWJUZEPbjGzqIxAFtuMmafUsWP5yQtQqVUivPixiQhS78mJdHNHhk3AeLgdjt8gLPTIKv~~-s4Q__)

🌟 Special Features
Multi-Path Routing: Shows top 3 cheapest routes

Point System:

Base balance: 500 points

Fare example: Main Gate → Hospital → Biotech Block (4 + 2 = 6 points)

Time-Stamped History

📄 License
MIT License. Feel free to modify and use for educational purposes.

⭐ Star this repo if you found it useful!
Contribute by reporting issues or suggesting improvements.
