# C-Perceptron

### Summary

This is the final project of an amazing programming class "Life beyond Python", which covered a wide range of topics including the perceptron machine learning algorithm. This program, which implements the perceptron algorithm in C, can be trained on a 2-d array of linearly separable data (floating point values from 0 - 1), and predicts a one or a negative one based on user input. it will also test itself against a different set of data and provide the percentage of correct predictions.

### Usage 

clone the repo and run the "make" command to run the program. This uses the makefile tool to avoid manually linking the perceptron library.

alternatively, one can run the /driver executable directly, but make sure to add the train.dat and test.dat arguments or it will not run properly.

### files

perceptron.h - perceptron interface
perceptron.c - implementation of the perceptron
driver - the program executable
train.dat - the training data
test.dat - the testing data
makefile - makefile for configuring C compiler without headaches


