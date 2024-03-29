#include"TSP.h"
//Main function calling different methods to solve TSP
//Print output into .sol and .trace file

using namespace std;

ofstream output_sol,output_trace;

int callTSP()
{	
	string Methods []= {"Approx", "Greedy", "LS1","LS2","BnB"};
	string filename1,filename2;
	char* argv[5];
	argv[1] = "../DATA/burma14.tsp";
	argv[2] = "1";
	argv[3] = "LS1";
	argv[4] = "3";
	int **distance;
	int *d=new int;
	int *o=new int;
	distance=readgraph(argv[1],d,o);
	cout << "NAME" << NAME << endl;
	int dim=*d;
	int opt=*o;
	double cutoff = strtod(argv[2],NULL);
	int seed=atoi(argv[4]);
	
	int i;
	int pathlength = 0;
	double gap;
	
	if(Methods[0].compare(argv[3])==0)
	{
		cout << "Method:" << "Approximation"<<endl;
		
		filename1 = NAME + "_" + Methods[0] + "_"+argv[2]+".sol";
		const char *name1 = filename1.c_str();
		output_sol.open(name1);
	
		if (!output_sol.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		node** s = new node* [dim];
		i = 0;
		for (i=0;i<dim;i++){
			s[i] = new node(i, dim);
		}

		prim(distance,s,dim);		
		cout<<"Path:";
		preorder(s[0]);
		cout<< s[0]->keyv+1<<endl;
		output_sol << s[0]->keyv+1 << endl;
		cout<<"Path Length:";
		pathlength = findpathLength(distance);
		cout<<pathlength<<endl;
		
		gap = (float)(pathlength-opt)/opt;
		cout << "Solution gap:" << 100*gap << "%" << endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[1].compare(argv[3])==0)
	{	
		cout << "Method:" << "Greedy"<<endl;
		
		filename1 = NAME + "_" + Methods[1] + "_"+argv[2]+".sol";
		const char *name1 = filename1.c_str();
		output_sol.open(name1);
		
		if (!output_sol.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		int *path;
		path=greedy_algo(distance, dim);
		
		cout<<"Path:";
		
		for(i=0;i<dim-1;i++)
			pathlength += distance[path[i]][path[i+1]];
		pathlength += distance[path[dim-1]][path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<path[i]+1<<",";
			output_sol << path[i]+1<<",";
		}
		cout<<path[dim-1]+1<<","<<path[0]+1<<endl;
		output_sol<<path[dim-1]+1<<","<<path[0]+1<<endl;
		
		cout<<"Path Length:";
		cout<<pathlength<<endl;
		
		gap = (float)(pathlength-opt)/opt;
		cout << "Solution gap:" << 100*gap << "%" << endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[2].compare(argv[3])==0)
	{
		cout << "Method:" << "Iterated Hill Climbing"<<endl;
		
		filename1 = NAME + "_" + Methods[2] + "_"+argv[2]+"_"+argv[4]+".sol";
		const char *name1 = filename1.c_str();
		filename2 = NAME + "_" + Methods[2] + "_"+argv[2]+"_"+argv[4]+".trace";
		const char *name2 = filename2.c_str();
		output_sol.open(name1);
		output_trace.open(name2);
		if (!output_sol.is_open()|| !output_trace.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}

		int **path;
		int *initial;
		initial=greedy_algo(distance, dim);
		path= HC(distance, dim, initial, cutoff, i);
		
		cout<<"Path:";
		
		for(i=0;i<dim-1;i++)
			pathlength += distance[*path[i]][*path[i+1]];
		pathlength += distance[*path[dim-1]][*path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<*path[i]+1<<",";
			output_sol << *path[i]+1<<",";
		}
		cout<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		output_sol<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		
		cout<<"Path Length:";
		cout<<pathlength<<endl;

		gap = (float)(pathlength-opt)/opt;
		cout << "Solution gap:" << 100*gap << "%" << endl;
		cout << "Elapsed time:" << cutoff << "s" <<endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[3].compare(argv[3])==0)
	{
		cout << "Method:" << "Simulated Annealing"<<endl;
		
		filename1 = NAME + "_" + Methods[3] + "_"+argv[2]+"_"+argv[4]+".sol";
		const char *name1 = filename1.c_str();
		filename2 = NAME + "_" + Methods[3] + "_"+argv[2]+"_"+argv[4]+".trace";
		const char *name2 = filename2.c_str();
		output_sol.open(name1);
		output_trace.open(name2);
		if (!output_sol.is_open()|| !output_trace.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		int **path;
		int *initial;
		initial=greedy_algo(distance, dim);

		int temp = distance[initial[9]][initial[10]]*2*dim;
		double cooling_r = 0.99;
		path = SA(initial, distance, temp, 0.1*dim, cooling_r, cutoff, dim, seed);
		
		cout<<"Path:";
		for(i=0;i<dim-1;i++)
			pathlength += distance[*path[i]][*path[i+1]];
		pathlength += distance[*path[dim-1]][*path[0]];
		output_sol << pathlength <<endl;
		for(i=0;i<dim-1;i++)
		{
			cout<<*path[i]+1<<",";
			output_sol << *path[i]+1<<",";
		}
		cout<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		output_sol<<*path[dim-1]+1<<","<<*path[0]+1<<endl;
		
		cout<<"Path Length:";
		cout<<pathlength<<endl;
		
		gap = (float)(pathlength-opt)/opt;
		cout << "Solution gap:" << 100*gap << "%" << endl;
		cout << "Elapsed time:" << cutoff << "s" <<endl;
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
	
	if(Methods[4].compare(argv[3])==0)
	{
		cout << "Method:" << "Branch and Bound"<<endl;
		
		filename1 = NAME + "_" + Methods[4] + "_"+argv[2]+".sol";
		const char *name1 = filename1.c_str();
		filename2 = NAME + "_" + Methods[4] + "_"+argv[2]+".trace";
		const char *name2 = filename2.c_str();
		output_sol.open(name1);
		output_trace.open(name2);
		if (!output_sol.is_open()|| !output_trace.is_open())
		{
			cout << "Failed to create output file!" << endl;
			return 0;
		}
		
		int *min;
		min=Matrix(distance,dim);
		struct Node *solution;
		int source=0;
		solution=BranchAndBound(distance, dim, min, source, cutoff);
		
		if(solution->time<cutoff)
		{
			cout << "Optimal solution found:"<< endl;
			cout << "Total cost:" << solution->value << endl;
			output_sol << solution->value <<endl;
			cout << "Optimal cycle:" ;
			for(vector<int>::const_iterator it=solution->path->begin();it!=solution->path->end();it++)
			{
				cout<<*it+1<<",";
				output_sol <<*it+1<<",";
			}
			cout << source+1 << endl;
			output_sol<< source+1 << endl;
			cout << "Elapsed time:"<< solution->time << "s" << endl;
		}
		else
		{
			cout << "Total cost:" << solution->value << endl;
			output_sol << solution->value <<endl;
			gap = (float)(solution->value-opt)/opt;
			cout << "Solution gap:" << 100*gap << "%" << endl;
			cout << "Solution cycle:" ;
			for(vector<int>::const_iterator it=solution->path->begin();it!=solution->path->end();it++)
			{
				cout<<*it+1<<",";
				output_sol <<*it+1<<",";
			}
			cout << source+1 << endl;
			output_sol<< source+1 << endl;
			cout << "Elapsed time:"<< solution->time << "s" << endl;
		}
		
		cout << endl << "Output file created!" << endl;
		output_sol.close();
		output_trace.close();
		return 0;
	}
}


int main(int argc, char* argv[]){
	callTSP();
	return 0;
}