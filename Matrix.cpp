#include<iostream>
#include<Eigen/Dense>
#include<Eigen/Eigenvalues>
#include<complex>
//va
using Eigen::MatrixXf;
using Eigen::VectorXf;
using namespace std;

VectorXf mainMinors(MatrixXf matrix, int n) {
    VectorXf mainMinorsVector(n);
    MatrixXf adjunctMatrix;
    for (int i = 1; i < n + 1; i++) {
        adjunctMatrix = matrix.block(0, 0, i, i);
        cout << "Minor " << i << endl;
        cout << adjunctMatrix << endl;
        mainMinorsVector(i - 1) = adjunctMatrix.determinant();
    }
    return mainMinorsVector;
}
int main() {
    cout << "Assign matrix dimension nxn" << endl;
    int n;
    cin >> n;
    MatrixXf matrix(n, n);
    cout << "Assign matrix:" << endl;
    float element;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> element;
            matrix(i, j) = element;
        }
    }
    cout << "Your matrix is:" << endl;
    cout << matrix << endl;
    MatrixXf adjunctMatrix(n, n);
    adjunctMatrix = matrix.adjoint();
    if (matrix != adjunctMatrix) {
        cout << "Your matrix is not Hermitian" << endl;
    }
    else {
        VectorXf eigenvalueVector(n);
        Eigen::SelfAdjointEigenSolver<MatrixXf> s(matrix);
        for (int i = 0; i < n; i++) {
            eigenvalueVector(i) = s.eigenvalues()[i];
        }
        cout << "Eigenvalues are:" << endl;
        cout << eigenvalueVector << endl;
        int k = 1;
        for (int i = 0; i < n; i++) {
            if (eigenvalueVector(i) < 0)
                k = 0;
        }
        if (k != 0)
            cout << "Your matrix is pozitive semidefinite" << endl;
        else
            cout << "Your matrix is Hermitian but it is NOT pozitive semidefinite" << endl;
    }
    VectorXf minorVector(n);
    minorVector = mainMinors(matrix, n);
    cout << "Vector of minors:" << endl;
    cout << minorVector << endl;
    int b = 1;
    for (int i = 0; i < n; i++) {
        if (minorVector(i) < 0)
            b = 0;
    }
    if (b == 0)
        cout << "Your matrix is NOT positive definite" << endl;
    else
        cout << "Your matrix is positive definite" << endl;
    int k;
    cin >> k;
}