// Hector Rizo
// Assignment 4
// 
// 

#include <iostream>
using namespace std;

class MyInt{
// stream overloads	
	friend ostream& operator<< ( ostream& out,const MyInt& obj);
	friend istream& operator>> (istream& in, MyInt& obj);
	
// relational overloads
	friend bool operator< (const MyInt& x, const MyInt& y);
	friend bool operator== (const MyInt& x, const MyInt& y);
	friend bool operator> (const MyInt& x, const MyInt& y);
	friend bool operator!=(const MyInt& x, const MyInt& y);
	friend bool operator <= (const MyInt&x, const MyInt& y);
	friend bool operator >= (const MyInt&x, const MyInt& y);
	
	private:
		char * number; // this stores the values entered by user
		int size; // number of indicies used in array
		int capacity; // max size of the array	
		int numDigits(const int& input)const; // this function counts digits in number
		void grow();
		void shrink();
		void sort(int * result, int digs) const;
		
	public:
		MyInt();
		~MyInt(); // deallocating char array
		MyInt(const int& input);
		MyInt ( const char* numbers);
		MyInt (const MyInt& copy);
		MyInt& operator= (const MyInt& copy);
		MyInt operator+ (const MyInt& x)const;
		MyInt operator* (const MyInt& x) const;
		MyInt& operator++();
		MyInt operator++ (int this_was_terribble);
		
	
	
};

