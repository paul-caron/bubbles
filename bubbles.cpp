/*
Author:Paul Caron
2020
*/


#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
struct circle;
using Vcircle=vector<circle>;
Vcircle bubbles(const Vcircle&);

constexpr int WIDTH=43;//console width
constexpr int BUBNUM=10;//number of bubbles per frame
constexpr int BUBMAXSIZE=15;//max size of a bubble
constexpr char chars[]=" .+o8@@@@@@@@@@";

int main() {
    srand(time(0));
    Vcircle circles;
    for(int i=0;i<50;i++) circles=bubbles(circles);
    return 0;
}





struct circle{
    const int cx;
    const int cy;
    const int r;
    circle(int cx,int cy,int r):cx(cx),cy(cy),r(r){}
};

inline Vcircle bubbles(const Vcircle &previous){
    const vector<int>row(WIDTH,0);
    vector<vector<int>>matrix(WIDTH,row);
    Vcircle circles;
    for(int i=0;i<BUBNUM;i++){
        const int r=rand()%BUBMAXSIZE+1;
        const int cx=rand()%WIDTH;
        const int cy=rand()%WIDTH+r;
        circles.emplace_back(cx,cy,r);
        for(int y=0;y<WIDTH;y++){
            for(int x=0;x<WIDTH;x++){
                const double d=round(sqrt(
                                pow(x-cx,2.0)+
                                pow(y-cy,2.0))
                               );
                if(d<r) ++matrix.at(y)
                                .at(x);
                else if(int(d)==r) matrix.at(y)
                                .at(x)+=2;
            }
        }
    }
    for(const auto& c:previous){
        for(int y=0;y<WIDTH;y++){
            for(int x=0;x<WIDTH;x++){
                const double d=round(sqrt(
                                pow(x-c.cx,2.0)+
                                pow(y-c.cy+WIDTH,2.0))
                               );
                if(d<c.r) ++matrix.at(y)
                                  .at(x);
                else if(int(d)==c.r) matrix.at(y)
                                .at(x)+=2;
            }
        }
    }
    for(const auto& row:matrix){
        for(const auto& value:row) cout<<chars[value];
        cout<<endl;
    }
    return circles;
}










