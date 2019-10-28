// Hector Rizo
// Assignment 4


// 
// 

#include <iostream>
#include <cstring>
#include "myInt.h"

using namespace std;
// ------------CONSTRUCTORS ------------
MyInt :: MyInt(){
	capacity = 1;
	size = 1;
	number = new char [capacity];
	number[0] = 48; // 48 is the ascii value for 0
}

MyInt :: ~MyInt(){
	if(number != NULL){ // checking if pointer is used
		delete [] number; 
		number = NULL;
	}
}

MyInt :: MyInt (const int& input){	
	int num = 0;
	if (input <0)
		num = 0;
	else
		num = input; // making copy of input
	
	capacity = numDigits(input); // setting capacity equal to num of digits
	size = capacity;
	number = new char [capacity];
	int copy = input; // this value stores the copy from the integer
	
	for(int i =size-1; i>=0; i--){
		number[i] = copy%10 + 48;
		copy = copy/10; // shrinking interger by one digit
	}
}

MyInt:: MyInt ( const char* numbers){
	
	bool reset = 0; // this variable is false until a invalid char is met
	int index = 0;
	int count = 0;
	bool stop = 0;
	for(int i = 0; i <strlen(numbers); i++){
		if(numbers[i] != 48){stop = 1;}
		if(numbers[i] == 48 && stop == 0){
			index = i+1;
			count++;
		}
		else continue;
	}
	
	
	
	capacity = strlen(numbers) - count; // taking null charector into account
	size = capacity;
	number = new char[capacity];
	
	for(int i = 0; i < size; i++){
		if(numbers[i] >= 48 && numbers[i] <= 57)
			number[i] = numbers[index + i];
		else{	reset = 1;		break;}
	}
	if(reset == 1){
		number[0] = 48;
		for(int i = 1; i < size; i++)
			number[i] = '\0';
		
		size =1;	
		
	}
	
	shrink();
	
}

MyInt :: MyInt (const MyInt& copy){
	size = copy.size;
	capacity = copy.capacity;
	
	number = new char[capacity];
	
	for(int i = 0; i< size; i++)
		number[i] = copy.number[i];
	
}

// -------- HELPER FUNCTIONS --------
int MyInt :: numDigits(const int& input) const{	
	int number = 10; // making a copy of input
	int count = 1; // counting digits always starts at 1
	
	while(number <= input) 
	{
		count++;
		number *= 10;
	}
	
	return count;
}

void MyInt :: shrink(){ 
	char * temp = NULL;
	capacity = size;
	temp = new char [capacity+1];
	for(int i = 0; i<capacity; i++)
		temp[i] = number[i];
	temp[capacity] = '\0';
	delete [] number;
	number = temp;
	temp = NULL;
}

void MyInt :: grow(){
	char * temp = NULL;
	capacity += 5;
	temp = new char [capacity];
	for(int i = 0; i<capacity; i++)
		temp[i] = number[i];
	delete [] number;
	number = temp;
	temp = NULL;
}

void MyInt :: sort (int * result, int digs) const{ 
	int carry = 0; int copy = 0; bool shift = 0; int index=0;
	
	for(int i = digs-1; i >= 1; i--){
		
		if(result[i] > 9){
			copy = result[i];
			result[i] = copy%10;
			carry = (copy/10);
			result[i-1] += carry;
			
		}
		else 
			continue;
	}
	
	carry = 0; copy = 0;
	
	for(int i = 0; i < digs; i++){
		
	
		result[i] += carry; 
		
		
		if(result[i] > 10 ){
			copy = result[i];
			result[i] = copy/10; 
			carry = (copy%10)*10; 
				
		}
		
		
		else if(result[i] == 10){ 
			
			copy = result[i];
			result[i] = copy/10;
			shift = 1;
			index = i;
			
			break;
			
		}
		
		else 
			continue;
	}
	
	
	if (shift == 1){
		for(int i = digs -1; i > index; i--){
			result[i] = result [i -1];
		}
		result[index+1] = 0;
	}
	
	
}

// --------PUBLIC FUNCTIONS ----------
MyInt& MyInt :: operator= (const MyInt& copy){
	delete[] number; // deallocating old set of nubmers
	size = copy.size;
	capacity = copy.capacity;
	number = new char[capacity+1];
	
	for(int i = 0; i< size; i++)
		number[i] = copy.number[i];
	number[capacity] = '\0';
	shrink();
	
	return *this;
}

