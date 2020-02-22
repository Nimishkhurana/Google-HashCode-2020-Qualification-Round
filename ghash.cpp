#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(i=a;i<b;i++)
#define rrep(i,b,a) for(i=b;i>=a;i--)
#define ld long double
#define ll long long
#define pb push_back
 
char INPUT_FILE[] = "b_read_on.txt";
char OUTPUT_FILE[] = "b_read_on_output.txt";

int B,L,D;
 
bool comparator(pair<int,int> l, pair<int, int> r) {
   return l.second>r.second;
}
 
class Library {
   public:
     int numBooks,signupDays,maxOneDayScan;
     bool signedUP;
     vector<pair<int,int>> ids;
     Library(int numBooks, int signupDays, int maxOneDayScan, vector<pair<int,int>> ids) { // id,score
         this->numBooks= numBooks;
         this->signupDays = signupDays;
         this->maxOneDayScan = maxOneDayScan;
         sort(ids.begin(), ids.end(), comparator);
         this->ids = ids;
         this->signedUP = false;
     }
};

unordered_set<int> usedBooks;
vector<Library> libraries;
vector<pair<int,int>> res1;
vector<vector<int> >res2;
const int MAX = 1e5 + 1;
bool signedUp[MAX];

bool signupLibrary(int ind, int curr_day){
    Library lib = libraries[ind];
    int num = 0;
    int mx = (D - (curr_day + lib.signupDays))* lib.maxOneDayScan; 
    int i;
    vector<int> books;
    signedUp[ind] = true;
    
    for(auto book: lib.ids){
        if(num >= mx)
            break;
        if(!usedBooks.count(book.first)){
            books.pb(book.first);
            usedBooks.insert(book.first);
            num++;
        }
    }
    if(num > 0){
        res1.pb(make_pair(ind, num));
        res2.pb(books);
        return true;
    }
    else
        return false;
    
}

int libraryScore(int ind, int curr_day){
    Library lib = libraries[ind];
    int num = 0;
    int mx = (D - (curr_day + lib.signupDays))* lib.maxOneDayScan;
    if(mx < 0) return INT_MIN; 
    int i;
    int res = 0;
    for(auto book: lib.ids){
        if(num > mx)
            break;
        if(!usedBooks.count(book.first)){
            res += book.second;
            num++;
        }
    }
    return res;
}
 
void calculate() { 
    int i, curr_day = 0;
    int num_libraries = 0;
    while(curr_day < D){
        int max_score = INT_MIN, score, lib_ind = -1;
        rep(i,0,(int)libraries.size()){
            if(signedUp[i] == true)
                continue;
            
            score = libraryScore(i, curr_day);
            if(max_score < score){
                max_score = score;
                lib_ind = i;
            }
        }

        if(lib_ind == -1) break;
        num_libraries += signupLibrary(lib_ind, curr_day);
        curr_day += libraries[lib_ind].signupDays;  
    }

    cout<<num_libraries<<endl;
    assert(num_libraries == (int)res1.size() && num_libraries == (int)res2.size());
    int j;
    rep(i,0,num_libraries){
        cout<<res1[i].first<<" "<<res1[i].second<<endl;
        assert(res1[i].second == (int)res2[i].size());
        rep(j,0,(int)res2[i].size()){
            cout<<res2[i][j]<<" ";
        }
        cout<<endl;
    }   
}
 
int main() {
   freopen(INPUT_FILE, "r", stdin);
   freopen(OUTPUT_FILE, "w", stdout);
   unordered_map<int,int> scores;
   cin>>B>>L>>D;
   int i, j, score;
   rep(i,0,B){
       cin>>score;
       scores[i] = score;
   }
   
   int numBooks,signupDays,maxOneDayScan, id;
   rep(i,0,L){
       cin>>numBooks>>signupDays>>maxOneDayScan;
       vector<pair<int,int>> id_score;
        rep(j,0,numBooks){
            cin>>id;
            id_score.push_back({id, scores[id]});
        }
        Library lib(numBooks,signupDays,maxOneDayScan,id_score);
        libraries.pb(lib);
   }
     calculate();
}