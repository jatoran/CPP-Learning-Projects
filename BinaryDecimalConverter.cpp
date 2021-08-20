#include <iostream>

using namespace std;

long long int getInteger(){
  long long int input;
  cin >> input;
  return input;
}

int getConversionType(){
  cout << "Choose Conversion Type:\n"
  "(1) Binary to Decimal\n"
  "(2) Decimal to Binary\n";
  int input = getInteger();
  
  if (input == 1) return input;
  else if (input == 2){
    input = 0;
    while((input != 1) && (input != 2)) {
      cout << "Enter Method (1) or (2):\n";
      input = getInteger();
    }
    return input + 1;
  }
  else return getConversionType();
}

void binaryToDecimal(long long int binaryValue){
  int powerOfTwo = 1;
  int decimalValue = 0;
  while (binaryValue != 0){
    decimalValue += ((binaryValue % 10) * powerOfTwo);
    binaryValue /= 10; 
    powerOfTwo *= 2; 
  }
  cout << decimalValue;
}

void decimalToBinaryM1(int decimalValue){
  int binaryValue[20];
  int i = 0;
  while (decimalValue > 0){
    binaryValue[i] = decimalValue % 2;
    decimalValue /= 2;
    i++;
  }
  for (int j = i - 1; j >= 0; j--) {
    cout << binaryValue[j];
  }
}

int findPower(int decimalValue){
  int power = 1;
  while (power * 2 < decimalValue) power *= 2;
  return power;
}

void decimalToBinaryM2(int decimalValue){
  int binaryValue[20];
  int powerOfTwo = findPower(decimalValue);

  while (powerOfTwo > 0){
    if (decimalValue >= powerOfTwo) {
      cout << 1;
      decimalValue -= powerOfTwo;
    }
    else cout << 0;
    powerOfTwo /= 2;
  }
}

void convertValue(int conversionType){
  cout << "Enter Decimal or Binary Value\n";
  long long int value = getInteger();
  if (conversionType == 1) binaryToDecimal(value);
  else if (conversionType == 2) decimalToBinaryM1(value);
  else if (conversionType == 3) decimalToBinaryM2(value);
}

int main(){
  convertValue(getConversionType());
  return 0;
}