MyInt MyInt :: operator+ (const MyInt& x) const{ 
	int capacity_copy = this->capacity + x.capacity; // getting new size of copy array
	int loop_size = 0;// this variable will hold the # iterations in copy loop_size
	int arr_size = 0;
	int number_conversion = 0; // this number will hold values tempmorarily for array math
	bool which_arr = 0; // this bool indicates which array is smaller in size
	int hold = 0;
	char * number_copy = new char [capacity_copy]; // this is the resulting number
	
	for(int i = 0; i<capacity_copy; i++){ // initializing array with 0s
		number_copy[i] = 48;
	}
	
	if(this->capacity < x.capacity){
		loop_size = x.capacity;
		arr_size = this->capacity;
		which_arr = 1;
	}									// these if and else set # of iterations in loop
	else{
		loop_size = this->capacity;
		arr_size = x.capacity;
		which_arr = 0;
	}
	
	for(int i = capacity_copy -1; i > capacity_copy - arr_size -1; i--){ // initializing new array with smaller array 
		if(which_arr == 0){
			number_conversion =  x.number[i-loop_size] ;
		}
		else{
			number_conversion = this->number[i-loop_size];
		}
		number_copy[i] = number_conversion;   		
	}	
	
	
	for(int i = capacity_copy -1; i > capacity_copy - loop_size-1 ; i--){ // adding second array to copy array
		
		if(which_arr == 0){
		number_conversion =  this->number[i-arr_size] - 48;
		}
		else{
			number_conversion = x.number[i-arr_size] - 48;
		}
		
		number_copy[i] += number_conversion;
		if (number_copy[i] > 57){
			hold = number_copy[i] - 10;
			number_copy[i-1] += 1; // carrying over value to index
			number_copy[i] = hold;
		}
	}
	
	
	
	int space_count = 0;
	for(int i = 0; i < capacity_copy; i++){ // this for loop counts number of empty spaces
		if(number_copy[i] == 48){
		space_count = i+1;
		}
		else 
			break;
	}
	
	
	capacity_copy = capacity_copy - space_count+1; // adjusting capacity and removing un needed space
	char * function_number = new char [capacity_copy]; // new array adjusted for size
	
	
	
	for(int i = capacity_copy-2; i >= 0; i--){
		function_number[i] = number_copy[i + space_count];
	}
		
	function_number[capacity_copy-1] = '\0';
	
	MyInt obj(function_number);
	delete[] number_copy; delete [] function_number; // deallocating memory
	number_copy = NULL; function_number= NULL;
	
	
	return obj;
}

MyInt MyInt :: operator* (const MyInt& x) const{
	
	int which_arr = 0; // this variable tells which number has more digits -- 0 means they are the same
	
	int top_digits	= x.size;
	
	int bottom_digits = x.size;
	
	int total_digits = x.size + this->size;
	
	
	int * top = 0; int * bottom = 0;
	
	
	
	if(this->size > x.size){
		which_arr = 1; // first number has more digits
		top_digits = this->size;
		bottom_digits = x.size;
		
		top = new int [top_digits];   		// converting to ints
		for(int i = 0; i < top_digits; i++){
			top[i] = this->number[i] - 48;
		}
		
		bottom = new int [bottom_digits];
		for (int i = 0; i < bottom_digits; i++){
			bottom[i] = x.number[i] -48;
		}
			
	}
	
	else if(this->size < x.size){
		which_arr =2;
		top_digits = x.size;
		bottom_digits = this->size;
		
		top = new int [top_digits];   		// converting to ints
		for(int i = 0; i < top_digits; i++){
			top[i] = x.number[i] - 48;
		}
		
		bottom = new int [bottom_digits];
		for (int i = 0; i < bottom_digits; i++){
			bottom[i] = this->number[i] -48;
		}
	}
	
	else{
		
		top = new int [top_digits];   		// converting to ints
		for(int i = 0; i < top_digits; i++){
			top[i] = this->number[i] - 48;
		}
		
		bottom = new int [bottom_digits];
		for (int i = 0; i < bottom_digits; i++){
			bottom[i] = x.number[i] -48;
		}
	}
	
	int ** answer = new int *[bottom_digits]; // dynamic 2d array to hold all rows
	for(int i = 0; i < bottom_digits; i++){
		answer[i] = new int[total_digits];
	}
	
	for(int row = bottom_digits -1; row >= 0; row--){  // initializing all elements
		for(int digit = total_digits-1; digit >= 0; digit--){
			answer[row][digit] = 0;
		}
	}
	
	int * final_answer = new int [total_digits]; // this array holds the sums of all the numbers
	for (int i = 0; i < total_digits; i++){
		final_answer[i] = 0;
	}
	
	int counter = 0; int row_counter = 0;
	for(int row = bottom_digits -1; row >= 0; row--){
		for(int digit = top_digits-1; digit >= 0; digit--){ // adding row by row within 2d array
			
			counter++;
			answer[row][(total_digits-1) - counter+ 1 - row_counter] = top[digit] * bottom[row];
			
		}
		counter = 0; row_counter++;
		sort(answer[row], total_digits);  // accounting for carries
	}
	
	
	
	for(int i = 0; i < bottom_digits; i++){  // storing all the sums in int array
		for(int j = 0; j < total_digits; j++){
			final_answer[j] += answer[i][j];
		}
	}
	 
	 
	
	sort(final_answer, total_digits); // accounting for carrys
	
	
	char * conversion_arr = new char [total_digits+1];
	for(int j = 0; j < total_digits; j++){
		conversion_arr[j] = 0;
		conversion_arr[j] +=final_answer[j] + 48; // converting to char array
	}
	
	conversion_arr[total_digits] = '\0'; // adding null char

	
	
	MyInt WIN(conversion_arr);
	
	for(int i = 0; i < bottom_digits; i++){ // deallocatingall pointes
		delete [] answer[i];
	}
	delete [] answer;
	
	delete [] top; 
	delete [] bottom;
	delete [] final_answer;
	delete []conversion_arr ;
	
	return WIN;
	
	
}

