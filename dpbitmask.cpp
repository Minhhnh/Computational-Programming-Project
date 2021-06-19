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
ll dp[21][1<<21];
ll dist[21][21];
ll x[21],y[21];
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
    int i,a,b;
    string str;
    getline(F,str);
    n = stoi(str);
    for(i=0;i<n;i++){
        getline(F,str,' ');
        a = stoi(str);
        getline(F,str);
        b = stoi(str);
        x[i] = a;
        y[i] = b;
    }
    F.close();
}
ll solve(ll i, ll set){
	//Input:
	//i: dinh dang xet
	//set: bieu dien tap hop
	//dp[i][set]: Chi phi nho nhat den dinh thu i trong tap hop set
	if (set==((1<<n)-1)) return dist[i][0];//tat ca cac dinh da duoc xet
	if (dp[i][set] != -1){
		return dp[i][set];//tra ve ket qua da luu
	}
	ll ans=1e9+7;
	for (ll j=0;j<n;j++){
		if (j!=i && !(set & (1<<j))){//neu dinh thu j chua nam trong tap hop dang xet
			ans=min(ans,dist[i][j] + solve(j,(set|(1<<j))));//them dinh thu j vao tap hop va xet tap hop con lai
		}
	}
	return dp[i][set]=ans;//luu lai ket qua de giam do phuc tap tinh toan
}

int main(){
	string testnum=chontest();
	refile(testnum,n);
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	memset(dp,-1,sizeof(dp));
	for (ll i=0;i<n;i++){
		for (ll j=0;j<n;j++){
			dist[i][j]=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
	cout<<solve(0,0);
	return 0;
}

