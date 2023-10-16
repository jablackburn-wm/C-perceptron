#include <stdio.h>
#include <stdlib.h>
#include "perceptron.h"

int main(int argc, char *argv[])
{
	// usage: ./a.out train.dat test.dat
    char *train_fname = argv[1];
    char *test_fname = argv[2];
    // int number_of_examples = atoi(argv[2]);

    // Building
	Data data = new_Data(train_fname);

    Model model = new_Model(data);
	// initialize_model(model);

    // Training
    fit_model(model, data);

    // Testing
	Data test_data = new_Data(test_fname);
	evaluate_model(model, test_data);

    // Scoring
    run_scoring_engine(model);

	delete_Data(data);
	delete_Data(test_data);
	delete_Model(model);

    return 0;
}