MyInt& MyInt :: operator++(){
	*this = *this + 1;
	return *this;	
}

MyInt MyInt :: operator++ (int this_was_terribble){
	MyInt temp = *this;
	*this = *this +1;
	return temp;
}

//---------FRIEND FUNCTIONS ------------
ostream& operator<< ( ostream& out,const MyInt& obj){
	for (int i = 0; i<obj.size; i++)
		out << obj.number[i];
	return out;
}

istream& operator >> (istream& in, MyInt& obj){
	int cap = 1;
	int index = 0; // this keeps track of array index
	char * set = new char[cap];
	char *copy = 0; // this is used to grow array
	char value; // this holds each digit
	int check = 0;
	char trash;
	
	while(check != 10){
		if(index ==  cap-1){  // growing array based on needed space
			cap += 1;  
			copy = new char[cap];
			for(int i = 0; i<index; i++)
				copy[i] = set[i];
			copy[index] = '\0';
			delete[] set;
			set = copy;
			copy =0;
			
		}

		check = in.peek();
		if(index == 0){
			if (check == 32 || check == 10){
				in.get(trash);				
			}
			else if(check < 48 || check > 58) break;
			
			else {
				in.get(set[index]);
				++index;
			}
		}
		
		else {
			if(check == 32 || check == 10 ){ in.ignore();break;}
			
			else if(check < 48 || check > 57){ break;} // if an element is not a nuber it is isnt touched
			
			else{
				in.get(set[index]);
				++index;
			}
		}
				
	}
	
	
	MyInt that(set); // initializing with char array
	obj = that; // copying temporary object data to cin value
	
	delete[]set;
	set = 0;
	
	return in;
}

bool operator< (const MyInt& x, const MyInt& y){
	bool result = 0; // starting at false
	if(x.size < y.size) // if it size of char array is smaller 
		result = 1;
	
	else if(x.size == y.size){ // checking every index of array
		for(int i = 0; i<x.size;i++){
			if(x.number[i] < y.number[i]){ 
				result = 1; break;}
		}
	} 
	return result;
}

bool operator== (const MyInt&x, const MyInt& y){
	bool result = 0;
	if (x.size == y.size){
		for(int i = 0; i < x.size; i++){
			if(x.number[i] == y.number[i])
				result = 1;
			else
				result = 0;
		}
	}
	
	return result;
}

bool operator> (const MyInt& x, const MyInt& y){
	bool result = 1;
	if (x<y || x==y)
	 result = 0;
	
	return result;
}

bool operator!= (const MyInt& x, const MyInt& y){
	bool result = 1;
	if(x==y)
		result = 0;
	
	return result;
}

bool operator<= (const MyInt&x, const MyInt& y){
	bool result = 0;
	if(x<y || x==y)
		result = 1;
	
	return result;
}

bool operator >= (const MyInt&x, const MyInt& y){
	bool result = 0;
	if(x>y || x== y)
		result = 1;
	
	return result;
}
