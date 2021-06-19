#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <graphics.h>
#include <fstream>
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define maxN 5000

struct Point{
	double x,y;
	Point(double x=0, double y=0)
		:x(x),y(y)
	{}
	Point operator - (Point &p){
		return Point(x-p.x,y-p.y);
	}
	double len(){
		return sqrt(x*x+y*y);
	}
} a[maxN];

bool vis[maxN];
int pos[maxN];
int n;

void tieude(){
	// Ham nay dung de in ra tieu de
    cout<<"**********************************************************************************************************************"<<endl;
    cout<<"*                                             DO AN LAP TRINH TINH TOAN                                              *"<<endl;
    cout<<"*                                 DE TAI: LAP TRINH GIAI QUYET BAI TOAN NGUOI DU LICH                                *"<<endl;
    cout<<"*                                        GIANG VIEN HUONG DAN: HUYNH HUU HUNG                                        *"<<endl;
    cout<<"*                                         SINH VIEN THUC HIEN: PHAM NGOC HIEU-19TCLCNHAT2                            *"<<endl;
    cout<<"*                                                              HO NGOC HOANG MINH-19TCLCNHAT1                        *"<<endl;
    cout<<"**********************************************************************************************************************"<<endl;
    cout<<endl;
}

 

string chontest(){
	// Ham nay dung de chon test
    string str;
    int i;
    do{
        system("cls");
        tieude();
        cout<<"Moi ban chon file text(Nhap mot so trong khoang 0-18): ";
        cin>>i;
    } while(i<0||i>18);
    cout<<endl;
    str = to_string(i);
    return str;
}

void refile(string str2,int &n){
	// Ham nay dung de doc du lieu vao tu file
	// str2: ten file
	// n: so luong thanh pho
    ifstream F;
    string str1;
    str1 += "D:\\Do_an_LTTT\\PROJECT\\Test\\test";
    str1 += str2;
    str1 += ".txt";
    F.open(str1);
    int i,x,y;
    string str;
    getline(F,str);
    n = stoi(str);
    for(i=0;i<n;i++){
        getline(F,str,' ');
        x = stoi(str);
        getline(F,str);
        y = stoi(str);
        a[i+1].x = x;
        a[i+1].y = y;
    }
    F.close();
}

void show(const Point *a, int *pos, double result, int n){
	// Ham nay dung de in ket qua ra man hinh va ve do thi mieu ta qua trinh di chuyen
	// a: mang cac Point luu tru toa do cua cac thanh pho
	// path: mang chua duong di ngan nhat
	// result: do dai duong di ngan nhat
	// n: so luong thanh pho  
    int i,tam;
    char ch[10];
    cout<<"So thanh pho: "<<n<<endl<<endl;
    cout<<"Toa do vi tri cua cac thanh pho"<<endl;
    for(i=0;i<n;i++) {
        cout<<"Thanh pho "<<i<<": ( "<<a[i+1].x<<" ; "<<a[i+1].y<<" )"<<endl;
    }
    cout<<endl;
    cout<<"Duong di voi tong khoang cach nho nhat qua tat ca cac thanh pho:"<<endl;
    for(i=0;i<n;i++) {
        cout<<pos[i+1]<<"->";
    }
    cout<<pos[n+1]<<endl;
    cout<<endl;
    cout<<"Do dai doan duong di:";
    cout<<result<<endl;
    initwindow(700,700);
    line(100,50,100,600);
    line(95,55,100,50);
    line(105,55,100,50);
    outtextxy(85,50,"x");
    line(100,600,650,600);
    line(645,595,650,600);
    line(645,605,650,600);
    outtextxy(660,600,"y");
    outtextxy(90,610,"O");
    for(i=1;i<=5;i++){
        tam = i*100;
        itoa(tam,ch,10);
        outtextxy((i+1)*100,610,ch);
        outtextxy(50,600-i*100,ch);
    }
    for(i=0;i<n;i++){
        circle(a[i+1].x+100,600-a[i+1].y,3);
    }
    for(i=0;i<n;i++){
        line(a[pos[i+1]].x+100,600-a[pos[i+1]].y,a[pos[i+2]].x+100,600-a[pos[i+2]].y);
        delay(20);
    }
    getch();
    closegraph();
}

void wrfile(string str,int *path, double result,int n){
	// Ham nay dung de ghi duong di ngan nhat vao file
	// str: dung de tao ten file
	// path: vector chua duong di ngan nhat
	// result: do dai duong di ngan nhat
	// n: so luong thanh pho
    ofstream F;
    int i;
    string str1;
    str1 += "D:\\Do_an_LTTT\\PROJECT\\Soluton_greedy\\sol";
    str1 += str;
    str1 += ".txt";
    F.open(str1);

    F<<"Duong di voi tong khoang cach nho nhat qua tat ca cac thanh pho:"<<endl;
    for(i=0;i<n;i++) {
        F<<path[i+1]<<"->";
    }
    F<<path[n+1]<<endl;
    F<<endl;
    F<<"Do dai doan duong di:";
    F<<result<<endl;
    
    F.close();
}

void TSPGreedy(){
	//Ham nay tim chu trinh su dung thuat toan greedy
	vis[1]=true;
	pos[1]=1;
	for (int i=2;i<=n;i++){
		double maxDist = 1e9+7;
		int posTemp = -1;
		for (int j=1;j<=n;j++){
			double curDist = (a[pos[i-1]]-a[j]).len();
			if (!vis[j] && curDist<maxDist){
				maxDist=curDist;
				posTemp=j;
			}
		}
		pos[i]=posTemp;
		vis[posTemp]=true;
	}
}
void optimize() {
	//Ham nay dung de toi uu chu trinh
    while (true) {
        bool stop = true;
        for(int u = 2; u <= n+1; ++u) {
            for(int v = n; v > u; --v) {
                double t1 = (a[pos[u-1]] - a[pos[u]]).len()
                        + (a[pos[v]] - a[pos[v+1]]).len();
                double t2 = (a[pos[u-1]] - a[pos[v]]).len()
                        + (a[pos[u]] - a[pos[v+1]]).len();
                if (t1 > t2) {
                    for(int i = u, j = v; i <= j; ++i, --j) {
                        swap(pos[i], pos[j]);
                    }
                    stop = false;
                }
            }
        }
        if (stop) break;
    }
}

int main(){
	string testnum=chontest();
	refile(testnum,n);
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	pos[n+1]=1;
	TSPGreedy();
	double sum2=0;
	optimize();
	sum2=0;
	for (int i=1;i<n;i++){
		sum2+=(a[pos[i+1]] - a[pos[i]]).len();
	}
	sum2+=(a[pos[n]] - a[pos[1]]).len();
	wrfile(testnum,pos,sum2,n);
	show(a,pos,sum2,n);
	cout<<fixed<<setprecision(2);
	cout<<sum2;
	return 0;
}


