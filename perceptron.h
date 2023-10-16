#ifndef PERCEPTRON_H
#define PERCEPTRON_H
// #define DIMENSIONS 3

typedef struct data *Data;
typedef struct model *Model;

// Building
Data new_Data(const char *fname);
Model new_Model(const Data data);
// void load_data(char *fname, Data xcoords, Data ycoords, Data targets);
// void initialize_model(Model model);

// Training
void fit_model(Model model, Data data);

// Testing
void evaluate_model(Model model, Data data);

// Scoring
void run_scoring_engine(const Model model);


void delete_Data(Data data);
void delete_Model(Model model);

#endif
