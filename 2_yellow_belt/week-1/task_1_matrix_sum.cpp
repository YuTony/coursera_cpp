#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
   public:
    Matrix() {
        N = 0;
        M = 0;
    }
    Matrix(int n, int m) {
        Reset(n, m);
    }
    void Reset(int n, int m) {
        if (n < 0) {
            throw out_of_range("num_rows must be >= 0");
        }
        if (m < 0) {
            throw out_of_range("num_columns must be >= 0");
        }
        if (n == 0 || m == 0) {
            n = m = 0;
        }
        N = n;
        M = m;
        matrix.assign(n, vector<int>(m));
    }
    int At(int i, int j) const {
        return matrix.at(i).at(j);
    }

    int& At(int i, int j) {
        return matrix.at(i).at(j);
    }

    int GetNumRows() const {
        return N;
    }

    int GetNumColumns() const {
        return M;
    }

   private:
    vector<vector<int>> matrix;
    int N, M;
};

istream& operator>>(istream& in, Matrix& matrix) {
    int n, m;
    in >> n >> m;
    matrix.Reset(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> matrix.At(i, j);
        }
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
    out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
    for (int i = 0; i < matrix.GetNumRows(); i++) {
        for (int j = 0; j < matrix.GetNumColumns(); j++) {
            if (j > 0) {
                out << " ";
            }
            out << matrix.At(i, j);
        }
        out << endl;
    }
    return out;
    int32_t x = 1u;
}

Matrix operator+(const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() != m2.GetNumRows()) {
        throw invalid_argument("Mismatched number of rows");
    }
    if (m1.GetNumColumns() != m2.GetNumColumns()) {
        throw invalid_argument("Mismatched number of columns");
    }
    Matrix res(m1.GetNumRows(), m1.GetNumColumns());
    for (int i = 0; i < res.GetNumRows(); ++i) {
        for (int j = 0; j < res.GetNumColumns(); ++j) {
            res.At(i, j) = m1.At(i, j) + m2.At(i, j);
        }
    }
    return res;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.GetNumRows() != m2.GetNumRows()) {
        return false;
    }
    if (m1.GetNumColumns() != m2.GetNumColumns()) {
        return false;
    }
    for (int row = 0; row < m1.GetNumRows(); ++row) {
        for (int column = 0; column < m1.GetNumColumns(); ++column) {
            if (m1.At(row, column) != m2.At(row, column)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    Matrix one;
    Matrix two;

    cin >> one >> two;
    cout << one + two << endl;
    return 0;
}
