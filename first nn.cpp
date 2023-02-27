// Моя первая нейросеть на C++
// Это однослойная нейросеть, её задача - научиться искать определённую ячейку, в которой лежит куриный обед из PUBG

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void print_vector(vector<float> const& input)
{
	cout << "[";
	for (int i = 0; i < input.size() - 1; i++)
		cout << input[i] << ", ";
	cout << input[input.size() - 1] << "]";
}

class SimpleNeuralNet
{
protected:
	// Используем float, так как переменные этого типа занимают 4 байт
	vector<float> input;
	vector<float> weight;

	void output()
	{
		cout << setprecision(1) << std::fixed;
		cout << "Neural Net output: " << evaluateNeuralNet() << "\tError: " << evaluateNeuralNetError() << "\tWeight Vector : "; print_vector(weight); cout << endl;
	}

	float evaluateNeuralNet()
	{
		// Метод, рассчитывающий значения на выходе
		float result = 0;
		float layerValue;
		for (int i = 0; i < input.size(); i++)
		{
			layerValue = input[i] * weight[i];
			result += layerValue;
		}
		return roundf(result * 100) / 100; ;
	}

	void learning(float learningRate = 0.20)
	{
		// Функция с циклом обучения. Добавляет коэффициент обучения к весу активного нейрона
		for (int i = 0; i < weight.size(); i++)
			if (input[i] > 0)
				weight[i] += learningRate;
	}

public:
	SimpleNeuralNet(vector<float> inputVector, vector<float> weightVector)
	{
		input = inputVector; weight = weightVector;
	}

	float evaluateNeuralNetError(float desired = 1.0) {
		// Функция для оценки работы нейронной сети
		return (desired - evaluateNeuralNet());
	}
	
	float training()
	{
		// Функция обучения
		float result = 0;
		cout << "Neural Network is learning to find Chicken dinner..." << "\n" << endl;
		while (evaluateNeuralNetError() > 0.0)
		{
			result = evaluateNeuralNet();
			output();
			learning();
		}
		output();
		cout << "\nWinner, winner Chicken dinner!" << endl;
		return result;
	}
};

int main()
{
	SimpleNeuralNet first({ 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 });
	first.training();
	return 0;
}