/* neuralnet.c */

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

double sigmoid(double x) {
  return 1 / (1 + exp(-x));
}

double derivative(double x) {
  return x * (1 - x);
}

double output(double in[], double w[], double bw) {
  double res = 0;
  for(size_t i = 0; i < 2; ++i)
    res += in[i] * w[i];
  res += bw;
  return sigmoid(res);
}
int random_range(int min, int max)
{
  int diff = max-min;
  return (int) (((double)(diff+1)/RAND_MAX) * rand() + min);
}

void train() {
  double in[4][2] = {{0,0},{0,1},{1,0},{1,1}};
  double res[4] = {0,1,1,0};

  // hidden neur 1
  double weightN1[2], inputsN1[2], errN1, bwN1;
  weightN1[0] = (double) rand() / (double) RAND_MAX;
  weightN1[1] = (double) rand() / (double) RAND_MAX;
  bwN1 = (double) rand() / (double) RAND_MAX;

  // hidden neur 2
  double weightN2[2], inputsN2[2], errN2, bwN2;
  weightN2[0] = (double) rand() / (double) RAND_MAX;
  weightN2[1] = (double) rand() / (double) RAND_MAX;
  bwN2 = (double) rand() / (double) RAND_MAX;

  // output 3
  double weightN3[2], inputsN3[2], errN3, bwN3;
  weightN3[0] = (double) rand() / (double) RAND_MAX;
  weightN3[1] = (double) rand() / (double) RAND_MAX;
  bwN3 = (double) rand() / (double) RAND_MAX;

  int epoch = 0;
  while(epoch < 8000) {
    ++epoch;
    //for(int i = 0; i < 4; ++i) {
      int i = random_range(1, 4);
      inputsN1[0] = in[i][0];
      inputsN1[1] = in[i][1];
      inputsN2[0] = in[i][0];
      inputsN2[1] = in[i][1];

      inputsN3[0] = output(inputsN1, weightN1, bwN1);
      inputsN3[1] = output(inputsN2, weightN2, bwN2);

      double outputN3 = output(inputsN3, weightN3, bwN3);

      printf("%f XOR %f = ", in[i][0], in[i][1]);
      printf("%f\n", outputN3);

      errN3 = derivative(outputN3) * (res[i] - outputN3);
      weightN3[0] += errN3 * inputsN3[0];
      weightN3[1] += errN3 * inputsN3[1];
      bwN3 += errN3;

      errN1 = derivative(inputsN3[0]) * errN3 * weightN3[0];
      errN2 = derivative(inputsN3[1]) * errN3 * weightN3[1];

      weightN1[0] += errN1 * inputsN1[0];
      weightN1[1] += errN1 * inputsN1[0];
      bwN1 += errN1;

      weightN2[0] += errN2 * inputsN2[0];
      weightN2[1] += errN2 * inputsN2[0];
      bwN2 += errN2;
    //}
  }
}

int main() {
  train();
  return 0;
}
