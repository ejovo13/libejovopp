#include "libejovo.hpp"
#include "ejovotest.hpp"

#include <cassert>

void t_RowView();
void t_ColView();
void t_MatView();
void t_VecView();

void t_get_row_view();
void t_RowView_constructors();
void t_RowVieww();

using namespace ejovo;


int main() {

    std::cout << "Hello lib\n";

    t_RowVieww();

    // t_RowView();
    // t_ColView();
    // t_VecView();
    // t_MatView();

    // Matrix<double>::RowView(m, 1);
    // Matrix<double>::RowView rv = Matrix<double>::RowView(m, 1);
    // Matrix<double>::RowView rv = m.get_row_view(1);
    // auto cv = m.get_col_view(1);

    // rv.print();
    // cv.print();



}

/**========================================================================
 *!                           Concrete Implementations of AbsView
 *========================================================================**/


/**============================================
 *!               RowView functions
 *=============================================**/
void t_RowView_constructors() {

    auto m = tmat();

    Matrix<double>::RowView rv1 {m, 1};
    Matrix<double>::RowView rv2 {m, 2, 3};
    Matrix<double>::RowView rv3 {m, 3, 2, 3};
    Matrix<double>::RowView rv4 {std::move(rv1) };

    assert(rv1.eq(new double[4] {4, 5, 2, 4}));
    assert(rv2.eq(new double[2] {3, 5}));
    assert(rv3.eq(new double[2] {4, 3}));
    assert(rv4.eq(new double[4] {4, 5, 2, 4}));

    assert(rv4.i == rv1.i);
    assert(rv4.jb == rv1.jb);
    assert(rv4.je == rv1.je);
    assert(rv4.mat.data == rv1.mat.data);

    assert(rv1.size() == 4);
    assert(rv2.size() == 2);
    assert(rv3.size() == 2);
    assert(rv4.size() == 4);

    std::cout << "RowView ||| constructors passed\n";

}

void t_get_row_view() {

    Matrix<double> m = tmat();

    Matrix<double>::RowView rv1 = m.get_row_view(1); // first row
    Matrix<double>::RowView rv2 = m.get_row_view(2, 3); // first row
    Matrix<double>::RowView rv3 = m.get_row_view(3, 2, 3); // first row

    assert(rv1.eq(new double[4] {4, 5, 2, 4}));
    assert(rv2.eq(new double[2] {3, 5}));
    assert(rv3.eq(new double[2] {4, 3}));

    std::cout << "RowView ||| get_row_view passed\n";

}

void t_RowView_matrix() {

    auto m = tmat();

    auto rv = m.get_row_view(1);
    auto mr1 = Matrix<double>::from({4, 5, 2, 4}, 1, 4);

    assert(rv == mr1); // comparing a row view with a normal Matrix
    assert(rv.to_matrix() == mr1); // comparing a row view to matrix with a normal Matrix
    assert(rv.mat == m);
    assert(rv.mat.data == m.data);

    std::cout << "RowView ||| to_matrix and equality passed\n";

}

void t_RowView_assignment() {

    auto m = tmat();

    auto r1 = m.get_row_view(1);

    /**============================================
     *!               RowView = T
     *=============================================**/
    r1 = 5;

    assert(r1.eq({5, 5, 5, 5}));
    assert(m(1, 1) == 5);
    assert(m(1, 2) == 5);
    assert(m(1, 3) == 5);
    assert(m(1, 4) == 5);

    /**============================================
     *!     RowView = std::initializer_list<T>
     *=============================================**/
    r1 = {1, 2, 3, 4};

    assert(r1.eq({1, 2, 3, 4}));
    assert(m(1, 1) == 1);
    assert(m(1, 2) == 2);
    assert(m(1, 3) == 3);
    assert(m(1, 4) == 4);

    /**============================================
     *!               RowView = Row Matrix<T>
     *=============================================**/
    auto m_new = Matrix<double>::from({18, 3, 4, 70}, 1, 4);
    r1 = m_new;

    assert(r1.eq({18, 3, 4, 70}));
    assert(m(1, 1) == 18);
    assert(m(1, 2) == 3);
    assert(m(1, 3) == 4);
    assert(m(1, 4) == 70);

    /**============================================
     *!            RowView = 2 x 2 Matrix<T>
     *=============================================**/
    auto m_new2 = Matrix<double>::from({2, 1, 5, 9}, 2, 2);
    r1 = m_new2.resize(r1.shape()); // MUST BE RESHAPED
    // TODO Make this reshape happen behind the scenes of m_new2?

    assert(r1.eq({2, 1, 5, 9}));
    assert(m(1, 1) == 2);
    assert(m(1, 2) == 1);
    assert(m(1, 3) == 5);
    assert(m(1, 4) == 9);

    std::cout << "RowView ||| assignment passed\n";


}

