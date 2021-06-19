#include<iostream> 
#include<vector> 
#include<algorithm>
#include<time.h>
#include<iomanip>
#include<fstream>
#include<graphics.h>
#include <string>
using namespace std;   

// Individual la mot ca the gom hai thanh phan
// Gnome: mot con duong di qua het tat ca cac thanh pho
// Fitness: do dai cua con duong do
struct individual{
	vector<int> gnome; 
    double fitness; 
};

// Ham nay dung de in ra tieu de
void tieude();

// Ham nay dung de chon test
string chontest();

// Ham nay dung de doc du lieu vao tu file
// str: ten file
// n: so luong thanh pho
// Ham tra ve mot vector hai chieu chua toa do cua cac thanh pho
vector<vector<int>> refile(string str,int &n);

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
 
// Ham nay dung de sinh mot so ngau nhien
// start: can duoi
// end: can tren
// Ham tra ve mot so ngau nhien nam giua hai can
int rand_num(int start, int end);

// Ham nay dung de khoi tao mot gnome ngau nhien
// n: so luong thanh pho
// Ham tra ve mot vector chua mot con duong di qua het tat ca cac thanh pho
vector<int> create_gnome(int n); 
  
// Ham nay dung de tinh toan do dai cua duong di
// gnome: vector chua duong di
// Cities: vector hai chieu chua khoang cach giua cac thanh pho
// Ham tra ve mot gia tri thuc la do dai cua duong di chua trong gnome
double cal_fitness(const vector<int> &gnome, const vector< vector<double> >& Cities);

// Ham nay dung de dot bien gen
// gnome: mot con duong di qua het tat ca cac thanh pho
// n: so luong thanh pho
// Ham tra ve mot vector la dot bien cua gnome
vector<int> mutatedGene(vector<int> gnome, int n); 
  
// Ham nay dung de giam gia tri cua bien temp
// temp: bien can giam gia tri
// Ham tra ve mot gia tri thuc la gia tri cua temp sau khi giam
double cooldown(double temp);
  
// Ham nay dung de tim ra con duong ngan nhat
// Cities: vector hai chieu chua khoang cach giua cac thanh pho
// n: so luong thanh pho
// POP_SIZE: so luong ca the cua mot quan the
// Ham tra ve mot vector chinh la duong di ngan nhat qua tat ca thanh pho
vector<int> TSP(const vector< vector<double> >& Cities, int n, int POP_SIZE);

// Ham nay dung de in ket qua ra man hinh va ve do thi mieu ta qua trinh di chuyen
// A: vector hai chieu luu tru toa do cua cac thanh ph
// path: vector chua duong di ngan nhat
// result: do dai duong di ngan nhat
// n: so luong thanh pho
void show(const vector<vector<int>>&A,const vector<int>&path, double result,int n);

// Ham nay dung de ghi duong di ngan nhat vao file
// str: dung de tao ten file
// path: vector chua duong di ngan nhat
// result: do dai duong di ngan nhat
// n: so luong thanh pho
void wrfile(string str,const vector<int>&path, double result,int n);
  
int main() {
	srand(time(NULL));
	cout << fixed << setprecision(3);
	string str;
	str = chontest();
	int i,j,n;
	vector<vector<int>> A(1000,vector<int>(2));
	A = refile(str,n);
	int POP_SIZE = n;
	vector<vector<double> > Cities(n,vector<double>(n));
	Cities = distance(A,n);
	vector<int> path = TSP(Cities, n, POP_SIZE);
	double result = cal_fitness(path,Cities);
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

int rand_num(int start, int end) { 
    int r = end - start; 
    int rnum = start + rand() % r; 
    return rnum; 
} 

vector<int> create_gnome(int n) { 
    int i, n1 = n;
    vector<int> gnome(n+1);
    vector<int> temp1(n);
    for(i=0;i<n;i++){
    	temp1[i] = i;
	}
	for(i=1;i<n;i++){
		int temp = rand_num(1, n1);
		gnome[i]=temp1[temp];
		swap(temp1[temp],temp1[n1-1]);
		n1--;
	}
    return gnome; 
}  

double cal_fitness(const vector<int> &gnome, const vector< vector<double> >& Cities) { 

    double f = 0; 
    for (int i = 0; i < gnome.size() - 1; i++) { 
        f += Cities[gnome[i]][gnome[i + 1]]; 
    } 
    return f; 
} 

vector<int> mutatedGene(vector<int> gnome, int n) {
	if(n==2) return gnome; 
    while (true) { 
    int r = rand_num(1, n); 
    int r1 = rand_num(1, n);
    if (r1 != r) { 
        int temp = gnome[r]; 
        gnome[r] = gnome[r1]; 
        gnome[r1] = temp; 
        break; 
    } 
    }
	return gnome; 
}

double cooldown(double temp) { 
    return (90 * temp) / 100.0; 
}
 
vector<int> TSP(const vector< vector<double> >& Cities, int n, int POP_SIZE) { 
    int gen = 1; 
    int gen_thres = 50; 
  
    vector<struct individual> population; 
    struct individual temp; 
	temp.gnome = vector<int>(n+1);  
    for (int i = 0; i < POP_SIZE; i++) { 
        temp.gnome = create_gnome(n);
        temp.fitness = cal_fitness(temp.gnome,Cities); 
        population.push_back(temp); 
    }
	  
    double temperature = 10000; 
  
    while (temperature >= 50.0 && gen <= gen_thres) { 
        vector<struct individual> new_population; 
        for (int i = 0; i < POP_SIZE; i++) {
        	int k = 0, l = 0;
			while (true) {
                struct individual new_gnome; 
                new_gnome.gnome = population[i].gnome;
				new_gnome.gnome = mutatedGene(new_gnome.gnome, n); 
                new_gnome.fitness = cal_fitness(new_gnome.gnome,Cities); 
  				
  				if(l<=1000) {
  					if (new_gnome.fitness <= population[i].fitness) { 
						new_population.push_back(new_gnome); 
	                    break; 
                		}
						l++; 
				  }
  				
                else {
                    if(k<=1000){
                    	double prob = pow(2.7, -1 * ((double)(new_gnome.fitness - population[i].fitness) / (double)temperature)); 
	                    if (prob > 0.5) { 
	                        new_population.push_back(new_gnome); 
	                        break; 
	                    }
					}
                    
					else {
						new_gnome.gnome = population[i].gnome; 
                		new_gnome.fitness = population[i].fitness; 
                		new_population.push_back(new_gnome);
                		break;
					}
					k++; 
                }
            }	 
        } 
        temperature = cooldown(temperature); 
        population = new_population;  
        gen++;
    } 
    
	int i,j;
    double min = population[0].fitness;
    j = 1;
    for(i=1;i<POP_SIZE;i++) {
    	if(population[i].fitness<min){
    		min = population[i].fitness;
    		j = i;
		}
	} 
	return population[j].gnome;     
} 

void show(const vector<vector<int>>&A, const vector<int>&path, double result, int n){
	int i,tam;
	char ch[10];
	cout<<"So thanh pho: "<<n<<endl<<endl;
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
	str1 += "D:\\Do_an_LTTT\\PROJECT\\Solution_genetic\\sol";
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
