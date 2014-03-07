


//NOTE BE THAT THE PROGRAM BELOW CHOOSES 3 OUT OF 20 GIVEN NODES AS HUBS.
//THE DATA SET USED IN THE SAME INCLUDES THE FIRST 20 ENTRIES OF THE CAB DATA UNIVERSALLY USED.
//0.2 discount (alpha) factor
//CURRENT INSTANCE FOR 20 NODES + 3 HUBS AND M = 5 FOR MATRIX CALCULATION (6 X 6 MATRICES)

/* Files for Storage : 

1) "Check_file.dat" : Stores the entire range of values calculated for the decision variables in EVERY iteration
2) "Complete_Output.dat" : Stores the final solution

*/

 
#include<ilcplex/ilocplex.h>
#include <cstdio>
#include <cstdlib>
#include<windows.h>
#include <fstream>
#include <iomanip>

#include "C:\Users\Chirag\Desktop\OR\simple\simple\include\cmatrix"



ILOSTLBEGIN
#if defined(__BORLANDC__)
#pragma option -w-aus
#endif

//
// Using declarations. 
//
using std::cout;
using std::endl;
using techsoft::epsilon;
using techsoft::isVecEq;
using std::exception;

#ifdef _MSC_VER
using ::rand;
#else
using std::rand;
using std::size_t;
#endif





#include<math.h>
#include<time.h>
#include<stdlib.h>

#include <time.h>                    


#ifndef _NO_NAMESPACE
using namespace std;

#define STD std
#else
#define STD
#endif

#ifndef _NO_TEMPLATE

#else
typedef matrix Matrix;
#endif

#ifndef _NO_EXCEPTION
#  define TRYBEGIN()	try {
#  define CATCHERROR()	} catch (const STD::exception& e) { \
						cerr << "Error: " << e.what() << endl; }
#else
#  define TRYBEGIN()
#  define CATCHERROR()
#endif


#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<fstream>
#include<iosfwd>
#include<string>
#include <deque>
#include <sstream>
#include <time.h>
//#include <iomanip.h>
#include <stdlib.h>

//#include <cplex.h>
#include <ilcplex/ilocplex.h>
//#include <iloconcert/ilomodel.h>
//#include <iloconcert/iloenv.h>
#include <ilconcert/ilosys.h>

ILOSTLBEGIN
//#define LARGE 



typedef IloArray<IloNum> OneD_Array_Float;
typedef IloArray<OneD_Array_Float> TwoD_Array_Float;
typedef IloArray<TwoD_Array_Float> ThreeD_Array_Float;
typedef IloArray<IloNumVarArray> m;
typedef IloArray<m> k;
typedef IloArray<k> N_H_H_N_connection;
typedef IloArray<int> OneD_Array;
typedef IloArray<OneD_Array> TwoD_Array;			//Two dimensional array for storing the constants of the problem
typedef IloArray<TwoD_Array> ThreeD_Array;
typedef IloArray<ThreeD_Array> FourD_Array;




typedef IloArray<IloNum> OneDMatrix;
typedef IloArray<OneDMatrix> TwoDMatrix;
typedef IloArray<TwoDMatrix> ThreeDMatrix;

typedef techsoft::matrix<double> Matrix;

double power(double x,int y)
{
	double z=1;
	int i=0;
	while(i<y)
	{
		z = z * x;
		i++;
	}
	return(z);
}



double Waiting_Time(double lambda,double mu)
{
	double waiting_time;
	if(mu <=lambda)
	{
		cout<<"Error!!!!!!"<<endl<<"Please check code";
		getchar();
	}

	waiting_time = 1/(mu - lambda);

	return(waiting_time);
}