void t_RowVieww() {

    t_RowView_constructors();
    t_get_row_view();
    t_RowView_matrix();
    t_RowView_assignment();

}


// void t_

void t_RowView() {

    Matrix<double> m = Matrix<double>::i(5);

    m.print();

    Matrix<double>::RowView rv(m, 1);

    rv.mat.print();
    std::cout << "rv.i = " << rv.i << ", rv.jb = " << rv.jb << ", rv.je: " << rv.je << "\n";

    std::cout << "mat(i, jb + 0): " << rv.mat(rv.i, rv.jb) << ", rv.size(): " << rv.size() << "\n";
    std::cout << "rv[0]: " << rv[0] << std::endl;
    std::cout << "rv[1]: " << rv[1] << std::endl;
    std::cout << "rv[2]: " << rv[2] << std::endl;
    std::cout << "rv[3]: " << rv[3] << std::endl;
    std::cout << "rv[4]: " << rv[4] << std::endl;

    std::cout << "rv.at[1]: " << rv.at(1) << std::endl;
    std::cout << "rv.at[2]: " << rv.at(2) << std::endl;
    std::cout << "rv.at[3]: " << rv.at(3) << std::endl;
    std::cout << "rv.at[4]: " << rv.at(4) << std::endl;
    std::cout << "rv.at[5]: " << rv.at(5) << std::endl;

    rv.print();

    rv = 10.0; // Unless I overload the operator = and assign for a RowView, this line becomes problematic!!!
    rv = Matrix<double>::zeros(1, 10); // fails
    rv = m.get_row_view(2); // fails

    (rv + 10).print();
    (10 + rv).print();
    (10 * rv).print();

    rv.assign(Matrix<double>::zeros(1, 5), ejovo::id_eq<double, double>);
    rv.assign(1.0, ejovo::id_eq<double, double>);
    rv.assign(m.get_row_view(2), ejovo::id_eq<double, double>);

    rv += 1.0;
    rv += m.get_row_view(3);
    rv += Matrix<double>::val(1, 5, 99);

    rv -= 10.0;
    rv -= m.get_row_view(5);
    rv -= Matrix<double>::ij(1, 5);

    rv *= 10;
    rv /= 5;

    m.print();

    std::cout << "t_RowView passed\n";

}

void t_ColView() {

    Matrix<double> m = Matrix<double>::i(5, 5);

    m.print();

    Matrix<double>::ColView cv(m, 1);

    cv = 10.0; // Unless I overload the operator = and assign for a RowView, this line becomes problematic!!!
    cv = Matrix<double>::zeros(1, 10); // fails
    cv = m.get_col_view(2); // fails

    cv.assign(Matrix<double>::zeros(5, 1), ejovo::id_eq<double, double>);
    cv.assign(1.0, ejovo::id_eq<double, double>);
    cv.assign(m.get_col_view(2), ejovo::id_eq<double, double>);

    cv += 1.0;
    cv += m.get_col_view(3);
    cv += Matrix<double>::val(5, 1, 99);

    cv -= 10.0;
    cv -= m.get_col_view(5);
    cv -= Matrix<double>::ij(5, 1);

    cv *= 10;
    cv /= 5;

    m.print();

    std::cout << "t_ColView passed\n";

}

void t_VecView() {

    auto m = Matrix<double>::i(5, 10);

    auto b = m > 10;
    b.print();

    auto bv = m[b];

    bv.print();

    bv = 10;
    bv = 10.0;

    m.print();

    bv = Matrix<double>::zeros(1, 40);

    m.print();

    bv = Matrix<double>::ones(5, 8);

    m.print();

}

void t_MatView() {

    auto m = Matrix<double>::i(4, 8);

    auto sub = m.submat(1, 2, 3, 4);

    m.print();
    sub.print();

    sub = 10;

    m.print();

}