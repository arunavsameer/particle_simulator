#include <bits/stdc++.h>
using namespace std;

pair<float, float> A = make_pair(5, 5);
pair<float, float> B = make_pair(3, 4);

float distance(pair<float, float> A, pair<float, float> B){
    float dist = (A.first - B.first)*(A.first - B.first) + (A.second - B.second)*(A.second - B.second);
    return sqrt(dist);
}

int main(){
    cout << distance(A, B);
}