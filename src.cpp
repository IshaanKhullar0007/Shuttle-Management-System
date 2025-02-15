#include<bits/stdc++.h>
using namespace std;

//Adjacency List
unordered_map<int,unordered_map<int,int>> adjList;

//Integer Mapping To Location Name
map<int,string> idxToLocationName = {
    {0,"Main Gate"},
    {1,"CSE Block"},
    {2,"Hospital"},
    {3,"Food Court"},
    {4,"Sports Complex"},
    {5,"Boys Hostel"},
    {6,"Girls Hostel"},
    {7,"Apparments"},
    {8,"Mall"},
    {9,"Biotech Block"}
};

//Student Class
class Student{
    public:
        string name;
        int age;
        string email;
        string password;
        int points = 500;
        bool block;
        vector<vector<string>> history;
        Student(){
            name = "";
            age = 0;
            email = "";
            password = "";
            block = true;
        }
        Student(string name, int age, string email, string password, bool block){
            this->name = name;
            this->age = age;
            this->email = email;
            this->password = password;
            this->block = false;
        }
        
        vector<vector<int>> shortestPath(int src, int dest){
            priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<>> pq;
            unordered_map<int, vector<vector<int>>> paths;
            unordered_map<int, vector<int>> distances;
            pq.push({0, {src}});

            while (!pq.empty()) {
                auto current = pq.top();
                pq.pop();
                
                int cost = current.first;
                vector<int> path = current.second;
                int lastNode = path.back();

                if (paths[lastNode].size() >= 3) continue;

                paths[lastNode].push_back(path);
                distances[lastNode].push_back(cost);

                if (lastNode == dest && paths[dest].size() == 3) break;

                for (auto &neighbor : adjList[lastNode]) {
                    int nextNode = neighbor.first;
                    int edgeWeight = neighbor.second;
                    
                    vector<int> newPath = path;
                    newPath.push_back(nextNode);

                    pq.push({cost + edgeWeight, newPath});
                }
            }
            return paths[dest];
        }

        void bookShuttle(Student &stu){
            while(1){
                cout<<"1. Book Shuttle\n";
                cout<<"2. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 :- ";
                cin>>choice;
                cout<<endl;

                if(choice == 1){
                    int src, dest;
                    cout<<"Choose Starting Point :\n";
                    for(auto i : idxToLocationName){
                        cout<<i.first<<"->"<<i.second<<" ";
                    }
                    cout<<endl;
                    cin>>src;
                    cout<<"Choose Destination Point :\n";
                    for(auto i : idxToLocationName){
                        cout<<i.first<<"->"<<i.second<<" ";
                    }
                    cout<<endl;
                    cin>>dest;
                    cout<<endl;
                    
                    auto ans = shortestPath(src,dest);
                    if(ans.size() == 0){
                        cout<<"No Path Exist From "<<idxToLocationName[src]<<" to "<<idxToLocationName[dest]<<endl;
                    }
                    else{
                        cout<<"Best "<<ans.size()<<" Path are :- \n";
                        int idx = 1;
                        vector<int> costArr;
                        for(auto i : ans){
                            cout<<"Route "<<idx<<": ";
                            idx++;
                            i.pop_back();
                            int cost = 0;
                            int size = i.size();
                            cout<<idxToLocationName[src]<<"->";
                            for(int j = 1 ; j < size ; j++){
                                cout<<idxToLocationName[i[j]]<<"->";
                                cost += adjList[i[j-1]][i[j]];
                            }
                            cost += adjList[dest][i.back()];
                            cout<<idxToLocationName[dest]<<", "<<cost<<" Points";
                            costArr.push_back(cost);
                            cout<<endl;
                        }
                        cout<<"Enter The Path :- ";
                        int choose;
                        cin>>choose;
                        cout<<choose;
                        cout<<endl;
                        if(choose > ans.size() || choose <= 0){
                            cout<<"Enter Valid Path";
                        }
                        else{
                            choose -= 1;
                            int points = stu.points;
                            if(points >= costArr[choose]){
                                stu.points -= costArr[choose];
                                cout<<"Shuttle is Booked From "<<idxToLocationName[src]<<" to "<<idxToLocationName[dest]<<" with cost of "<<costArr[choose]<<" Points"<<endl;
                                cout<<"Updated Balance is "<<stu.points<<" Points";
                                time_t now = time(0);
                                string timestamp = ctime(&now);
                                timestamp.pop_back();
                                stu.history.push_back({timestamp,idxToLocationName[src],idxToLocationName[dest],to_string(stu.points)});
                            }
                            else{
                                cout<<"Insufficient Balance\n";
                            }
                        }
                    }
                }
                else if(choice == 2){
                    break;
                }
                else{
                    cout<<"Enter a Valid Choice\n";
                }
                cout<<endl;
            }
        }
        
