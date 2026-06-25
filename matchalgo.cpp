// // #include <iostream>
// // #include <fstream>
// // #include <vector>
// // #include <queue>
// // #include <sstream>
// // #include <cctype>
// // using namespace std;

// // // Ride structure
// // struct Ride {
// //     int id;
// //     string driver;
// //     string from;
// //     string to;
// //     int fare;
// //     int distance;
// //     int score;
// // };

// // // Comparator (Best-First Search)
// // struct Compare {
// //     bool operator()(Ride a, Ride b) {
// //         return a.score < b.score; // highest score first
// //     }
// // };

// // // Convert to lowercase
// // string lower(string s){
// //     for(char &c : s) c = tolower(c);
// //     return s;
// // }

// // // 🔥 Smart Matching Score
// // int calculateScore(Ride &r, string userFrom, string userTo) {

// //     int score = 0;

// //     string rf = lower(r.from);
// //     string rt = lower(r.to);
// //     string uf = lower(userFrom);
// //     string ut = lower(userTo);

// //     // ✅ Exact match (highest priority)
// //     if (rf == uf) score += 100;
// //     if (rt == ut) score += 100;

// //     // ✅ Partial match
// //     if (rf.find(uf) != string::npos) score += 40;
// //     if (rt.find(ut) != string::npos) score += 40;

// //     // ✅ Distance factor (closer is better)
// //     score += max(0, 50 - r.distance / 10);

// //     // ✅ Fare factor (cheaper is better)
// //     score += max(0, 30 - r.fare / 100);

// //     return score;
// // }

// // int main() {

// //     string path = "C:\\Users\\ranvi\\OneDrive\\Desktop\\sem2 project\\";

// //     ifstream in(path + "input.txt");
// //     ofstream out(path + "output.json");

// //     if (!in.is_open()) {
// //         cout << "Error opening input.txt";
// //         return 1;
// //     }

// //     string userFrom, userTo;
// //     in >> userFrom >> userTo;

// //     vector<Ride> rides;
// //     string line;

// //     getline(in, line); // skip first line

// //     // 🔥 Read CSV data
// //     while (getline(in, line)) {

// //         if (line.empty()) continue;

// //         stringstream ss(line);
// //         string temp;

// //         Ride r;

// //         getline(ss, temp, ','); r.id = stoi(temp);
// //         getline(ss, r.driver, ',');
// //         getline(ss, r.from, ',');
// //         getline(ss, r.to, ',');
// //         getline(ss, temp, ','); r.fare = stoi(temp);
// //         getline(ss, temp, ','); r.distance = stoi(temp); // ✅ CORRECT (from DB)

// //         // 🔥 Calculate score
// //         r.score = calculateScore(r, userFrom, userTo);

// //         rides.push_back(r);
// //     }

// //     // 🔥 Best-First Search (priority queue)
// //     priority_queue<Ride, vector<Ride>, Compare> pq;

// //     for (auto &r : rides) {
// //         pq.push(r);
// //     }

// //     vector<Ride> result;

// //     while (!pq.empty()) {
// //         result.push_back(pq.top());
// //         pq.pop();
// //     }

// //     // 🔥 JSON output
// //     out << "[";

// //     for (int i = 0; i < result.size(); i++) {
// //         out << "{";
// //         out << "\"id\":" << result[i].id << ",";
// //         out << "\"driver\":\"" << result[i].driver << "\",";
// //         out << "\"from\":\"" << result[i].from << "\",";
// //         out << "\"to\":\"" << result[i].to << "\",";
// //         out << "\"fare\":" << result[i].fare << ",";
// //         out << "\"distance\":" << result[i].distance << ",";
// //         out << "\"score\":" << result[i].score;
// //         out << "}";

// //         if (i != result.size() - 1) out << ",";
// //     }

// //     out << "]";

// //     return 0;
// // }


// #include <iostream>
// #include <vector>
// #include <queue>
// #include <sstream>
// #include <map>
// #include <climits>
// #include <cctype>
// using namespace std;

// // Ride structure
// struct Ride {
//     int id;
//     string driver;
//     string from;
//     string to;
//     int fare;
//     int distance;
//     int score;
// };

// // Comparator
// struct Compare {
//     bool operator()(Ride a, Ride b) {
//         return a.score < b.score;
//     }
// };

// // Graph
// map<string, vector<pair<string,int>>> graph;

