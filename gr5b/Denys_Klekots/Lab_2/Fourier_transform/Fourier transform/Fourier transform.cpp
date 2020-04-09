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

		/////////////////
		//if (i % 100) cout << "\a";
		/////////////////

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

	ret /= size;

	return ret;
}

double coefficientCos(double* data, int size, double step, double period, int number) {

	double ret = 0;
	double frequency = 2 * M_PI * number / period;


	for (int i = 0; i < size - 1; i++) {

		ret += (data[i] + data[i + 1]) * cos(frequency * (((double)i + 0.5) * step));

	}

	ret /= size;

	return ret;
}

double coefficients(char* inputName, int number_of_coefficients,double crackDist,double* amplitude, double* phase) {

	int counterStart;//нумерується з 0
	int counterEnd;

	ifstream input;

	input.open(inputName);
	numbers(counterStart, counterEnd, input, crackDist);
	input.close();

	/*cout << counterStart << endl;
	cout << counterEnd << endl;
	cout << "----------" << endl;*/

	double step = 0;
	double period = 0;
	double* data;
	data = new double[counterEnd - counterStart + 1];

	input.open(inputName);
	dataRead(data, counterStart, counterEnd, input, step, period);
	input.close();

	/*for (int i = 0; i < counterEnd - counterStart + 1; i++) {
		cout << data[i] << endl;
	}

	cout << "-------------" << endl;
	cout << "step =" << step << endl;
	cout << "period =" << period << endl;*/

	double* coefficientsin;
	double* coefficientcos;

	coefficientsin = new double[number_of_coefficients];
	coefficientcos = new double[number_of_coefficients];

	for (int i = 0; i < number_of_coefficients; i++) {

		coefficientsin[i] = coefficientSin(data, counterEnd - counterStart + 1, step, period, i);
		coefficientcos[i] = coefficientCos(data, counterEnd - counterStart + 1, step, period, i);

	}

	for (int i = 0; i < number_of_coefficients; i++) {

		amplitude[i] = sqrt(coefficientsin[i] * coefficientsin[i] + coefficientcos[i] * coefficientcos[i]);

		phase[i] = atan(coefficientsin[i] / coefficientcos[i]);

	}


	delete[] coefficientsin;
	delete[] coefficientcos;
	delete[] data;

	return 2 * M_PI / period;
}

void graph(double* amplitude, double* phase, int number_of_coefficients, double frequency) {

	ofstream T;

	T.open("graph.txt");

	double x = 0;
	double step=0.00001;
	double ret;
	while (x < 0.1) {

		ret = 0;

		for (int i = 0; i < number_of_coefficients; i++) {

			ret += amplitude[i] * cos(frequency * i * x + phase[i]);

		}

		T << x << "\t" << ret << endl;

		x += step;
	}
	

}

void write(char* name) {

	ofstream T;
	T.open(name);

	for (int i = 0; i < 100000; i++) {

		if ((i*10 / 3205) % 2) T << (double)4*i/100000.0<<"\t"<<1<<endl;
		else T << (double)4*i/100000.0 << "\t" << -1 << endl;

	}
	T.close();

}

int main()
{

	char inputName[] = "name";
	char outputName[]= "CH2.txt";

	write(inputName);

	char result[] = "Result.txt";

	int const number_of_coefficients = 211;
	//int const number_of_coefficients = 211;
	double crackDist = 0.025;

	//////////////////////////////
	//write(inputName);
	//////////////////////////////

	double amplitudeIn[number_of_coefficients];
	double phaseIn[number_of_coefficients];

	double amplitudeOut[number_of_coefficients];
	double phaseOut[number_of_coefficients];

	double frequencyIn = coefficients(inputName, number_of_coefficients, crackDist, amplitudeIn, phaseIn);
	double frequencyOut = coefficients(inputName, number_of_coefficients, crackDist, amplitudeOut, phaseOut);

	double frequency = (frequencyIn + frequencyOut) / 2;

	ofstream resultFile;

	resultFile.open(result);

	resultFile << "frequency \t coefficient \t phase" << endl;

	for (int i = 0; i < number_of_coefficients; i++) {

		resultFile << i * frequency << "\t" << amplitudeIn[i] / amplitudeOut[i] << "\t";
		resultFile << phaseOut[i] - phaseIn[i] << endl;


	}


	graph(amplitudeIn, phaseIn, number_of_coefficients, frequency);
	

}
