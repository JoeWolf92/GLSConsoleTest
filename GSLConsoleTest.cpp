// GSLConsoleTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <gsl/gsl_linalg.h>

int main()
{
	double A_data[] = {
       0.57092943, 0.00313503, 0.88069151, 0.39626474,
       0.33336008, 0.01876333, 0.12228647, 0.40085702,
       0.55534451, 0.54090141, 0.85848041, 0.62154911,
       0.64111484, 0.8892682 , 0.58922332, 0.32858322
	};
	
	double b_data[] = {
		1.5426693 , 0.74961678, 2.21431998, 2.14989419
	};

	// Access the above C arrays through GSL views
	gsl_matrix_view A = gsl_matrix_view_array(A_data, 4, 4);
	gsl_vector_view b = gsl_vector_view_array(b_data, 4);

	// Print the values of A and b using GSL print functions
	std::cout << "A = \n";
	gsl_matrix_fprintf(stdout, &A.matrix, "%lf");
	
	std::cout << "\nb = \n";
	gsl_vector_fprintf(stdout, &b.vector, "%lf");

	// Allocate memory for the solution vector x and the permutation perm:
	gsl_vector * x = gsl_vector_alloc(4);
	gsl_permutation * perm = gsl_permutation_alloc(4);

	// Decompose A into the LU form:
	int signum;
	gsl_linalg_LU_decomp(&A.matrix, perm, &signum);

	// Solve the linear system
	gsl_linalg_LU_solve(&A.matrix, perm, &b.vector, x);

	// Print the solution
	std::cout << "\nx = \n";
	gsl_vector_fprintf(stdout, x, "%lf");

	// Release the memory previously allocated for x and perm
	gsl_vector_free(x);
	gsl_permutation_free(perm);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