// // 🔥 Trim function (IMPORTANT FIX)
// string trim(string s) {
//     while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
//     while (!s.empty() && (s.front() == ' ')) s.erase(s.begin());
//     return s;
// }

// // Convert to lowercase
// string lower(string s){
//     for(char &c : s) c = tolower(c);
//     return s;
// }

// // 🔥 Safe stoi
// int safe_stoi(string s) {
//     try {
//         return stoi(trim(s));
//     } catch(...) {
//         return 0;
//     }
// }

// // 🔥 Dijkstra
// int dijkstra(string start, string end) {

//     if(graph.find(start) == graph.end() || graph.find(end) == graph.end())
//         return 1000;

//     map<string,int> dist;

//     for(auto &node : graph)
//         dist[node.first] = INT_MAX;

//     priority_queue<pair<int,string>, vector<pair<int,string>>, greater<>> pq;

//     dist[start] = 0;
//     pq.push({0,start});

//     while(!pq.empty()) {

//         auto top = pq.top();
//         pq.pop();

//         int d = top.first;
//         string node = top.second;

//         for(auto &nbr : graph[node]) {

//             if(d + nbr.second < dist[nbr.first]) {
//                 dist[nbr.first] = d + nbr.second;
//                 pq.push({dist[nbr.first], nbr.first});
//             }
//         }
//     }

//     if(dist[end] == INT_MAX) return 1000;
//     return dist[end];
// }

// // 🔥 Score
// int calculateScore(Ride &r, string userFrom, string userTo) {

//     int score = 0;

//     string rf = lower(r.from);
//     string rt = lower(r.to);
//     string uf = lower(userFrom);
//     string ut = lower(userTo);

//     if (rf == uf) score += 100;
//     if (rt == ut) score += 100;

//     if (rf.find(uf) != string::npos) score += 40;
//     if (rt.find(ut) != string::npos) score += 40;

//     score += max(0, 50 - r.distance / 10);
//     score += max(0, 30 - r.fare / 100);

//     return score;
// }

// int main(int argc, char* argv[]) {

//     if (argc < 3) {
//         cout << "[]";
//         return 0;
//     }

//     string userFrom = argv[1];
//     string userTo = argv[2];

//     vector<Ride> rides;
//     string line;

//     // 🔥 Read input safely
//     while (getline(cin, line)) {

//         line = trim(line);
//         if (line.empty()) continue;

//         stringstream ss(line);
//         string temp;

//         Ride r;

//         if (!getline(ss, temp, ',')) continue;
//         r.id = safe_stoi(temp);

//         if (!getline(ss, r.driver, ',')) continue;
//         if (!getline(ss, r.from, ',')) continue;
//         if (!getline(ss, r.to, ',')) continue;

//         if (!getline(ss, temp, ',')) continue;
//         r.fare = safe_stoi(temp);

//         r.from = trim(r.from);
//         r.to = trim(r.to);

//         r.distance = 0;

//         rides.push_back(r);
//     }

//     // 🔥 Build graph
//     for(auto &r : rides) {
//         int weight = max(1, r.fare / 10);
//         graph[r.from].push_back({r.to, weight});
//         graph[r.to].push_back({r.from, weight});
//     }

//     // 🔥 Apply Dijkstra + score
//     for(auto &r : rides) {
//         r.distance = dijkstra(r.from, r.to);
//         r.score = calculateScore(r, userFrom, userTo);
//     }

//     // 🔥 Best First Search
//     priority_queue<Ride, vector<Ride>, Compare> pq;

//     for (auto &r : rides) {
//         pq.push(r);
//     }

//     vector<Ride> result;

//     while (!pq.empty()) {
//         result.push_back(pq.top());
//         pq.pop();
//     }

//     // 🔥 JSON Output
//     cout << "[";

//     for (int i = 0; i < result.size(); i++) {
//         cout << "{";
//         cout << "\"id\":" << result[i].id << ",";
//         cout << "\"driver\":\"" << result[i].driver << "\",";
//         cout << "\"from\":\"" << result[i].from << "\",";
//         cout << "\"to\":\"" << result[i].to << "\",";
//         cout << "\"fare\":" << result[i].fare << ",";
//         cout << "\"distance\":" << result[i].distance << ",";
//         cout << "\"score\":" << result[i].score;
//         cout << "}";

//         if (i != result.size() - 1) cout << ",";
//     }

//     cout << "]";

//     return 0;
// }


#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <map>
#include <climits>
#include <cctype>
using namespace std;

