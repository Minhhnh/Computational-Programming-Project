#include<iostream> 
#include<vector> 
#include<algorithm>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<graphics.h>
#include <string>
using namespace std;
#define M  10000001

// Ham nay dung de in ra tieu de
void tieude();

// Ham nay dung de chon test
string chontest();

// Ham nay dung de doc du lieu vao tu file
// str: ten file
// n: so luong thanh pho
// Ham tra ve mot vector hai chieu chua toa do cua cac thanh pho
vector<vector<int>> refile(string str2,int &n);

// Ham nay dung de tinh toan khoang cach giua cac thanh pho
// A: vector hai chieu luu tru toa do cua cac thanh pho
// n: so luong thanh pho
// Ham tra ve mot vector hai chieu chua khoang cach giua cac thanh pho 
vector<vector<double>> distance(const vector<vector<int>> &A, int n);

// Ham nay dung de tinh khoang cach giua hai diem
// A: vector chua toa do cua diem dau tien
// B: vector chua toa do cua diem thu hai
// Ham tra ve mot gia tri thuc la khoang cach giua hai diem
double caldistance(const vector<int> &A,const vector<int> &B);

// Ham nay dung de tim thanh pho co key nho nhat
// key: mamg 1 chieu chua gia tri key cua cac thanh pho
// mstSet: mang 1 chieu dung de theo doi cac dinh da duoc them vao MST
// n: so luong thanh pho 
// Ham tra ve mot gia tri nguyen la so thu tu cua thanh pho co key nho nhat    
int minKey(double key[], bool mstSet[], int n);    

// Ham nay dung de tim ra cay khung be nhat
// Cities: vector hai chieu chua khoang cach giua cac thanh pho 
// n: so luong thanh pho 
vector<vector<int> > primMST(const vector<vector<double> >& Cities, int n);

// Ham nay dung de duyet cay theo kieu tien to va luu lai cac dinh da di qua
// path: vector dung de luu cac dinh
// Tree: vector hai chieu bieu dien MST
// k: bien phuc vu cho viec duyet cay
void PreoderTraversal(vector<int> &path, const vector<vector<int> >& Tree, int k);

// Ham nay dung de tinh toan do dai cua duong di
// gnome: vector chua duong di
// Cities: vector hai chieu chua khoang cach giua cac thanh pho
// Ham tra ve mot gia tri thuc la do dai cua duong di chua trong gnome
double cal_fitness(const vector<int> &gnome, const vector<vector<double> >& Cities);
 
// Ham nay dung de in ket qua ra man hinh va ve do thi mieu ta qua trinh di chuyen
// A: vector hai chieu luu tru toa do cua cac thanh ph
// path: vector chua duong di ngan nhat
// result: do dai duong di ngan nhat
// n: so luong thanh pho  
void show(const vector<vector<int>>&A, vector<int>&path, double result,int n);

// Ham nay dung de ghi duong di ngan nhat vao file
// str: dung de tao ten file
// path: vector chua duong di ngan nhat
// result: do dai duong di ngan nhat
// n: so luong thanh pho
void wrfile(string str,const vector<int>&path, double result,int n);
  
int main(){  
	
	srand(time(NULL));
	cout << fixed << setprecision(2);
	int i,j,n;
	double result;
	vector<vector<int>> A(1000,vector<int>(2));
	string str;
	str = chontest();
	A = refile(str,n);
	vector<vector<double> > Cities(n,vector<double>(n));
	Cities = distance(A,n);
	vector<vector<int> > Tree(n);
	vector<int> path;
    Tree = primMST(Cities,n);  
    PreoderTraversal(path,Tree,0);
    path.push_back(0);
	result = cal_fitness(path,Cities);
	wrfile(str,path,result,n);
	show(A,path,result,n);
  
    return 0;  
}  