        void passwordUpdate(Student &stu){
            while(1){
                cout<<"1. Update Password\n";
                cout<<"2. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 :- ";
                cin>>choice;
                cout<<endl;
                
                if(choice == 1){
                    string newPassword = "";
                    string oldPassword = "";
                    cout<<"Enter Old Password For Validation :- ";
                    cin>>oldPassword;
                    if(oldPassword == stu.password){
                        cout<<"\nEnter New Password :- ";
                        cin>>newPassword;
                        if(newPassword == oldPassword){
                            cout<<"Old Password And New Password Shouldn't Be Same";
                        }
                        else{
                            stu.password = newPassword;
                            cout<<"Your Password Has Been Updated";
                        }
                    }
                    else{
                        cout<<"Enter Correct Old Password\n";
                    }
                }
                else if(choice == 2){
                    break;
                }
                else{
                    cout<<"Enter a Valid Choice\n";
                }
                cout<<endl;
            }
        }
        
        void addFunds(Student &stu){
            while(1){
                cout<<"1. Add Funds\n";
                cout<<"2. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 :- ";
                cin>>choice;
                cout<<endl;

                if(choice == 1){
                    int balance = stu.points;
                    if(balance < 1000){
                        cout<<"Enter the Amount From "<<1<<" to "<<1000-balance<<" :- ";
                        int amountToBeAdded;
                        cin>>amountToBeAdded;
                        cout<<endl;
                        if(amountToBeAdded >= 1 && amountToBeAdded <= 1000 - balance){
                            stu.points += amountToBeAdded;
                            cout<<"Your account updated Balance is "<<stu.points<<" Points\n";
                            cout<<"This amount is credited to your University Fees\n";
                        }
                        else{
                            cout<<"Enter The Correct Amount In The Range Given\n";
                        }
                    }
                    else
                        cout<<"You Have Sufficient Balance\n";
                }
                else if(choice == 2){
                    break;
                }
                else{
                    cout<<"Enter Correct Option";
                }
                cout<<endl;
            }
        }
        
        void knowBalance(Student &stu){
            cout<<"Your Current Balance is "<<stu.points<<" Points"<<endl;
        }

        void showBookingHistory(Student &stu){
            if (stu.history.empty()) {
                cout << "No Booking History Available.\n";
                return;
            }

            cout<<"Booking History :- "<<endl;
            for(auto i : stu.history){
                cout<<"Date & Time Of Booking :- "<<i[0]<<endl;
                cout<<"Source :- "<<i[1]<<endl;
                cout<<"Destination :- "<<i[2]<<endl;
                cout<<"Remaining Balance :- "<<i[3]<<endl;
                cout<<endl;
            }
        }
};

//Admin Class
class Admin{
    public:
        string email;
        string password;

        Admin(){
            email = "";
            password = "";
        }

        Admin(string email, string password){
            this->email = email;
            this->password = password;
        }
        
        void changesRoutes(){
            while(1){
                int src, dest;
                cout<<"1. Add Route\n";
                cout<<"2. Delete Route\n";
                cout<<"3. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 or 3 :- ";
                cin>>choice;
                cout<<endl;
                
                if(choice == 3)
                    break;
                if(choice >= 4 || choice <= 0){
                    cout<<"Make Valid Choice\n";
                    continue;
                }
                
                cout<<"Choose Source for Changing Route :\n";
                for(auto i : idxToLocationName){
                    cout<<i.first<<"->"<<i.second<<" ";
                }
                cout<<endl;
                cin>>src;
                cout<<"Choose Destination for Changing Route :\n";
                for(auto i : idxToLocationName){
                    cout<<i.first<<"->"<<i.second<<" ";
                }
                cout<<endl;
                cin>>dest;
                cout<<endl;
                auto routeIt = adjList[src].find(dest);
                if(choice == 1){
                    if(routeIt == adjList[src].end()){
                        int fare;
                        cout<<"Enter Fare for the Route :- ";
                        cin>>fare;
                        adjList[src][dest] = fare;
                        cout<<"Route from "<<idxToLocationName[src]<<" to "<<idxToLocationName[dest]<<" is Added with fare "<<fare<<" points\n";
                    }
                    else{
                        cout<<"Route Can't Be Added as route already exists\n";
                    }
                }
                else if(choice == 2){
                    if(routeIt != adjList[src].end()){
                        adjList[src].erase(dest);
                        cout<<"Route from "<<idxToLocationName[src]<<" to "<<idxToLocationName[dest]<<" is Deleted\n";
                    }
                    else{
                        cout<<"Route Can't Be Deleted as route doesn't exist\n";
                    }
                }
                cout<<endl;
            }
        }
        
