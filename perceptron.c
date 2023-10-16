#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"



struct Shape {
	int examples;
	int dimensions;
};

struct data {
    double **elements;
	int *targets;
	struct Shape shape;
};

struct model {
    double *weights;
	struct Shape shape;
};



static struct Shape get_shape(const char *fname)
{

	FILE *fp;

    if ((fp = fopen(fname, "r")) == NULL)  {
        fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }

	int examples = 0; // examples is num of rows
	int dimensions = 0; // dimensions is num of columns - 1 (num of spaces in a row)
	char c = getc(fp);
	// get dimensions from first line
	while(c != '\n')
	{
		if (c == ' ') dimensions++;
		c = getc(fp);
	};
	// get examples 
	while(c != EOF)
	{
		if (c == '\n') examples++;
		c = getc(fp);
	};

	struct Shape shape = { examples, dimensions };

	fclose(fp);
	return shape;
};



Data new_Data(const char *fname)
{
	/* allocate memory */
    Data data = (Data) malloc(sizeof(struct data));
	struct Shape shape = get_shape(fname);
	data->shape = shape;
	int examples = shape.examples;
	int dimensions = shape.dimensions;
	data->targets = (int*) malloc(examples * sizeof(int));
    data->elements = (double**) malloc(examples * sizeof(double*));
	for (int i=0; i < examples; i++) {
		data->elements[i] = (double*) malloc(dimensions * sizeof(double));
	}

	/* load data */
    FILE *fp;
    if ((fp = fopen(fname, "r")) == NULL)  {
        fprintf(stderr, "load_data: can't open %s\n", fname);
        exit(1);
    }
    int row = 0;
    int col = 0;
    double *target_as_double = (double*) malloc(sizeof(double));
    while (row != examples)
    {
        while (col != dimensions) 
        {
            fscanf(fp, "%lf", &(data->elements[row][col]));
            col++;
        };
        fscanf(fp, "%lf", target_as_double);
        data->targets[row] = (int) *target_as_double;
        col = 0;
        row++;
    };
	free(target_as_double);
    fclose(fp);
    fprintf(stdout, "load_data: loaded %d examples from %s\n", row, fname);
    return data;
}




Model new_Model(const Data data)
{
    Model model = (Model) malloc(sizeof(struct model));
	struct Shape shape = data->shape;
	model->shape = shape;
	int dimensions = model->shape.dimensions;
    model->weights = (double*) malloc((dimensions + 1) * sizeof(double)); 
    for (int i = 0; i <= dimensions; i++)
        model->weights[i] = (double) rand() / RAND_MAX;
    return model;
}



static void sgd(Model model, Data data, int cur_example)
{
	int dimensions = data->shape.dimensions;
	int target = data->targets[cur_example];
	int i = 1;
    //weights[0] = weights[0];
    model->weights[0] += target * 1;
	while (i <= dimensions) 
	{
		model->weights[i] += target * data->elements[cur_example][dimensions - i]; 
		i++;
	};
}

static int predict(Model model, Data data, int cur_example)
{
	double hypothesis = 0;
	int dimensions = data->shape.dimensions;
	int i = 0;
	while (i < dimensions)
	{
		hypothesis += model->weights[dimensions - i] * data->elements[cur_example][i];
		i++;
	};
    return (hypothesis < 0) ? -1 : 1;
}

void fit_model(Model model, Data data)
{
    double hypothesis, target;
    bool misclassified = true;
    while (misclassified) {
        misclassified = false;
        for (int i = 0; i < data->shape.examples; i++) {
            hypothesis = predict(model, data, i);
            target = data->targets[i];
            if ((hypothesis >= 0 && target > 0) || (hypothesis < 0 && target < 0))
                continue;
            sgd(model, data, i);  // Update weights using misclassified point
            misclassified = true;
        }
    }
}



void evaluate_model(Model model, Data data)
{
	int examples = data->shape.examples;
	int num_correct = 0;
	for (int i = 0; i < examples; i++)
	{
		if (predict(model, data, i) == data->targets[i]) num_correct++;
	};
	double fraction_correct = (double)num_correct / (double)examples;
	printf("\nevaluate model: %%%lf accurate\n\n", fraction_correct * 100);
}


void run_scoring_engine(Model model)
{
    double x, y;
    printf("Enter x: \n");
    scanf("%lf", &x);
    printf("Enter y: \n");
    scanf("%lf", &y);

    Data data = (Data) malloc(sizeof(struct data));
	struct Shape shape = {1,2};
	data->shape = shape;
    data->elements = (double**) malloc(sizeof(double*));
	data->elements[0] = (double*) malloc(2 * sizeof(double));
	data->elements[0][0] = x;
	data->elements[0][1] = y;

    printf("Prediction = %d\n", predict(model, data, 0));
	free(data->elements[0]);
	free(data->elements);
	free(data);
}


void delete_Data(Data data) 
{
	int examples = data->shape.examples;
	for (int i=0; i < examples; i++) {
		free(data->elements[i]);
	}
	free(data->elements);
	free(data->targets);
	free(data);
}

void delete_Model(Model model) 
{
	free(model->weights);
	free(model);
}
