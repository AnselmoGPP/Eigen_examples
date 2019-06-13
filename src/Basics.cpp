/*
	Eigen defines the following Matrix typedefs:
	- MatrixNt		== Matrix<type, N, N>		Example: MatrixXi == Matrix<int, Dynamic, Dynamic>
	- VectorNt		== Matrix<type, N, 1>		Example: Vector2f == Matrix<float, 2, 1>
	- RowVectorNt	== Matrix<type, 1, N>		Example: RowVector3d == Matrix<double, 1, 3>

	where:	N == 2, 3, 4, Dynamic
			t == i (int), f (float), d (double), cf (complex<float>), cd (complex<double>)
*/

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

// ----------------------------------------

void simple_matrix() {

	MatrixXd matr(2, 2);		// MatrixXd has doubles. MatrixXi has integers.
	matr(0, 0) = 1;
	matr(0, 1) = 2;
	matr(1, 0) = 3;
	matr(1, 1) = matr(1, 0) + matr(0, 0);

	std::cout << matr << std::endl << std::endl;

	MatrixXd matr2(2, 2);
	matr << 1, 2, 3, 4;
	std::cout << matr << std::endl;
}

void random_and_constant() {

	MatrixXd ran = MatrixXd::Random(3, 3);				// Random between -1 and 1
	std::cout << ran << std::endl;

	MatrixXd con = MatrixXd::Constant(3, 3, 5.2);
	std::cout << con << std::endl;
}

void vector() {

	VectorXd vec(3);			// VectorXd has doubles. VectorXi has integers.
	vec << 1, 2, 3.5;
	std::cout << vec << std::endl;
}

void random_between_4_and_10() {

	MatrixXd matr = MatrixXd::Random(3, 3);
	matr = (matr * (6/2)) + MatrixXd::Constant(3,3,5);
	std::cout << matr << std::endl;

}

void fixed_size() {

	Matrix4d m4 = Matrix4d::Random();
	std::cout << m4 << std::endl;

	Vector4d v4 = Vector4d::Random();
	std::cout << v4 << std::endl;
}

void matrix_template_class() {
	//In Eigen, all matrices and vectors are objects of the Matrix template class.
	//Vectors are just a special case of matrices, with either 1 row or 1 column.

	// Matrix<typename, RowsAtCompileTime, ColsAtCompileTime, StorageOrder, MaxRowsAtCompileTime, MaxColsAtCompileTime>
	Matrix<double, 3, 2> matr1;
	Matrix<double, 3, 5, 0> matr6;								// 0=ColMajor, 1=RowMajor (default)
	Matrix<double, Dynamic, Dynamic, RowMajor, 10, 10> matr5;

	Matrix<double, Dynamic, Dynamic> matr2;
	Matrix<double, 3, Dynamic> matr3(1, 5);		// ¿?
	Matrix<double, Dynamic, 5> matr4;
}
	
void resizing_and_assigning() {

	MatrixXd matr(2, 3);
	matr.resize(3, 5);				// If the size changes with resize(), the values of the coefficients may change
	matr.conservativeResize(5, 4);	// The values of the coefficients doesn't change

	std::cout << matr.rows() << ' ' << matr.cols() << ' ' << matr.size() << std::endl;

	MatrixXd matr2(10, 15);
	matr = matr2;					// matr is resized
}

void addition_subtraction() {
	
	MatrixXd m1(2, 2);
	m1 << 1, 2, 3, 4;
	Matrix2d m2;
	m2 << 4, 3, 2, 1;

	std::cout << m1 + m2 << std::endl << std::endl;
	std::cout << m1 - m2 << std::endl << std::endl;
	std::cout << - m1 << std::endl << std::endl;
	m1 += m2;
	std::cout << m1 << std::endl << std::endl;
	m1 -= m2;
	std::cout << m1 << std::endl << std::endl;
}

void multiplication_division() {

}



// ----------------------------------------


int main() {
    
	//simple_matrix();
	//random_and_constant();
	//vector();
	//random_between_4_and_10();
	//fixed_size();
	//matrix_template_class()
	//resizing_and_assigning();
	addition_subtraction();
	multiplication_division();
}














// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