        void updatePoints(unordered_map<string,Student> &mappingEmailToStudentsDetails){
            while(1){
                cout<<"1. Credits Points\n";
                cout<<"2. Debit Points\n";
                cout<<"3. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 or 3 :- ";
                cin>>choice;
                cout<<endl;

                if(choice == 3)
                    break;
                if(choice >= 4 || choice <= 0){
                    cout<<"Make Valid Choice\n";
                    continue;
                }

                string studentToBeUpdatePoints;
                cout<<"Enter Student Email Id to Update Points :- ";
                cin>>studentToBeUpdatePoints;
                auto studentIt = mappingEmailToStudentsDetails.find(studentToBeUpdatePoints);
                if(studentIt != mappingEmailToStudentsDetails.end()){
                    int oldPoint = mappingEmailToStudentsDetails[studentToBeUpdatePoints].points;
                    int newPoints;
                    cout<<"Enter the Points :- ";
                    cin>>newPoints;
                    if(choice == 1){
                        mappingEmailToStudentsDetails[studentToBeUpdatePoints].points += newPoints;
                        cout<<"Student With Email Id "<<studentToBeUpdatePoints<<" account is credit with "<<newPoints<<" Points\n";
                        cout<<"Student With Email Id "<<studentToBeUpdatePoints<<" account updated Balance is "<<mappingEmailToStudentsDetails[studentToBeUpdatePoints].points<<" Points\n";
                    }
                    else if(choice == 2){
                        mappingEmailToStudentsDetails[studentToBeUpdatePoints].points -= newPoints;
                        cout<<"Student With Email Id "<<studentToBeUpdatePoints<<" account is debit with "<<newPoints<<" Points\n";
                        cout<<"Student With Email Id "<<studentToBeUpdatePoints<<" account updated Balance is "<<mappingEmailToStudentsDetails[studentToBeUpdatePoints].points<<" Points\n";
                    }
                }
                else{
                    cout<<"Student With Email Id "<<studentToBeUpdatePoints<<" Doesn't Exist In The DataBase\n";
                }
                cout<<endl;
            }
        }

        void blockUnblockStudent(unordered_map<string,Student> &mappingEmailToStudentsDetails){
            while(1){
                cout<<"1. Block/UnBlock Student\n";
                cout<<"2. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 :- ";
                cin>>choice;
                cout<<endl;
                
                if(choice == 1){
                    string studentToBeBlocked;
                    cout<<"Enter Student Email Id to be Blocked :- ";
                    cin>>studentToBeBlocked;
                    auto studentIt = mappingEmailToStudentsDetails.find(studentToBeBlocked);
                    if(studentIt != mappingEmailToStudentsDetails.end()){
                        bool isBlocked = mappingEmailToStudentsDetails[studentToBeBlocked].block;
                        mappingEmailToStudentsDetails[studentToBeBlocked].block = !isBlocked;
                        cout<<"Student With Email Id "<<studentToBeBlocked<<" is ";
                        if(isBlocked)
                            cout<<"Unblocked\n";
                        else
                            cout<<"Blocked\n";
                    }
                    else{
                        cout<<"Student With Email Id "<<studentToBeBlocked<<" Doesn't Exist In The DataBase\n";
                    }
                }
                else if(choice == 2){
                    break;
                }
                else{
                    cout<<"Enter a Valid Choice\n";
                }
                cout<<endl;
            }
        }
        
