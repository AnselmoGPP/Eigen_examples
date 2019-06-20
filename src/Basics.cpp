/*
	Eigen defines the following Matrix typedefs:
	- MatrixNt		== Matrix<type, N, N>		Example: MatrixXi == Matrix<int, Dynamic, Dynamic>
	- VectorNt		== Matrix<type, N, 1>		Example: Vector2f == Matrix<float, 2, 1>
	- RowVectorNt	== Matrix<type, 1, N>		Example: RowVector3d == Matrix<double, 1, 3>

	where:	N == 2, 3, 4, X, Dynamic (not known at compile-time).
			t == i (int), f (float), d (double), cf (complex<float>), cd (complex<double>)
*/

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

// ----------------------------------------

void simple_matrix() {					// (1)
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

void random_and_constant() {				// (2)
	MatrixXd ran = MatrixXd::Random(3, 3);				// Random between -1 and 1
	std::cout << ran << std::endl;

	MatrixXd con = MatrixXd::Constant(3, 3, 5.2);
	std::cout << con << std::endl;
}

void vector() {						// (3)
	VectorXd vec(3);			// VectorXd has doubles. VectorXi has integers.
	vec << 1, 2, 3.5;
	std::cout << vec << std::endl;
}

void random_between_2_and_8() {				// (4)
	MatrixXd matr = MatrixXd::Random(3, 3);
	matr = (matr * (6/2)) + MatrixXd::Constant(3,3,5);
	std::cout << matr << std::endl;
}

void fixed_size() {					// (5)
	Matrix4d m4 = Matrix4d::Random();
	std::cout << m4 << std::endl;

	Vector4d v4 = Vector4d::Random();
	std::cout << v4 << std::endl;
}

void matrix_template_class() {				// (6)
	//In Eigen, all matrices and vectors are objects of the Matrix template class.
	//Vectors are just a special case of matrices, with either 1 row or 1 column.

	// Matrix<typename, RowsAtCompileTime, ColsAtCompileTime, StorageOrder, MaxRowsAtCompileTime, MaxColsAtCompileTime>
	Matrix<double, 3, 2> matr1;
	Matrix<double, 3, 5, 0> matr6;								// 0=ColMajor(default), 1=RowMajor 
	Matrix<double, Dynamic, Dynamic, RowMajor, 10, 10> matr5;

	Matrix<double, Dynamic, Dynamic> matr2;
	Matrix<double, 3, Dynamic> matr3(1, 5);		// ¿?
	Matrix<double, Dynamic, 5> matr4;
}
	
void resizing_and_assigning() {				// (7)
	MatrixXd matr(2, 3);
	matr.resize(3, 5);				// If the size changes with resize(), the values of the coefficients may change
	matr.conservativeResize(5, 4);	// The values of the coefficients doesn't change

	std::cout << matr.rows() << ' ' << matr.cols() << ' ' << matr.size() << std::endl;

	MatrixXd matr2(10, 15);
	matr = matr2;					// matr is resized
}

void addition_subtraction() {				// (8)
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

void scalar_multiplication_division() {			// (9)
// Escalar multiplication/division
	Matrix2d a;
	a << 1, 2, 3, 4;
	Vector3d v(1,2,3);
	
	std::cout << a * 2.5 << std::endl;
	std::cout << 0.1 * v << std::endl;
	v *= 2;
	std::cout << v << std::endl;
	v /= 2;
	std::cout << v << std::endl;

// Matrix/vector multiplication/division
	Matrix2d mat;
	mat << 1, 2, 3, 4;
	Vector2d u(-1,1), v(2,0);
	std::cout << mat*mat << std::endl;
	std::cout << mat*u << std::endl;
	std::cout << u.transpose()*mat << std::endl;
	std::cout << u.transpose()*v << std::endl;
	std::cout << u*v.transpose() << std::endl;
	mat = mat*mat;
}

void transposition_conjugation(){			// (10)
	MatrixXcf a = MatrixXcf::Random(2,2);
	MatrixXcf b = MatrixXcf::Random(2,2);
	MatrixXcf c = MatrixXcf::Random(2,2);
	
	std::cout << a << endl;
	std::cout << a.transpose() << std::endl;
	std::cout << a.conjugate() << std::endl;
	std::cout << a.adjoint() << std::endl;
	
	//a = a.transpose(); 			// Wrong (the aliasing issue: no temporary is created)
	//a = a.adjoint();			// Wrong (the aliasing issue: no temporary is created)
	a.transposeInPlace();
	a.adjointInPlace();
	c.noalias() += a * b;			// If your matrix product can be safely evaluated into the destination matrix without aliasing issue, then you can use noalias() to avoid the temporary
}

void dot_and_cross_product(){				// (11)
	Vector3d v(1,2,3);
	Vector3d w(0,1,2);

	std::cout << v.dot(w) << endl;		// Cross product is only for vectors of size 3
	double dp = v.adjoint()*w; 		// Automatic conversion of the inner product to a scalar
	std::cout << dp << endl;
	std::cout << v.cross(w) << endl;	// Dot product is for vectors of any sizes
}

void reduction_ops(){
	Matrix2d mat;
	mat << 1, 2, 3, 4;
	
	std::cout << mat.sum() << endl;
	std::cout << mat.prod() << endl;
	std::cout << mat.mean() << endl;
	std::cout << mat.minCoeff() << endl;
	std::cout << mat.maxCoeff() << endl;
	std::cout << mat.trace() << endl;	// Sum of the diagonal coefficients. Also computed as efficiently using a.diagonal().sum()

	Matrix3f m = Matrix3f::Random();
	std::ptrdiff_t i, j;	
	float minOfM = m.minCoeff(&i,&j);
	std::cout << m << endl;
	std::cout << "The minimum coefficient (" << minOfM << ") is at position (" << i << "," << j << ")\n\n";
	
	RowVector4i v = RowVector4i::Random();
	int maxOfV = v.maxCoeff(&i);
	std::cout << v << std::endl;
	std::cout << "The maximum coefficient (" << maxOfV << ") is at position " << i << endl;
}



// ----------------------------------------


int main() {
	unsigned int val = 0;
	
	for(;;){
		std::cout << "\nEnter function number: ";
		std::cin >> val;
		std::cout << "-----------------------" << std::endl;
		
		switch(val) {
			case 1:
				simple_matrix();
				break;
			case 2:
				random_and_constant();
				break;
			case 3:
				vector();
				break;
			case 4:
				random_between_4_and_10();
				break;
			case 5:
				fixed_size();
				break;
			case 6:
				matrix_template_class()
				break;
			case 7:
				resizing_and_assigning();
				break;
			case 8:
				addition_subtraction();
				break;
			case 9:
				scalar_multiplication_division();
				break;
			case 10:
				transposition_conjugation();
				break;
			case 11:
				dot_and_cross_product()
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			case 16:
				break;
			case 17:
				break;
			case 18:
				break;
			case 19:
				break;
			case 20:
				break;				
			default:
				return 0;		
		}
	}
}
