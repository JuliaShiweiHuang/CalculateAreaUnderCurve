/*
Developer: Shiwei Huang
Purpose: 
1. This program should estimate the area under two functions: f(x)=x^2 and f(x)=x^0.5+1 by giving the rightmost x. Assuming leftmost x=0;
2. One way to estimate the area is to give a rightmost x. Then divide the area between x=0 and rightmost x. The area of the region is found
by summing the areas of all the rectangular subregions;
3. A good estimate for the true area can be found if the (upper sum - lower sum)<=epsilon;
4. The upper and lower sums converge as the number of intervals(the number of rectangles increases);

Input:
1. The program should display a short menu explaning number 1 for function 1: f(x)=x^2; Number 2 for function 2: f(x)=x^0.5+1; 
number 3 to quit; if the number is not in range 1-3, the program will show the error message and repeat the menu;
2. User should type number 1 or number 2 to choose the right function;
3. User should type the rightmost x for the desired region for calculating the area under rightmost x. We are also assuming the leftmost x=0;
4. User should enter a desired epsilon;
5. Once the solution has been found, the whole process should repeat;

Output:
1. The program should display the minimum number of intervals needed;
2. Minimum number of intervals = (UpperSum-LowerSum)<Epsilon;
3. If the region has been divided into more than 2000 intervals and the sum is not within epsilon, a message to that effect should be displayed;
*/
                                          
#include <iostream>
#include <iomanip>     
#include <stdio.h>    
#include <math.h> 

                                              
using namespace std;

void menu();
void funOne(float rightmost1, float epsilon1); //f(x)=x^2;
void funTwo(float rightmost2, float epsilon2); //f(x)=x^0.5+1;

void menu()
{
	int num;
	float rightMost, epsilon; //variable rightMost, epsilon should be used to pass by value in funOne and funTwo;
	cout<<"Type 1 for function one f(x)=x^2"<<endl;
	cout<<"Type 2 for function two f(x)=x^0.5+1"<<endl;
	cout<<"Type 3 for quit"<<endl;
	cout<<"Type other number than 1 or 2 or 3, menu will repeat"<<endl;
	cout<<"Now enter your function(choose from 1-3): "<<endl;
	cin>>num;
	
	if (num==1) {
		cout<<"Function chosen: "<<num<<endl;
		cout<<"Rightmost x: ";
		cin>>rightMost;
		cout<<"Epsilon: ";
		cin>>epsilon;
		funOne(rightMost, epsilon);
		menu();
	}

	if (num==2) {
		cout<<"Function chosen: "<<num<<endl;
		cout<<"Rightmost x: ";
		cin>>rightMost;
		cout<<"Epsilon: ";
		cin>>epsilon;
		funTwo(rightMost, epsilon);
		menu();
	}

	if (num!=1 && num!=2 && num!=3) { //if number is not in range 1-3, the program need to show an error message and ask the user to prompt the number again;
		cout<<"Error: 404. The program will repeat the menu."<<endl;
		menu();
	}

}

void funOne(float rightmost1, float epsilon1) //function one: f(x)=x^2; Note also funOne is pass by value; 
{
	int i=1;	
	float width, length, delta, sumUp, sumLo, upperSum, lowerSum;
	width=rightmost1/i; //The variable width calculates the width for each rectangle divided. Width of each divided rectangle will always be the same.
	length = pow(width, 2); //Because this function is f(x)=x^2; thus the length for the rectangle is x^2; however, in the end, I didn't use the length in my algorithm. This is just for clarification. 
	delta=width*rightmost1*rightmost1; //delta calculates the delta from (upperSum-lowerSum), which is the last rectangle from the function f(x)=x^2;
	//doing the math, delta(last rectangle: area=width*length --> area=width*rightmost1*rightmost1);
	
	while(delta>epsilon1){ //From the while loop, if (upperSum-lowerSum)>epsilon, we need to divide the rectangle one more time;
		i++;
		width=rightmost1/i; //Thus, the new width after being divided one more time will be rightmost1/i;
		delta=width*rightmost1*rightmost1; //Calculate the delta again;
	}
	int j=1;
	sumUp=0;
	for (j=1; j<=i; j++) {
		float lengthEachUp = pow (width*j, 2); // LengthEachUp is a variable, which is (width*j)^2, which calculates the first, second, third... rectangle's length;
		upperSum = width* lengthEachUp; //each rectangular area = width * (width*j)^2
		sumUp=sumUp+upperSum; //sumUp variable is to calcualte the first, second, third..up to ith rectangle's total area summation; 
		}

	int k=1;
	sumLo=0;
	for (k=1; k<=i-1; k++){
		float lengthEachLo=pow(width*k, 2); //length of each sumlow's rectangtle's length;
		lowerSum=width*lengthEachLo; //lowerSum: calculates each rectangle's lowerSum;
		sumLo=sumLo+lowerSum; //sumLo: calculates the first, second, third.. up to (i-1)th rectangle's lower area's summation; 
	}

	if (i>=2000 && delta>epsilon1){
		cout<<"Please note that this calculation might have error."<<endl;
	}
	
	cout<<endl;
	cout<<"Number of intervals needed: "<<i<<endl;
	cout<<fixed;
	cout<<"Upper sum: "<<setprecision(4)<<sumUp<<endl; //The sums should be displayed with four decimal places; 
	cout<<"Lower sum: "<<setprecision(4)<<sumLo<<endl;
}

void funTwo(float rightmost2, float epsilon2)
{
	int i=1;
	int j=1;

	float width, delta, upperSum, sumUp, sumLo;
	width=rightmost2/i; //The width for each rectangle from the second function f(x)=x^0.5+1;
	delta=rightmost2*pow(rightmost2,0.5)/i; //delta from the function f(x)=x^0.5+1 would be the last rectangle from the upper sum minus the last rectangle from the lower sum;
	//Math behind it:
	//delta = the last rectangle from the upper sum - the first rectangle from the lower sum;
	//delta = ((rightmost2/i) * (rightmost2^0.5+1)) - ((rightmost2/i) * 1);
	//delta = (rightmost2/i) * (rightmost2^0.5+1) - (rightmost2/i);
	//delta = (rightmost2/i) * (rightmost2^0.5+1-1);
	//delta = (rightmost2*rightmost2^0.5)/i;

	while(delta>epsilon2){
		i++;
		width=rightmost2/i;
		delta=rightmost2*pow(rightmost2,0.5)/i;
	}

	upperSum=0;
	sumUp=0;
	for (j=1; j<=i; j++){
		upperSum=width*(pow(width*j, 0.5)+1); //upperSum calculates the first, second... up to ith rectangle's individual area;
		sumUp=sumUp+upperSum; //sumUp calculates the upperSum's summation from the first, second... up to ith rectangle's summation; 
	}
	sumLo=sumUp-delta; //sumLo calculates the total lowerSum's summation;

	if (i>=2000 && delta>epsilon2){
		cout<<"Please note that this calculation might have error."<<endl;
	}
	cout<<endl;
	cout<<"Number of intervals needed: "<<i<<endl;
	cout<<fixed;
	cout<<"Upper sum: "<<setprecision(4)<<sumUp<<endl; //The sums should be displayed with four decimal places; 
	cout<<"Lower sum: "<<setprecision(4)<<sumLo<<endl;
}

int main() {
	menu();
}
