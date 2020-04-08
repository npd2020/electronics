#include <iostream>
#include <fstream>
#include <cmath>
#define M_PI 3.141592653589793

using namespace::std;

void numbers(int& counterStart, int& counterEnd, ifstream& input,double crackDist) {

	double numberLast;
	double number;
	double idle;
	counterStart = 0;
	counterEnd = 0;
	bool one = true;

	input >> idle;
	input >> number;

	for (int i = 0; true; i++) {

		numberLast = number;
		input >> idle;
		input >> number;

		if (fabs(number - numberLast) > crackDist) {

			if (counterStart == 0) counterStart = i;
			else if (one) one = false;
			else {
				counterEnd = i;
				break;
			}

		}

		///////////////
		if (i % 100) cout << "\a";
		///////////////

		if ((char)idle == 'e') cout << "bad :-(" << endl;
	}

	counterStart++;

}

void dataRead(double* data, int counterStart, int counterEnd, ifstream& input,double& step, double& period) {

	double idle;
	double startPeriod;

	for(int i=0;i< counterStart;i++){
		input >> idle;
		input >> idle;
	}

	input >> startPeriod;

	int size = counterEnd - counterStart+1;
	for (int i = 0; i < size; i++) {
		input >> data[i];
		input >> idle;
	}
	input >> idle;
	input >> period;
	input >> idle;
	input >> step;

	step -= period;//взнаємо крок з яким запмсані дані в надії що після періоду є ще хочаб два рядочка з даними
	period = period - startPeriod - step;

}

double coefficientSin(double* data, int size, double step, double period,int number) {

	double ret = 0;
	double frequency = 2 * M_PI * number / period;


	for (int i = 0; i < size - 1; i++) {

		ret += (data[i] + data[i + 1]) * sin(frequency * (((double)i + 0.5) * step));

	}

	ret *= period;

	return ret;
}

double coefficientCos(double* data, int size, double step, double period, int number) {

	double ret = 0;
	double frequency = 2 * M_PI * number / period;


	for (int i = 0; i < size - 1; i++) {

		ret += (data[i] + data[i + 1]) * cos(frequency * (((double)i + 0.5) * step));

	}

	ret *= period;

	return ret;
}


int main()
{
 //   //////////////////////////////
	//ofstream T;
	//T.open("Test.txt");
	//
	//for (int i = 0; i < 10000; i++) {

	//	T<< i*4/100000.0 << "\t";

	//	if ((i*10/3205) % 2) T << 100 << endl;
	//	else T << -100 << endl;

	//}
	//T.close();
	/////////////////////////////////

	char inputName[] = "Test.txt";
	char outputName[]= "Res.txt";
	int const number_of_coefficients = 211;
	double crackDist = 0.025;
	int counterStart;//нумерується з 0
	int counterEnd;

	ifstream input;
	ofstream output;
	
	input.open(inputName);
	numbers(counterStart, counterEnd, input, crackDist);
	input.close();

	cout << counterStart << endl;
	cout << counterEnd << endl;
	cout << "----------" << endl;

	double step=0;
	double period=0;
	double* data;
	data = new double[counterEnd - counterStart + 1];

	input.open(inputName);
	dataRead(data, counterStart, counterEnd, input, step, period);
	output.close();

	for (int i = 0; i < counterEnd - counterStart + 1; i++) {
		cout << data[i] << endl;
	}

	cout << "-------------" << endl;
	cout <<"step ="<< step<<endl;
	cout <<"period ="<< period << endl;

	double coefficientsin[number_of_coefficients];
	double coefficientcos[number_of_coefficients];

	for (int i = 0; i < number_of_coefficients; i++) {

		coefficientsin[i] = coefficientSin(data, counterEnd - counterStart + 1, step, period, i);
		coefficientcos[i] = coefficientCos(data, counterEnd - counterStart + 1, step, period, i);

	}

	output.open(outputName);

	output << "Coef. sin \t Coef. cos" << endl;

	for (int i = 0; i < number_of_coefficients; i++) {

		output << coefficientsin[i] << "\t \t" << coefficientcos[i]<<endl;

	}

	output.close();

	delete[] data;
}
