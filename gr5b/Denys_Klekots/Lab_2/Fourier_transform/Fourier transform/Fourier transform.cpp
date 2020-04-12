#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#define M_PI 3.141592653589793

using namespace std;

int const Average = 11;//завжди не парне
bool letGA;//генеральне, чи біжуче середнє, це допоміжна змінна, використовується дальше
double crackDist;

void showVector(vector<string> v, char* name) {
	ofstream GoodPoints(name);
	int m = v.size();
	for (int i = 0; i < m; i++) {
		GoodPoints << v[i] << endl;
	}
	GoodPoints << "end";

	cout << "OK" << endl;
}

void overwriting(char* baddata, char* clean) {

	ifstream points(baddata);

	vector<string> v;
	vector<string> V;

	string s = "/0", a = "";
	while (s != "") {
		getline(points, s);
		v.push_back(s);
	}
	int n = v.size();
	int m;
	for (int i = 0; i < n; i++) {
		m = v[i].size();
		for (int j = 0; j < m; j++) {
			if (v[i][j] != ',')
				a = a + v[i][j];
		}
		V.push_back(a);
		a = "";
	}
	showVector(V, clean);

}

void numbers(int& counterStart, int& counterEnd, ifstream& input) {

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
	else ret = data[(from + to) / 2];

	return ret;
}

void travelingAverage(double*& data, int size) {

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

void genetalAverage(double* data, int size) {

	double ret = 0;
	int halth;

	for (int i = 0; i < size - 1; i++) {

		if (fabs(data[i] - data[i + 1]) > crackDist) {
			halth = i;
			break;
		}
	}


	for (int i = 0; i < halth; i++)
		ret += data[i];

	ret /= halth;

	for (int i = 0; i < halth; i++)
		data[i] = ret;

	ret = 0;


	for (int i = halth + 1; i < size; i++)
		ret += data[i];

	ret /= halth;

	for (int i = halth + 1; i < size; i++)
		data[i] = ret;
}

void dataRead(double*& data, int counterStart, int counterEnd, ifstream& input, double& step, double& period) {

	double idle;
	double startPeriod;

	for (int i = 0; i < counterStart; i++) {
		input >> idle;
		input >> idle;
	}

	input >> startPeriod;

	int size = counterEnd - counterStart + 1;
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

	if (letGA) genetalAverage(data, size);
	else travelingAverage(data, size);
}

double coefficientSin(double* data, int size, double step, double period, int number) {

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

double coefficients(char* inputName, int number_of_coefficients, double* amplitude, double* phase, int counterStart, int counterEnd) {

	ifstream input;

	double step = 0;
	double period = 0;
	double* data;
	data = new double[counterEnd - counterStart + 1];

	input.open(inputName);
	dataRead(data, counterStart, counterEnd, input, step, period);
	input.close();

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

int main()
{
	char badinputName[] = "F0000CH1.txt";
	char badoutputName[] = "F0000CH2.txt";

	char inputName[] = "CH1.txt";
	char outputName[] = "CH2.txt";

	char result[] = "Result.txt";

	int const number_of_coefficients = 40;
	int avar = 11;//завжди не парне
	crackDist = 0.025;


	overwriting(badinputName, inputName);
	overwriting(badoutputName, outputName);

	int counterStart;
	int counterEnd;


	ifstream input;
	input.open(inputName);
	numbers(counterStart, counterEnd, input);
	input.close();

	double amplitudeIn[number_of_coefficients];
	double phaseIn[number_of_coefficients];

	double amplitudeOut[number_of_coefficients];
	double phaseOut[number_of_coefficients];

	letGA = true;
	double frequencyIn = coefficients(inputName, number_of_coefficients, amplitudeIn, phaseIn, counterStart, counterEnd);
	letGA = false;
	double frequencyOut = coefficients(outputName, number_of_coefficients, amplitudeOut, phaseOut, counterStart, counterEnd);

	double frequency = (frequencyIn + frequencyOut) / 2;

	ofstream resultFile;

	resultFile.open(result);

	resultFile << "frequency \t coefficient \t phase" << endl;

	double* reductionAnplitude;
	double* differencePhase;

	reductionAnplitude = new double[number_of_coefficients];
	differencePhase = new double[number_of_coefficients];

	for (int i = 0; i < number_of_coefficients; i++) {

		reductionAnplitude[i] = amplitudeOut[i] / amplitudeIn[i];
		differencePhase[i] = phaseOut[i] - phaseIn[i];

	}

	char In[] = "In.txt";
	char Out[] = "Out.txt";

	for (int i = 1; i < number_of_coefficients; i += 2) {

		resultFile << i * frequency << "\t" << reductionAnplitude[i] << "\t";
		resultFile << differencePhase[i] << endl;

	}

	delete[] reductionAnplitude;
	delete[] differencePhase;
}