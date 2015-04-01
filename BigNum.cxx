// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class

// Slaton Ransom Spangler
// HW 3

#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		
		digits = new unsigned int[DEFAULT_CAPACITY]; // Make a new array
		positive = true; // zero is positive
		used = 1; // zero has one digit
		capacity = DEFAULT_CAPACITY;
		digits[0] = 0; // put zero in the one's place.
		
	}    

	BigNum::BigNum(int num)
	{
		
		capacity = DEFAULT_CAPACITY; // 20 is big enough for ints
		digits = new unsigned int[capacity];
		
		int temp;
		
		if (num < 0){
			positive = false;
			temp = -num; // without this, the % operator produces negative numbers for the array.
			}
		else{
			positive = true;
			temp = num;
			}
		
		used = 0;
		
		if(temp != 0){
			
			while(temp != 0){
				digits[used] = (temp % 10); //take one down, pass it around
				temp = (temp/10); //chop!
				used++;
			}
		}
		
		else{
			used = 1;
			digits[0] = 0;
		}
		
		
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{

		capacity = DEFAULT_CAPACITY;
		
		while (strin.length() > capacity){
			capacity = (capacity * 2); // strings can be long.
		}
		
	
		
		digits = new unsigned int[capacity];
		
		int index = 0; // used for the for loop. we go to strin[1] if the first value is a "-" sign.
		used = 0;
		
		positive = true;
		
		if(strin[0] == 45){ // if the first character is "-"
			positive = false;
			index++;
		}
		
		
		
		// while there's zeroes, increment
		// until string length
		while(strin[index] == 48 && (strin.length())!= index){
			index++;

		}
		
		unsigned int in = index;
		if(in == strin.length()){
			used = 1;
			digits[0] = 0;
		}
		
		else{
		
			for(int i = (strin.length()-1); i >= index; i--){
				digits[used] = (strin[i]-48);
				used++;
			}
		}


	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		used = anotherBigNum.used; // This is identical to the HW2 copy constructor
		capacity = anotherBigNum.capacity; 
		digits = new unsigned int[capacity];  
		positive = anotherBigNum.positive;
		
		for(unsigned int i = 0; i < used; i++){ 
			digits[i] = anotherBigNum.digits[i];}
    }

    BigNum::~BigNum()
    {
		delete [] digits; //delete the array of digits
    }
    
    void BigNum::resize(unsigned int n) // the same as HW2
	{
		if(n > capacity){ // no need to downsize!
		
			unsigned int* digits_old = digits; 

			digits = new unsigned int[n]; 
	
			for(unsigned int i = 0; i < used; i++){ 
				digits[i] = digits_old[i];}
	
			delete [] digits_old; 
	
			capacity = n; 
	}
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		
	if (&anotherBigNum == this){ // again, identical to HW2
		return *this;
		}
	
	else{
		
		delete [] digits; 
		
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];   
		
		for(unsigned int i = 0; i < used; i++){
			digits[i] = anotherBigNum.digits[i];}
		
		return *this;
		
			
	}
}
  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		*this = *this + addend;
		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		*this = *this - subtractand;
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = (*this*multiplicand);
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		*this = (*this + 1);
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		*this = (*this - 1);
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b, BigNum& result)
	{

		int diff = 0;
		int carry = 0;
		result.used = a.used;
		
		for(unsigned int i = 0; i < (a.used); i++){
			
			diff = a.digits[i];
		
			if(i < b.used){
				diff -= b.digits[i];
			}
		
			diff -= carry;
				
			if(diff < 0){
				diff += 10;
				carry = 1;
			}
			else{
				carry = 0;
			}
		
			result.digits[i] = diff;
			
		}
		
		while(digits[result.used-1] == 0){
			result.used --;
		}
		return result;
		
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		// This is really slow, but I'm through trying my other
		// implementation method. 
		BigNum sum;
		BigNum abs = b;
		abs.positive = true;
		used = (a.used + b.used);
		for(BigNum i = 0; i < abs; ++i){
			sum += a;
			
		}
		while(digits[used-1] == 0){
			used --;
		}
		*this = sum;
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
	
		BigNum result;

		int carry = 0;
		int sum;
		unsigned int count = 0;

		if(a.used + b.used > result.capacity){
			result.resize(result.capacity*2);
		}
		
		if(!a.positive && b.positive){
			BigNum abs = a;
			abs.positive = true;
			result = (b - abs);
			return &result;
			
		}
		else if(!b.positive && a.positive){
			BigNum abs = b;
			abs.positive = true;
			result = (a - abs);
			return result;
			
		}

		
		else{

			if(!a.positive && !b.positive){
				result.positive = false;
			}
			
			while(count < a.used || count < b.used){
		
		
				sum = 0;
			
				if(count >= a.used){
					sum += b.digits[count];
				}
				else if(count >= b.used){
					sum += a.digits[count];
				}
				else{
					sum += (a.digits[count] + b.digits[count]);
				}
			
				sum += carry;
		
				if(sum > 9){
					carry = (sum / 10);
					result.digits[count] = (sum % 10);
				}
			
				else{
					carry = 0;
					result.digits[count] = sum;
				}
		
			count ++;
			}
		}
		
		if(carry > 0){
			result.digits[count] = carry;
			count++;
		}
		
		result.used = count;	
		return result;	
	} 

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		
		if(a.used + b.used > result.capacity){
			result.resize(result.capacity*2);
		}
		
		if(a == b){
			result = 0;
			
		}
		
		else if(a.positive && b.positive){
			if(a > b){
				result = result.diff(a, b, result);
			}
			else if (a < b){
				result = result.diff(b, a, result);
				result.positive = false;
			}
		}
		
		else if(!a.positive && b.positive){
			BigNum abs = a;
			abs.positive = true;
			result = (abs + b);
			result.positive = false;
		}
		
		else if(a.positive && !b.positive){
			BigNum abs = b;
			abs.positive = true;
			result = (a + abs);
		}
		
		else if(!a.positive && !b.positive){
			if(a > b){
				result = result.diff(b, a, result);
			}
			if(b > a){
				result.positive = false;
				result = result.diff(a, b, result);
			}
		}
				
		
		
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		
		BigNum result = 0;
		
		if(a.used + b.used > result.capacity){
			result.resize(result.capacity*2);	
		}
		if(a.positive && b.positive){
			if(a > b){
				result = result.mult(a, b);
				
			}
			else if (a < b){
				result = result.mult(b, a);
				
			}
		}
		
		else if(!a.positive && b.positive){
			BigNum abs = a;
			abs.positive = true;
			if(abs > b){
				result = result.mult(abs, b);
				
			}
			else if(abs < b){
				result = result.mult(b, abs);
			
			}
			result.positive = false;
		}
		
		else if(a.positive && !b.positive){
			BigNum abs = b;
			abs.positive = true;
			if(a > abs){
				result = result.mult(a, abs);
				
			}
			else if(a < abs){
				result = result.mult(abs, a);
				
			}
			result.positive = false;
		}
		
		else if(!a.positive && !b.positive){
			if(a < b){
				result = result.mult(a, b);
				
			}
			else if (a > b){
				result = result.mult(b, a);
				
			}
		}
		
		
				
			 
		
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if((a < b) == false && (a == b) == false){
			return true;
		}
		else{
			return false;
		}
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		if(a > b || a == b){
			return true;
		}
		else{
			return false;
		}
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		
		if(a.positive == false && b.positive == true){
			return true;
		}
		
		else if(a.positive == true && b.positive == false){
			return false;
		}
		
		else if(a.positive == false && b.positive == false){
			if(a.used > b.used){
				return true;
			}
			else if(a.used < b.used){
				return false;
			}
			else{
				for(int i = a.used - 1; i >= 0; i--){
					if(a.digits[i] < b.digits[i]){
						return false;
					}
				}
				return true;
			}
			
		}
		else{
			if(a.used < b.used){
				return true;
			}
			else if(a.used > b.used){
				return false;
			}
			else{
				for(int i = a.used - 1; i >= 0; i--){
					if(a.digits[i] > b.digits[i]){
						return false;
					}
					else if(a.digits[i] < b.digits[i]){
						return true;
					}
					
				}
				return false;
			}
			
		}
			
		
			

	}
	bool operator<=(const BigNum& a, const BigNum& b)
	{
		if(a < b || a == b){
			return true;
		}
		else{
			return false;
		}
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if (a.used != b.used || a.positive != b.positive){
			return false;
		}
		
		for(unsigned int i = 0; i < a.used; i++){
			if(a.digits[i] != b.digits[i]){
				return false;
			}
		}
		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
		
	}

	// trim leading zeros
	void BigNum::trim()
	{
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		if(bignum.positive == false){
			os << "-";
		}
		for(int i = bignum.used-1; i >= 0; i--){
			
		os << bignum.digits[i];
	}
		
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string str;
		is >> str;

		BigNum temp = str;
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }



#endif



