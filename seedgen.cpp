#include <iostream>
#include <cstdlib>  
#include <cmath>    

int main() {
    unsigned int seed;
    int length;
    
    std::cout << "Enter a seed value: ";
    std::cin >> seed;

    std::cout << "Enter the length of the random number (number of digits): ";
    std::cin >> length;


    srand(seed);

    int minValue = pow(10, length - 1); 
    int maxValue = pow(10, length) - 1; 


    int randomNumber = minValue + rand() % (maxValue - minValue + 1);

    std::cout << "Random number with " << length << " digits based on seed " << seed << ": " << randomNumber << std::endl;



    return main();
}