        void changeFares(){
            while(1){
                cout<<"1. Update Fare\n";
                cout<<"2. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 :- ";
                cin>>choice;
                cout<<endl;
                if(choice == 1){
                    int src, dest;
                    int updatedFare;
                    cout<<"Choose Source for Updating Fare :\n";
                    for(auto i : idxToLocationName){
                        cout<<i.first<<"->"<<i.second<<" ";
                    }
                    cout<<endl;
                    cin>>src;
                    cout<<"Choose Destination for Updating Fare :\n";
                    for(auto i : idxToLocationName){
                        cout<<i.first<<"->"<<i.second<<" ";
                    }
                    cout<<endl;
                    cin>>dest;
                    cout<<endl;
                    if(adjList[src][dest] != 0){
                        cout<<"Enter The Fare to Be Updated :- ";
                        cin>>updatedFare;
                        cout<<endl;
                        int oldFare = adjList[src][dest];
                        adjList[src][dest] = updatedFare;
                        cout<<"Fare from "<<idxToLocationName[src]<<" to "<<idxToLocationName[dest]<<"is Updated from "<<oldFare<<" to "<<updatedFare<<endl;
                    }
                    else{
                        cout<<"Path Doesn't Exist"<<endl;
                    }
                }
                else if(choice == 2){
                    break;
                }
                else{
                    cout<<"Enter a Valid Choice\n";
                }
                cout<<endl;
            }
        }
        
        void addOrRemoveStudent(unordered_map<string,Student> &mappingEmailToStudentsDetails){
            while(1){
                cout<<"1. Add Student\n";
                cout<<"2. Remove Student\n";
                cout<<"3. Go Back\n";

                int choice;
                cout<<"\nChoice 1 or 2 or 3 :- ";
                cin>>choice;
                cout<<endl;
    
                if(choice == 1){
                        string name,email,password;
                        int age;
                        cout<<"Enter Name :- ";
                        cin>>name;
                        cout<<"Enter Age :- ";
                        cin>>age;
                        cout<<"Enter Email Id :- ";
                        cin>>email;
                        cout<<"Enter Temporary Password :- ";
                        cin>>password;
                        mappingEmailToStudentsDetails[email] = Student(name,age,email,password,false);
                }
                else if(choice == 2){
                        cout<<"Enter Email Id of Student to remove :- ";
                        string studentNameToBeDeleted;
                        cin>>studentNameToBeDeleted;
                        auto st = mappingEmailToStudentsDetails.find(studentNameToBeDeleted);
                        if(st != mappingEmailToStudentsDetails.end()){
                            mappingEmailToStudentsDetails.erase(studentNameToBeDeleted);
                            cout<<"Student With Email Id "<<studentNameToBeDeleted<<" Deleted From the DataBase\n";
                        }
                        else{
                            cout<<"Student With Email Id "<<studentNameToBeDeleted<<" doesn't Exist\n";
                        }
                }
                else if(choice == 3){
                    break;
                }
                else{
                    cout<<"Enter correct Choice\n";
                }
                cout<<endl;
            }
        }

        void showStudentDetail(unordered_map<string,Student> &mappingEmailToStudentsDetails){
            int idx = 1;
            for(auto i : mappingEmailToStudentsDetails){
                cout<<idx<<". "<<i.second.name<<" "<<i.second.age<<" "<<i.second.email<<" "<<i.second.points<<endl;
                idx++;
            }
            cout<<endl;
        }
};
    
//Mapping Email to Admin
unordered_map<string,Admin> mappingEmailToAdminDetails;

//Mapping Email to Students
unordered_map<string,Student> mappingEmailToStudentsDetails;

//Edges
vector<vector<int>> edges = {
    {0,2,4},{2,9,2},{2,8,4},{9,7,2},{8,3,10},
    {7,1,2},{1,3,3},{2,7,5},{2,1,7},{1,8,2},
    {7,6,3},{6,5,2},{5,4,2},{3,4,1},{1,6,3},
    {1,5,7},{3,4,5}
};