// Ride structure
struct Ride {
    int id;
    string driver;
    string from;
    string to;
    int fare;
    int distance;
    int seats;
    int score;
};

// Comparator
struct Compare {
    bool operator()(Ride a, Ride b) {
        return a.score < b.score;
    }
};

// Graph
map<string, vector<pair<string,int>>> graph;

// Trim
string trim(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == ' ')) s.pop_back();
    while (!s.empty() && (s.front() == ' ')) s.erase(s.begin());
    return s;
}

// Lowercase
string lower(string s){
    for(char &c : s) c = tolower(c);
    return s;
}

// Safe stoi
int safe_stoi(string s) {
    try {
        return stoi(trim(s));
    } catch(...) {
        return 0;
    }
}

// Dijkstra
int dijkstra(string start, string end) {

    if(graph.find(start) == graph.end() || graph.find(end) == graph.end())
        return 1000;

    map<string,int> dist;

    for(auto &node : graph)
        dist[node.first] = INT_MAX;

    priority_queue<pair<int,string>, vector<pair<int,string>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0,start});

    while(!pq.empty()) {

        auto top = pq.top();
        pq.pop();

        int d = top.first;
        string node = top.second;

        for(auto &nbr : graph[node]) {
            if(d + nbr.second < dist[nbr.first]) {
                dist[nbr.first] = d + nbr.second;
                pq.push({dist[nbr.first], nbr.first});
            }
        }
    }

    if(dist[end] == INT_MAX) return 1000;
    return dist[end];
}

// Score
int calculateScore(Ride &r, string userFrom, string userTo) {

    int score = 0;

    string rf = lower(r.from);
    string rt = lower(r.to);
    string uf = lower(userFrom);
    string ut = lower(userTo);

    if (rf == uf) score += 100;
    if (rt == ut) score += 100;

    if (rf.find(uf) != string::npos) score += 40;
    if (rt.find(ut) != string::npos) score += 40;

    score += max(0, 50 - r.distance / 10);
    score += max(0, 30 - r.fare / 100);

    return score;
}

int main(int argc, char* argv[]) {

    if (argc < 3) {
        cout << "[]";
        return 0;
    }

    string userFrom = argv[1];
    string userTo = argv[2];

    vector<Ride> rides;
    string line;

    //  READ INPUT SAFELY
    while (getline(cin, line)) {

        line = trim(line);
        if (line.empty()) continue;

        stringstream ss(line);
        string temp;

        Ride r;

        // ID
        if (!getline(ss, temp, ',')) continue;
        r.id = safe_stoi(temp);

        // Driver
        if (!getline(ss, r.driver, ',')) continue;

        // Source
        if (!getline(ss, r.from, ',')) continue;

        // Destination
        if (!getline(ss, r.to, ',')) continue;

        // Fare
        if (!getline(ss, temp, ',')) continue;
        r.fare = safe_stoi(temp);

        // SEATS 
        if (!getline(ss, temp, ',')) {
            r.seats = 2;   // default fallback
        } else {
            r.seats = safe_stoi(temp);
            if (r.seats <= 0) r.seats = 2;  // avoid zero bug
        }

        r.from = trim(r.from);
        r.to = trim(r.to);

        r.distance = 0;


        rides.push_back(r);
    }

    // Graph
    for(auto &r : rides) {
        int weight = max(1, r.fare / 10);
        graph[r.from].push_back({r.to, weight});
        graph[r.to].push_back({r.from, weight});
    }

    // Score
    for(auto &r : rides) {
        r.distance = dijkstra(r.from, r.to);
        r.score = calculateScore(r, userFrom, userTo);
    }

    // Priority queue
    priority_queue<Ride, vector<Ride>, Compare> pq;
    for (auto &r : rides) pq.push(r);

    vector<Ride> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }

    // JSON OUTPUT
    cout << "[";

    for (int i = 0; i < result.size(); i++) {
        cout << "{";
        cout << "\"id\":" << result[i].id << ",";
        cout << "\"driver\":\"" << result[i].driver << "\",";
        cout << "\"from\":\"" << result[i].from << "\",";
        cout << "\"to\":\"" << result[i].to << "\",";
        cout << "\"fare\":" << result[i].fare << ",";
        cout << "\"distance\":" << result[i].distance << ",";
        cout << "\"seats\":" << result[i].seats << ",";  // 
        cout << "\"score\":" << result[i].score;
        cout << "}";

        if (i != result.size() - 1) cout << ",";
    }

    cout << "]";

    return 0;
}