#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


void printMultiVec(std::vector<std::vector<int>> &vect){
	for (int i = 0; i < vect.size(); i++) { 
        for (int j = 0; j < vect[i].size(); j++) 
            cout << vect[i][j] << " "; 
        cout << endl; 
    }
}


void makeSingleVector(std::vector<std::vector<int>> &vectMul, std::vector<int> &vect){
	for (int i = 0; i < vectMul.size(); i++) { 
        for (int j = 0; j < vectMul[i].size(); j++){        	
        	vect.push_back(vectMul[i][j]);
        }        
    }
}


int main(int argc, char const *argv[])
{

	int cols = 5;
	int rows = 3;
	// Create
    vector< vector<int> > vec(rows, vector<int>(cols));
    

    
	vec[0][0] = 1;
	vec[0][1] = 2;
	vec[0][2] = 3;
	vec[0][3] = 4;
	vec[0][4] = 5;

	vec[1][0] = 6;
	vec[1][1] = 7;
	vec[1][2] = 8;
	vec[1][3] = 9;
	vec[1][4] = 10;

	vec[2][0] = 11;
	vec[2][1] = 12;
	vec[2][2] = 13;
	vec[2][3] = 14;
	vec[2][4] = 15;


	printMultiVec(vec);


	cout << "\n\n" << endl;

	std::reverse(vec[0].begin(), vec[0].end());
	std::reverse(vec[1].begin(), vec[1].end());
	std::reverse(vec[2].begin(), vec[2].end());


	std::reverse(vec.begin(), vec.end());
    
	vector<int> result;
	printMultiVec(vec);


	makeSingleVector(vec, result);

	for (int i = 0; i < result.size(); ++i)
	{
		cout << result.at(i) <<endl;
	}



	

	return 0;
}