int main(){
    //Create Adj List
    for(auto i : edges){
        adjList[i[0]][i[1]] = i[2];
        adjList[i[1]][i[0]] = i[2];
    }

    // Initialize students and admins (example data).
    mappingEmailToStudentsDetails["ishaan@lpu.in"] = Student("Ishaan Khullar", 21, "ishaan@lpu.in", "ishaan123", false);
    mappingEmailToStudentsDetails["rahul@lpu.in"] = Student("Rahul Sharma", 22, "rahul@lpu.in", "rahul123", false);
    mappingEmailToStudentsDetails["priya@lpu.in"] = Student("Priya Mehta", 20, "priya@lpu.in", "priya123", false);
    mappingEmailToStudentsDetails["sneha@lpu.in"] = Student("Sneha Verma", 23, "sneha@lpu.in", "sneha123", false);
    
    mappingEmailToAdminDetails["admin1@lpu.in"] = Admin("admin1@lpu.in","pass123");
    mappingEmailToAdminDetails["admin2@lpu.in"] = Admin("admin2@lpu.in","pass123");

    string userName;
    string passKey;
    
    cout << "=====================================\n";
    cout << "      Welcome to Shuttle Bhuttle \n";
    cout << "=====================================\n\n";

    cout << "               LOGIN\n";
    cout << "-------------------------------------\n";
    while(1){
        cout << " Enter your University Email: ";
        cin >> userName;
    
        cout << " Enter your Password: ";
        cin >> passKey;
        auto studentIt = mappingEmailToStudentsDetails.find(userName);
        auto adminIt = mappingEmailToAdminDetails.find(userName);

        if(studentIt != mappingEmailToStudentsDetails.end()){
            if(mappingEmailToStudentsDetails[userName].password == passKey){

                cout << "\n Login Successful! Welcome, " << userName << "!\n";
                Student stu = mappingEmailToStudentsDetails[userName];

                while(1){
                    cout<<"1. Book Shuttle"<<endl;
                    cout<<"2. Add Funds"<<endl;
                    cout<<"3. Password Update"<<endl;
                    cout<<"4. Know Current Balance"<<endl;
                    cout<<"5. History Travel"<<endl;
                    cout<<"6. Logout"<<endl;
                    
                    int choice;
                    cout<<"\nEnter Choice :- ";
                    cin>>choice;
                    cout<<endl;

                    if(choice == 1){
                        if(mappingEmailToStudentsDetails[userName].block){
                            cout<<"You Have Been Blocked To Use Shuttle.\n";
                            cout<<"Contact Your Shuttle Department Admin for More Information.\n";
                        }
                        else{
                            stu.bookShuttle(mappingEmailToStudentsDetails[userName]);
                        }
                    }
                    else if(choice == 2){
                        stu.addFunds(mappingEmailToStudentsDetails[userName]);
                    }
                    else if(choice == 3){
                        stu.passwordUpdate(mappingEmailToStudentsDetails[userName]);
                    }
                    else if(choice == 4){
                        stu.knowBalance(mappingEmailToStudentsDetails[userName]);
                    }
                    else if(choice == 5){
                        stu.showBookingHistory(mappingEmailToStudentsDetails[userName]);
                    }
                    else if(choice == 6){
                        break;
                    }
                    else{
                        cout<<" Invalid Choice\n";
                    }
                }
            }
            else{
                cout<<" Incorrect Password"<<endl;
            }
        }
        else if(adminIt != mappingEmailToAdminDetails.end()){
            if(mappingEmailToAdminDetails[userName].password == passKey){
                cout << "\n Login Successful! Welcome, " << userName << "!\n";
                Admin adm = mappingEmailToAdminDetails[userName];

                while(1){
                    cout<<"1. Change(Add/Remove) Routes\n";
                    cout<<"2. Credit/Debit Points\n";
                    cout<<"3. Block/UnBlock Students\n";
                    cout<<"4. Changes Fares\n";
                    cout<<"5. Add/Remove Students\n";
                    cout<<"6. Show Students Details\n";
                    cout<<"7. Logout\n";

                    int choice;
                    cout<<"\nEnter Choice :- ";
                    cin>>choice;
                    cout<<endl;

                    if(choice == 1){
                        adm.changesRoutes();
                    }
                    else if(choice == 2){
                        adm.updatePoints(mappingEmailToStudentsDetails);
                    }
                    else if(choice == 3){
                        adm.blockUnblockStudent(mappingEmailToStudentsDetails);
                    }
                    else if(choice == 4){
                        adm.changeFares();
                    }
                    else if(choice == 5){
                        adm.addOrRemoveStudent(mappingEmailToStudentsDetails);
                    }
                    else if(choice == 6){
                        adm.showStudentDetail(mappingEmailToStudentsDetails);
                    }
                    else if(choice == 7){
                        break;
                    }
                    else{
                        cout<<" Invalid Choice\n";
                    }
                }
            }
            else{
                cout<<" Incorrect Password"<<endl;
            }
        }
        else{
            cout<<" Incorrect Email ID"<<endl;
        }
    }
}
