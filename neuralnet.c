#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LAYER_SIZE 2

typedef struct s_input_test
{
  double inputs[LAYER_SIZE];
  double result;
} t_input_test;

typedef struct s_layer
{
  double weights[LAYER_SIZE];
  double inputs[LAYER_SIZE];
  double bias;
} t_layer;

// Training set:
t_input_test tests[] = {
  {{0, 0}, 0},
  {{0, 1}, 1},
  {{1, 0}, 1},
  {{1, 1}, 0},
};

double sigmoid(double x)
{
  return 1. / (1. + exp(-x));
}

double sigmoid_derivative(double x)
{
  return x * (1. - x);
}

double forward(double inputs[], double weights[], double bias)
{
  double res = 0;

  for(size_t i = 0; i < LAYER_SIZE; ++i)
    res += inputs[i] * weights[i];
  res += bias;

  return sigmoid(res);
}

int random_range(int min, int max)
{
  int diff = max-min;
  return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}

double random_double(void)
{
  /* Gives a random double ranging from 0 to 1 */

  return (double) rand() / (double) RAND_MAX;
}

void initialize_layer(t_layer *l)
{
  /* Initializes the layer weights and bias with random values */

  for(size_t i = 0; i < LAYER_SIZE; ++i)
    l->weights[i] = random_double();
  l->bias = random_double();
}

void backprop(t_layer *l, double err)
{
  /* Updates the layer weights and bias in function of the given error */

  for(size_t i = 0; i < LAYER_SIZE; ++i)
    l->weights[i] += err * l->inputs[i];
  l->bias += err;
}

int main() {
  // Build layers
  t_layer layers[LAYER_SIZE];
  for (size_t i = 0; i < LAYER_SIZE; i++)
    initialize_layer(&layers[i]);

  // Build output layer
  t_layer output_layer;
  initialize_layer(&output_layer);

  for (size_t epoch = 0; epoch < 2000 * 4; epoch++)
  {
    // We give it a random test
    t_input_test t = tests[random_range(1,4)];
    printf("\n%d XOR %d ", (int)t.inputs[0], (int)t.inputs[1]);

    // Feed the input layers with the inputs
    for (size_t i = 0; i < LAYER_SIZE; i++)
    {
      t_layer l = layers[i];
      for (size_t j = 0; j < LAYER_SIZE; j++)
        l.inputs[j] = t.inputs[j];
      output_layer.inputs[i] = forward(l.inputs, l.weights, l.bias);
    }

    // Determine the output
    double output = forward(output_layer.inputs,
                            output_layer.weights,
                            output_layer.bias);
    // Determine the error between what we found and the expected result
    double output_err = sigmoid_derivative(output) * (t.result - output);

    // Update output layer
    printf("\n%f", output_layer.bias);
    backprop(&output_layer, output_err);
    printf(" %f\n", output_layer.bias);

    // Update the neurons for intermediate layer
    for (size_t i = 0; i < LAYER_SIZE; i++)
    {
      double err = sigmoid_derivative(output_layer.inputs[i])
                 * output_err
                 * output_layer.weights[i];

      backprop(&layers[i], err);
    }

    printf("= %f(%d) (ERR:%f)\n", output, (int)t.result, output_err);
  }

  return 0;
}