int main()
{
	//10 warehouses with 4 channels each, 40 farms and 25 retail outlets 
	IloEnv env;
	cout<<setprecision(40)<<Waiting_Time(20925.3,(20933.1))<<endl;
	cout<<setprecision(40)<<Waiting_Time(20925.3*1.000001,20933.1)<<endl;
	cout<<20925.3*1.000001;
	
	m w_ik(env,20);		//warehouse connection to farm
	int i=0;int k1=0;int j=0;
	while(i<20)
	{
		w_ik[i] = IloNumVarArray(env,10,0,1,ILOINT);
		i++;
	}
	i=0;
	
	m x_jk(env,20);		//warehouse connection to retails	
	while(j<20)
	{
		x_jk[j] = IloNumVarArray(env,10,0,1,ILOINT);
		j++;
	}
	j=0;
	
	int c=1;		//channels

	m y_kl(env,10);		//capacity of warehouse channels
	int l=0;k1=0;
	while(k1<10)
	{
		y_kl[k1] = IloNumVarArray(env,5,0,1,ILOINT);
		k1++;
	}
	k1=0;

	IloNumVarArray z_k(env,10,0,1,ILOINT);		///warehouse opened decision variable


	IloModel model(env);

	i=0;
	while(i<20)
	{
		k1=0;
		IloExpr expr(env);
		while(k1<10)
		{
			expr += w_ik[i][k1];
			k1++;
		}
		model.add(expr == 1);
		i++;
		expr.end();
	}

	j=0;
	while(j<20)
	{
		k1=0;
		IloExpr expr(env);
		while(k1<10)
		{
			expr += x_jk[j][k1];
			k1++;
		}
		model.add(expr == 1);
		j++;
		expr.end();
	}
	
//constraint
	k1=0;
	while(k1<10)
	{
		l=0;IloExpr expr(env);
		while(l<5)
		{
			expr += y_kl[k1][l];
			l++;
		}
		model.add(expr == z_k[k1]);
		model.add(expr<=1);
		expr.end();
		k1++;
	}


	OneD_Array_Float Production(env,20);
	OneD_Array_Float Demand(env,20);
	OneD_Array_Float Capacity(env,5);
	OneD_Array_Float Capacity_Cost(env,5);
	TwoD_Array_Float Speed_ik(env,20);


	TwoD_Array_Float D_ik(env,20);

	i=0;k1=0;
	while(i<20)
	{
		D_ik[i] = IloNumArray(env,10);
		Speed_ik[i] = IloNumArray(env,10);
		i++;
	}

	TwoD_Array_Float D_jk(env,20);
	TwoD_Array_Float Speed_jk(env,20);
	j=0;k1=0;
	while(j<20)
	{
		D_jk[j] = IloNumArray(env,10);
		Speed_jk[j] = IloNumArray(env,10);
		j++;
	}

	double Transport_Cost = 0.00184;			//transportation cost per unit distance per unit mass
	
	double Transport_Speed = 30;				//60 kmph

	ifstream fin;
	fin.open("Production.dat");
	float total_production =0;
	string str;

	i=0;
	while(i<20)
	{
		getline(fin,str);

		Production[i] = atof(str.c_str());
		total_production += Production[i];
		i++;
	}

	fin.close();
	fin.open("Demand.dat");

	float total_demands = 0;
	j=0;
	while(j<20)
	{
		getline(fin,str);
		Demand[j] = atof(str.c_str());
		total_demands += Demand[j];
		j++;
	}
cout<<"Total production = "<<total_production;


	int d = 1;
	Capacity[0] = 8722.4;
	Capacity[1] = 11000.0;
	Capacity[2] = 17000.0;
	Capacity[3] = 17000.8*2;
	Capacity[4] = 55000.8;

	int cap_cost_factor = 10;
	
	Capacity_Cost[0] = 147.44 * cap_cost_factor ;
	Capacity_Cost[1] = 166.36* cap_cost_factor;
	Capacity_Cost[2] = 223.15* cap_cost_factor;
	Capacity_Cost[3] = 393.51* cap_cost_factor * 20;
	Capacity_Cost[4] = 620.642* cap_cost_factor * 20;

	fin.close();

	float Waiting_time_factor = 1;
	ifstream fin55;
	fin55.open("Speed_ik.txt");
string str2;
	i=0;
	k1=0;
	cout<<endl<<"The distance between farm and granary is"<<endl<<endl;
	fin.open("DISTANCE_FG.dat");
	while(i<20)
	{
		k1=0;
		while(k1<3)
		{
			getline(fin,str);
			D_ik[i][k1] = atof(str.c_str());
			getline(fin55,str2);
			Speed_ik[i][k1] = atof(str2.c_str());
			cout<<Speed_ik[i][k1]<<"	";
			k1++;

		}




		while(k1<10)
		{
			getline(fin,str);
			D_ik[i][k1] = 3*atof(str.c_str());
			getline(fin55,str2);
			Speed_ik[i][k1] = atof(str2.c_str());
			cout<<Speed_ik[i][k1]<< "	";
			k1++;
		}

		i++;cout<<endl;
	}

	fin.close();
	fin55.close();
	ifstream fin552;
getchar();

	ifstream fin2;
	
	j=0;
	k1=0;
	cout<<endl<<"This is the retail-farm matrix:"<<endl<<endl;
	fin2.open("DISTANCE_RG.dat");
	fin552.open("Speed_jk.txt");
	while(j<20)
	{
		k1=0;
		while(k1<3)
		{
			getline(fin2,str);
		getline(fin552,str2);
			Speed_jk[j][k1] = atof(str2.c_str());
			D_jk[j][k1] = atof(str.c_str());
			cout<<Speed_jk[j][k1]<<"	";
			k1++;
		}
		while(k1<10)
		{
			getline(fin2,str);
			getline(fin552,str2);
			Speed_jk[j][k1] = atof(str2.c_str());
		
			D_jk[j][k1] = 3*atof(str.c_str());
			cout<<Speed_jk[j][k1]<<"	";
			k1++;
		}
		j++;cout<<endl;
	}


	fin2.close();

	j=0;getchar();getchar();


	cout<<"This is the array needed :"<<endl<<endl;

	k1=0;
	while(j<20)
	{
		k1=0;
		
		while(k1<10)
		{
		cout<<setprecision(10)<<D_jk[j][k1]<<"	";
		k1++;
		}

		cout<<endl;
		j++;
	}

	//constraint 3
	k1=0;
	while(k1<10)
	{
		IloExpr supply(env);
		IloExpr demand(env);
		i=0;j=0;
		while(i<20)
		{
			supply += w_ik[i][k1] * Production[i];
			i++;
		}
		while(j<20)
		{
			demand += x_jk[j][k1] * Demand[j];
			j++;
		}
		model.add(supply >= demand);
		supply.end();
		demand.end();
		k1++;
	}
cout<<"done";
	k1=0;
	//constraint 4
	while(k1<10)
	{
		IloExpr supply(env);
		IloExpr capacity(env);
		
		i=0;l=0;
		while(i<20)
		{
			supply += w_ik[i][k1] * Production[i];
			i++;
		}
		while(l<5)
		{
			capacity += y_kl[k1][l] * Capacity[l];
			l++;
		}
		model.add(capacity>=supply);
		supply.end();
		capacity.end();
		k1++;
	}


	//model.add(z_k[9] == 0);

cout<<"done";

IloExpr obj(env);

i=0;k1=0;
j=0;

while(i<20)
{
	k1=0;
	while(k1<10)
	{
		obj += w_ik[i][k1] * D_ik[i][k1] * Production[i] * Transport_Cost;
		k1++;
	}
	i++;
}

while(j<20)
{
	k1=0;
	while(k1<10)
	{
		obj += x_jk[j][k1] * D_jk[j][k1] * Demand[j]*Transport_Cost;
		k1++;
	}
	j++;
}


l=0;
k1=0;
while(k1<10)
{
	l=0;
	while(l<5)
	{
		obj += y_kl[k1][l] * Capacity_Cost[l];
		l++;
	}
	k1++;
}

model.add(IloMinimize(env,obj));

IloCplex cplex(model);

if(!cplex.solve())
{
	cout<<"The problem is infeasible without cuts added";
	getchar();
	getchar();
	return 0;
}

cout<<endl<<endl<<"Optimal Objective is : "<<cplex.getObjValue();


i=0;k1=0;
j=0;
double trans_cost=0;
while(i<20)
{
	k1=0;
	while(k1<10)
	{
		trans_cost += cplex.getValue(w_ik[i][k1]) * D_ik[i][k1] * Production[i]*Transport_Cost;
		k1++;
	}
	i++;
}
j=0;
while(j<20)
{
	k1=0;
	while(k1<10)
	{
		trans_cost += cplex.getValue(x_jk[j][k1]) * D_jk[j][k1] * Demand[j]*Transport_Cost;
		k1++;
	}
	j++;
}


l=0;
k1=0;double cap_cost=0;
while(k1<10)
{
	l=0;
	while(l<5)
	{
		cap_cost += cplex.getValue(y_kl[k1][l]) * Capacity_Cost[l];
		l++;
	}
	k1++;
}


ofstream fin4;
fin4.open("BTP_OUTPUT_single_channel.dat",ios::app);
fin4<<endl<<endl<<endl<<"****************************"<<endl<<"The Results are "<<endl<<endl;

fin4<<"Trans_cost = "<<trans_cost<<endl<<"Capacity cost = "<<cap_cost<<endl<<endl<<endl;
cout<<endl<<endl<<"Trans_cost = "<<trans_cost<<endl<<"Capacity cost = "<<cap_cost<<endl<<endl<<endl;
getchar();
getchar();
i=0;
k1=0;
j=0;


fin4<<"The output for D_ik parameters"<<endl<<endl;
i=0;
while(i<20)
{
	k1=0;
	while(k1<10)
	{
		fin4<<D_ik[i][k1]<<"	";
		k1++;
	}
	fin4<<endl;
	i++;
}


fin4<<"The output for D_jk parameters"<<endl<<endl;
i=0;
while(i<20)
{
	k1=0;
	while(k1<10)
	{
		fin4<<D_jk[i][k1]<<"	";
		k1++;
	}
	fin4<<endl;
	i++;
}

fin4<<"The output for w_ik variables"<<endl<<endl;
i=0;
while(i<20)
{
	k1=0;
	while(k1<10)
	{
		fin4<<cplex.getValue(w_ik[i][k1])<<"	";
		k1++;
	}
	fin4<<endl;
	i++;
}

fin4<<endl<<"The output for x_jk variables :"<<endl<<endl;

while(j<20)
{
	k1=0;
	while(k1<10)
	{
		fin4<<cplex.getValue(x_jk[j][k1])<<"	";
		k1++;
	}
	j++;fin4<<endl;
}

fin4<<endl<<"The output for y_kl variables:"<<endl<<endl;

l=0;
k1=0;
while(k1<10)
{
	l=0;
	while(l<5)
	{
		fin4<<cplex.getValue(y_kl[k1][l])<<"	";
		l++;
	}
	k1++;fin4<<endl;
}

fin4<<endl<<"The output for volume flow through each warehouse";
double flowsum =0;

OneD_Array_Float mu_k(env,10);
OneD_Array_Float lambda_k(env,10);
k1=0;

while(k1<10)
{
	i=0;flowsum =0;
	while(i<20)
	{
		flowsum += Production[i] * cplex.getValue(w_ik[i][k1]);
		i++;
	}
	fin4<<"Supply to warehouse "<<k1+1<<" = "<<flowsum<<endl;lambda_k[k1] = flowsum;
	k1++;
}

i=0;

fin4<<endl<<endl<<"The output for demand of each warehouse"<<endl<<endl;

k1=0;

while(k1<10)
{
	j=0;
	flowsum=0;
	while(j<20)
	{
		flowsum += Demand[j] * cplex.getValue(x_jk[j][k1]);
		j++;
	}

	fin4<<"Demand from warehouse "<<k1+1<<" = "<<flowsum<<endl;

	k1++;
}


fin4<<endl<<endl<<"The output for capacity allotted at each warehouse"<<endl<<endl;

k1=0;

while(k1<10)
{
	l=0;
	flowsum=0;
	while(l<5)
	{
		flowsum += Capacity[l] * cplex.getValue(y_kl[k1][l]);
		l++;
	}

	fin4<<"Capacity allotted at warehouse "<<k1+1<<" = "<<flowsum<<endl;
	mu_k[k1] = flowsum;

	k1++;
}

Matrix waiting_time(10,1);
Matrix gradient(10,2);

i=0;
while(i<10)
{
	waiting_time[i][0] = 0;
	gradient[i][0] = 0;
	gradient[i][1] = 0;
	i++;
}

	k1=0;
	while(k1<10)
	{
		if(cplex.getValue(z_k[k1]) > 0.9)
		{
			
			cout<<endl<<"Waiting_Time at warehouse "<<k1+1<<" = "<<Waiting_Time(lambda_k[k1] , mu_k[k1])<<endl<<endl<<endl;
			waiting_time[k1][0] = Waiting_Time(lambda_k[k1] , mu_k[k1]);
			cout<<"lambda = "<<lambda_k[k1]<<endl<<"Mu = "<<mu_k[k1]<<endl;
			cout<<"Required value = "<<Waiting_Time(lambda_k[k1] * 1.000001 , mu_k[k1])<<endl;
			gradient[k1][0] = (Waiting_Time(lambda_k[k1] * 1.000001 , mu_k[k1]) - Waiting_Time(lambda_k[k1] , mu_k[k1]))/(0.000001*lambda_k[k1]);
			gradient[k1][1] = (Waiting_Time(lambda_k[k1], mu_k[k1]* 1.000001) - Waiting_Time(lambda_k[k1] , mu_k[k1]))/(0.000001*mu_k[k1]);
			cout<<"Gradient1 at warehouse "<<k1+1<<" = "<<gradient[k1][0]<<endl;
			cout<<"Gradient2 at warehouse "<<k1+1<<" = "<<gradient[k1][1]<<endl;
		}
		k1++;
	}


int flag =1;
int x=0;

i=0;
while(i<20)
{	
	j=0;
	while(j<20)
	{
		k1=0;
		while(k1<10)
		{
			if(D_ik[i][k1] * cplex.getValue(w_ik[i][k1])/Speed_ik[i][k1] + D_jk[j][k1]*cplex.getValue(x_jk[j][k1])/Speed_jk[j][k1] + waiting_time[k1][0] > 6*Waiting_time_factor)
			{
				flag = 0;
			}
			k1++;
		}
		j++;
	}
	i++;
}
if(flag==0)
{
	cout<<endl<<endl<<"PROBLEM DETECTED WITHOUT CUTS IN TRANSPORT TIME"<<endl<<endl;
	getchar();
}
cout<<"done";


//LOOP START FOR ADDING CUTS


while(flag==0)
{


flag = 1;

i=0;j=0;k1=0;int m1=0;
int i1=0;int j1=0;
int counterf=0;
while(i<20)
{
	j=0;
	while(j<20)

	{
		k1=0;
		while(k1<10)
		{
			m1=0;
			IloExpr flow_req(env);
			IloExpr cap_req(env);
			i1=0;
			while(i1<20)
			{
				flow_req  += Production[i1]*w_ik[i1][k1];
				i1++;
			}
			j1=0;
			while(j1<5)
			{
				cap_req += Capacity[j1] * y_kl[k1][j1];
				j1++;
			}


			while(m1<10)
			{
				cplex.addCut(w_ik[i][k1] * D_ik[i][k1] /Speed_ik[i][k1] + x_jk[j][k1] * D_jk[j][k1]/Speed_jk[j][k1] + waiting_time[m1][0]*z_k[k1] + gradient[m1][0] * (flow_req - lambda_k[m1]*z_k[k1]) + gradient[m1][1] * (cap_req - mu_k[m1]*z_k[k1])<=6*Waiting_time_factor);
				cout<<"Cut Added for "<<m1+1<<"th warehouse"<<endl;
				m1++;
			}


			cout<<"Done"<<"Done adding cuts";
			counterf++;
			cout<<" with cut series = "<<counterf<<endl<<endl;
		k1++;
		flow_req.end();
		cap_req.end();
		}
	j++;
	}
	i++;
}

if(!cplex.solve())
{
	cout<<"The problem is infeasible with cuts added";
	getchar();
	getchar();
	return 0;
}

//reset lambda and mu matrices
k1=0;

while(k1<10)
{
	i=0;flowsum =0;
	while(i<20)
	{
		flowsum += Production[i] * cplex.getValue(w_ik[i][k1]);
		i++;
	}
	lambda_k[k1] = flowsum;
	k1++;
}
cout<<endl<<"done";
getchar();
getchar();
i=0;
k1=0;

k1=0;

while(k1<10)
{
	l=0;
	flowsum=0;
	while(l<5)
	{
		flowsum += Capacity[l] * cplex.getValue(y_kl[k1][l]);
		l++;
	}

	mu_k[k1] = flowsum;
	k1++;
}


//reset waiting time and gradient matrices
i=0;
while(i<10)
{
	waiting_time[i][0] = 0;
	gradient[i][0] = 0;
	gradient[i][1] = 0;
	i++;
}

	k1=0;
	while(k1<10)
	{
		if(cplex.getValue(z_k[k1]) > 0.9)
		{
			
			cout<<endl<<endl<<"Waiting_Time at warehouse "<<k1+1<<" = "<<Waiting_Time(lambda_k[k1] , mu_k[k1])<<endl<<endl;
			waiting_time[k1][0] = Waiting_Time(lambda_k[k1] , mu_k[k1]);
			gradient[k1][0] = (Waiting_Time(lambda_k[k1] * 1.000001 , mu_k[k1]) - Waiting_Time(lambda_k[k1] , mu_k[k1]))/(0.000001*lambda_k[k1]);
			gradient[k1][1] = (Waiting_Time(lambda_k[k1], mu_k[k1]* 1.000001) - Waiting_Time(lambda_k[k1] , mu_k[k1]))/(0.000001*mu_k[k1]);
			cout<<"Gradient 1 at warehouse"<<k1+1<<" = "<<gradient[k1][0]<<endl;
			cout<<"Gradient 2 at warehouse"<<k1+1<<" = "<<gradient[k1][1]<<endl;


		}
		k1++;
	}


	
	i=0;
while(i<20)
{	
	j=0;
	while(j<20)
	{
		k1=0;
		while(k1<10)
		{
			if(D_ik[i][k1] * cplex.getValue(w_ik[i][k1])/Speed_ik[i][k1] + D_jk[j][k1]*cplex.getValue(x_jk[j][k1])/Speed_jk[j][k1] + waiting_time[k1][0] > 6*Waiting_time_factor)
			{
				flag = 0;
			}
			k1++;
		}
		j++;
	}
	i++;
}


getchar();
getchar();

}



i=0;k1=0;
j=0;
trans_cost=0;
while(i<20)
{
	k1=0;
	while(k1<10)
	{
		trans_cost += cplex.getValue(w_ik[i][k1]) * D_ik[i][k1] * Production[i]*Transport_Cost;
		k1++;
	}
	i++;
}
j=0;
while(j<20)
{
	k1=0;
	while(k1<10)
	{
		trans_cost += cplex.getValue(x_jk[j][k1]) * D_jk[j][k1] * Demand[j]*Transport_Cost;
		k1++;
	}
	j++;
}


l=0;
k1=0; cap_cost=0;
while(k1<10)
{
	l=0;
	while(l<5)
	{
		cap_cost +=  cplex.getValue(y_kl[k1][l]) * Capacity_Cost[l];
		l++;
	}
	k1++;
}


cout<<"The transport cost is :"<<trans_cost<<endl<<"The Capacity cost is:"<<cap_cost<<endl<<"Total cost = "<<(trans_cost + cap_cost);


int flag1 =0;
	while(i<20)
	{
		k1=0;
		while(k1<10)
		{
			j=0;
			while(j<20)
			{
			
			
						if( cplex.getValue(w_ik[i][k1]) * D_ik[i][k1]/Speed_ik[i][k1]+ cplex.getValue(x_jk[j][k1]) * D_jk[j][k1]/Speed_jk[j][k1] + Waiting_Time(lambda_k[k1],mu_k[k1]) > 6*Waiting_time_factor)
						{
					fin4<<endl<<"path w["<<i+1<<"]["<<k1+1<<"] + x["<<j+1<<"]["<<k1+1<<"]"<<endl<<"The values are "<<cplex.getValue(w_ik[i][k1]) * D_ik[i][k1] / Transport_Speed<<" and "<<cplex.getValue(x_jk[j][k1]) * D_jk[j][k1] / Transport_Speed<<endl<<endl;
			//		getchar();
					flag1 =1;
			//		getchar();
						}
			
				j++;
			}
			k1++;
		}
		i++;
	}




	ofstream fin44;
	fin44.open("Final_Btp_Output_changed_function_single_channel.dat",ios::app);

	fin44<<"The results are as follows :"<<endl<<endl<<endl;

	i=0;
	k1=0;
	j=0;


	fin44<<"The transport cost is :"<<trans_cost<<endl<<"The Capacity cost is:"<<cap_cost<<endl<<"Total cost = "<<(trans_cost + cap_cost);
	fin44<<"FARM - GRAINARY CONNECTION :"<<endl<<endl;

	i=0;
	while(i<20)
	{
		k1=0;
		while(k1<10)
		{
			fin44<<cplex.getValue(w_ik[i][k1])<<"	";
			k1++;
		}
		fin44<<endl;
		i++;
	}



		fin44<<endl<<"RETAIL - GRAINARY CONNECTION :"<<endl<<endl;

	j=0;
	while(j<20)
	{
		k1=0;
		while(k1<10)
		{
			fin44<<cplex.getValue(x_jk[j][k1])<<"	";
			k1++;
		}
		fin44<<endl;
		j++;
	}

		fin44<<endl<<"GRAINARY CAPACITY:"<<endl<<endl;

	i=0;k1=0;
	while(k1<10)
	{
		l=0;
		while(l<5)
		{
			fin44<<cplex.getValue(y_kl[k1][l])<<"	";
			l++;
		}
		fin44<<endl;
		k1++;
	}

		k1=0;
	while(k1<10)
	{
		if(cplex.getValue(z_k[k1]) > 0.9)
		{
			
			fin44<<endl<<endl<<"Waiting_Time at warehouse "<<k1+1<<" = "<<Waiting_Time(lambda_k[k1] , mu_k[k1])<<endl<<endl<<endl;
			
		}
		k1++;
	}

k1=0;

while(k1<10)
{
	i=0;flowsum =0;
	while(i<20)
	{
		flowsum += Production[i] * cplex.getValue(w_ik[i][k1]);
		i++;
	}
	fin44<<"Supply to warehouse "<<k1+1<<" = "<<flowsum<<endl;
	k1++;
}

i=0;

fin44<<endl<<endl<<"The output for demand of each warehouse"<<endl<<endl;

k1=0;

while(k1<10)
{
	j=0;
	flowsum=0;
	while(j<20)
	{
		flowsum += Demand[j] * cplex.getValue(x_jk[j][k1]);
		j++;
	}

	fin44<<"Demand from warehouse "<<k1+1<<" = "<<flowsum<<endl;

	k1++;
}


fin44<<endl<<endl<<"The output for capacity allotted at each warehouse"<<endl<<endl;

k1=0;

while(k1<10)
{
	l=0;
	flowsum=0;
	while(l<5)
	{
		flowsum += Capacity[l] * cplex.getValue(y_kl[k1][l]);
		l++;
	}

	fin44<<"Capacity allotted at warehouse "<<k1+1<<" = "<<flowsum<<endl;
	

	k1++;
}





	getchar();
	getchar();
	
	}
