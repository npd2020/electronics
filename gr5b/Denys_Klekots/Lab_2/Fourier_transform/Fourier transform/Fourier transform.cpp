#include <iostream>
#include <fstream>
#include <cmath>
#define M_PI 3.141592653589793

using namespace::std;

double const crackDist = 0.025;
int const Average = 11;//завжди не парне

void numbers(int& counterStart, int& counterEnd, ifstream& input) {

	double numberLast;
	double number;
	double idle;
	counterStart = 0;
	counterEnd = 0;
	//bool one = true;
	bool one = false;//прораховуємо лише половину імаульса

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

double avar(int from, int to, double* data) {

	double ret = 0;
	bool let = true;

	for (int i = from; i <= to; i++) {
		
		ret += data[i];

	}

	for (int i = from; i <= to; i++) {//не усереднюємо стрибок

		for (int j = i + 1; j <= to; j++)
			if (fabs(data[i] - data[j]) > crackDist) let = false;
	}

	if (let) ret /= (to - from + 1);//не усереднюємо стрибок
	else ret = data[(from+to)/2];

	return ret;
}

void travelingAverage(double* &data, int size) {

	double* newdata;
	newdata = new double[size];

	for (int i = 0; i < Average / 2; i++)//краї не усереднюємо
		newdata[i] = data[i];

	for (int i = size - Average / 2; i < size; i++)//краї не усереднюємо
		newdata[i] = data[i];

	for (int i = Average / 2; i < size - Average / 2; i++)
		newdata[i] = avar(i - Average / 2, i + Average / 2, data);

	delete[] data;

	data = newdata;
}

void dataRead(double* &data, int counterStart, int counterEnd, ifstream& input,double& step, double& period) {

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

	travelingAverage(data, size);

	//////////////////////////////////////////////

	ofstream T;
	T.open("Control.txt");

	for (int i = 0; i < size; i++)
		T << i * step << "\t" << data[i]<<endl;

	T.close();
	//////////////////////////////////////////////


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

double coefficients(char* inputName, int number_of_coefficients,double* amplitude, double* phase) {

	int counterStart;//нумерується з 0
	int counterEnd;

	ifstream input;

	input.open(inputName);
	numbers(counterStart, counterEnd, input);
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

	/////////////////////////////////////////
	//ofstream T;
	//T.open("Coef.txt");


	//for (int i = 0; i < number_of_coefficients; i++)
	//	T << coefficientsin[i] << "\t" << coefficientcos[i] << endl;
	/////////////////////////////////////////

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

			ret += amplitude[i] * cos(frequency * i * x - phase[i]);

		}

		T << x << "\t" << ret << endl;

		x += step;
	}
	

}

void write(char* name) {

	ofstream T;
	T.open(name);

	for (int i = 0; i < 100000; i++) {

		if ((i*10 / 3205) % 2) T << (double)4*i/100000.0<<"\t"<< -0.0525171*10000 <<endl;
		else T << (double)4*i/100000.0 << "\t" << 0.0525171*10000 << endl;

	}
	T.close();

}

int main()
{

	char inputName[] = "CH1.txt";
	char outputName[]= "CH2.txt";

	write(inputName);

	char result[] = "Result.txt";

	//int const number_of_coefficients = 211;
	int const number_of_coefficients = 160;

	//////////////////////////////
	//write(inputName);
	//////////////////////////////

	double amplitudeIn[number_of_coefficients];
	double phaseIn[number_of_coefficients];

	double amplitudeOut[number_of_coefficients];
	double phaseOut[number_of_coefficients];

	double frequencyIn = coefficients(inputName, number_of_coefficients, amplitudeIn, phaseIn);
	double frequencyOut = coefficients(outputName, number_of_coefficients, amplitudeOut, phaseOut);

	double frequency = (frequencyIn + frequencyOut) / 2;

	ofstream resultFile;

	resultFile.open(result);

	resultFile << "frequency \t coefficient \t phase" << endl;

	double* reductionAnplitude;
	double* differencePhase;

	reductionAnplitude = new double[number_of_coefficients];
	differencePhase = new double[number_of_coefficients];

	for (int i = 0; i < number_of_coefficients; i++) {

		reductionAnplitude[i] = amplitudeIn[i] / amplitudeOut[i];
		differencePhase[i] = phaseOut[i] - phaseIn[i];

		if (differencePhase[i] < 0) differencePhase[i] += M_PI;//різниця фаз має бути додатньою від 0 до 3.1415...

	}

	for (int i = 0; i < number_of_coefficients; i++) {

		resultFile << i * frequency << "\t" << reductionAnplitude[i] << "\t";
		resultFile << differencePhase[i] << endl;

	}

	graph(amplitudeIn, phaseIn, number_of_coefficients, frequency);

	delete[] reductionAnplitude;
	delete[] differencePhase;
}