void tieude(){
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

vector<vector<int>> refile(string str2,int &n){
	ifstream F;
	string str1;
	str1 += "D:\\Do_an_LTTT\\PROJECT\\Test\\test";
	str1 += str2;
	str1 += ".txt";
	F.open(str1);
	int i,a,b;
	vector<vector<int>> A(1000,vector<int>(2));
	string str;
	getline(F,str);
	n = stoi(str);
	for(i=0;i<n;i++){
		getline(F,str,' ');
		a = stoi(str);
		getline(F,str);
		b = stoi(str);
		A[i][0] = a;
		A[i][1] = b;
	}
	F.close();
	return A;
}

vector<vector<double>> distance(const vector<vector<int>> &A, int n){
	vector<vector<double>> Cities(n,vector<double>(n));
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			Cities[i][j] = Cities[j][i] = caldistance(A[i],A[j]);
		}
	}
	return Cities;
}

double caldistance(const vector<int> &A,const vector<int> &B){
	return sqrt((A[0]-B[0])*(A[0]-B[0])+(A[1]-B[1])*(A[1]-B[1]));
}

int minKey(double key[], bool mstSet[], int n){  
    int min_index; 
	double min = M; 
    for (int v = 0; v < n; v++)  
        if (mstSet[v] == false && key[v] < min)  
            min = key[v], min_index = v;  
    return min_index;  
}

vector<vector<int> > primMST(const vector<vector<double> >& Cities, int n)  {    
	int parent[n];    
    double key[n];  
    bool mstSet[n];  
    vector<vector<int> > Tree(n);
    for (int i = 0; i < n; i++)  
        key[i] = M-1, mstSet[i] = false;  
   
    key[0] = 0;  
    parent[0] = -1; 
    
	for (int count = 0; count < n - 1; count++) {  
        int u = minKey(key, mstSet,n);  
        mstSet[u] = true;  
        for (int v = 0; v < n; v++)  
            if (Cities[u][v] && mstSet[v] == false && Cities[u][v] < key[v])  
                parent[v] = u, key[v] = Cities[u][v];  
    }
	
	for(int i = 1; i<n; i++){
		Tree[parent[i]].push_back(i);
	}
	return Tree;    
}

void PreoderTraversal(vector<int> &path, const vector<vector<int> >& Tree, int k){
	int i,size = Tree[k].size();
	path.push_back(k);
	if(size){
		for(i=0;i<size;i++){
			PreoderTraversal(path,Tree,Tree[k][i]);
		}
	}
} 

double cal_fitness(const vector<int> &gnome, const vector<vector<double> >& Cities) { 
    double f = 0; 
    for (int i = 0; i < gnome.size() - 1; i++) { 
        f += Cities[gnome[i]][gnome[i + 1]]; 
    } 
    return f; 
}

void show(const vector<vector<int>>&A, vector<int>&path, double result, int n){
	int i,tam;
	char ch[10];
	cout<<"So thanh pho:"<<n<<endl;
	cout<<endl;
	cout<<"Toa do vi tri cua cac thanh pho"<<endl;
	for(i=0;i<n;i++) {
		cout<<"Thanh pho "<<i<<": ( "<<A[i][0]<<" ; "<<A[i][1]<<" )"<<endl;
	}
	cout<<endl;
	cout<<"Duong di voi tong khoang cach nho nhat qua tat ca cac thanh pho:"<<endl;
	for(i=0;i<n;i++) {
		cout<<path[i]<<"->";
	}
	cout<<path[n]<<endl;
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
		circle(A[i][0]+100,600-A[i][1],3);
	}
	
	for(i=0;i<n;i++){
		line(A[path[i]][0]+100,600-A[path[i]][1],A[path[i+1]][0]+100,600-A[path[i+1]][1]);
		delay(20);
	}
	
	getch();
    closegraph();
	
}

void wrfile(string str,const vector<int>&path, double result,int n){
	ofstream F;
	int i;
	string str1;
	str1 += "D:\\Do_an_LTTT\\PROJECT\\Solution_mst\\sol";
	str1 += str;
	str1 += ".txt";
	F.open(str1);

	F<<"Duong di voi tong khoang cach nho nhat qua tat ca cac thanh pho:"<<endl;
	for(i=0;i<n;i++) {
		F<<path[i]<<"->";
	}
	F<<path[n]<<endl;
	F<<endl;
	F<<"Do dai doan duong di:";
	F<<result<<endl;
	
	F.close();
}
