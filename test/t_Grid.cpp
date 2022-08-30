#include "ejovotest.hpp"
// #include "operations.hpp"

void t_Matrix();

using namespace ejovo;
int main() {

    auto m = Matrix<double>::ij(10);
    auto m2 = Matrix<double>::zeros(5, 20);
    auto m3 = Matrix<double>::zeros(1, 2);

    assert(m.first() == 1);
    assert(m.last() == 19);
    // m.fill(3);

    // m.print();

    assert(m.size() == m2.size());
    assert(m.is_same_size(m2));
    assert(m.isnt_same_size(m3));
    assert(m.is_valid_bound(4));
    assert(!m.is_valid_bound(1000));

    t_Matrix();

    return 0;
}

void t_Matrix() {

    // boolean tests
    auto t_bool = [] () {

        auto pos = Matrix<double>::from({1, 2, 3, 4, 5});
        auto pos_neg = Matrix<double>::from({1, -3, 3, 5, -3});
        auto neg = Matrix<double>::from({-3, -1, -5, -3, -4});

        assert(pos.all(ejovo::factory::gt<double>(0)));
        assert(pos.none(ejovo::factory::lt<double>(0)));

        assert(pos_neg.any(ejovo::factory::lt<double>(0)));
        assert(pos_neg.any(ejovo::factory::gt<double>(0)));

        assert(neg.all(ejovo::factory::lt<double>(0)));
        assert(neg.none(ejovo::factory::gt<double>(0)));

        assert(pos.count(ejovo::factory::lt<double>(0)) == 0);
        assert(pos.count(ejovo::factory::gt<double>(0)) == 5);

        assert(neg.count(ejovo::factory::lt<double>(0)) == 5);
        assert(neg.count(ejovo::factory::gt<double>(0)) == 0);

        assert(pos_neg.count(ejovo::factory::lt<double>(0)) == 2);
        assert(pos_neg.count(ejovo::factory::gt<double>(0)) == 3);

    };

    // fill and mutate tests
    auto t_fill = [] () {

        auto m = Matrix<double>::from({1, 2, 3, 4, 5});
        auto m2 = Matrix<double>::from({1, 2, 3, 4, 5});
        auto m3 = Matrix<double>::val(1, 5, 3);
        auto m4 = Matrix<double>::from({1, 2, 3, 99, 99});
        auto m5 = Matrix<double>::from({2, 4, 6, 198, 198});
        auto m6 = Matrix<double>::from({1, 2, 3, 198, 198});

        m2.fill(3);
        m.fill_if(99, ejovo::factory::gt<double>(3));

        assert(m3 == m2);
        assert(m == m4);

        m4.mutate([&] (auto x) { return x * 2; });

        assert(m4 == m5);

        m5.mutate_if(ejovo::factory::times(0.5), ejovo::factory::lt(10));

        assert(m5 == m6);

    };

    auto t_stats = [] () {

        auto x = ejovo::seq<double>(5);

        assert(x.sum() == 15);
        assert(x.mean() == 3);

        assert(x.var(false) == 2.5);
        assert(x.sd(false) == sqrt(2.5));
        assert(x.var() == 2);
        assert(x.sd() == sqrt(2));
        assert(x.min() == 1);
        assert(x.max() == 5);
        assert(x.prod() == 120);

        // I lose precision that's carry
        assert(abs(x.norm() - sqrt(1 + 4 + 9 + 16 + 25)) < 0.0000001);

        auto y = Matrix<double>::from({-1, 2, 3, 4, -5});

        assert(y.sum_abs() == 15);
        assert(y.sum() == 3);

        std::cout << "Stats passed\n";

    };

    /**========================================================================
     *!                           Functional like patters
     *========================================================================**/
    auto t_functional = [] () {

        auto m = Matrix<double>::from({1, 3, 5, 4, 2, 6});

        // take
        assert(m.take(3).eq({1, 3, 5}));
        assert(m.take(0).is_null());
        assert(m.take(5).eq({1, 3, 5, 4, 2}));
        assert(m.take(20).eq({1, 3, 5, 4, 2, 6}));

        // tail
        assert(m.tail().eq({3, 5, 4, 2, 6}));

        // head
        assert(m.head().eq({1, 3, 5, 4, 2}));

        // drop@
        assert(m.drop(10).is_null());
        assert(m.drop(2).eq({1, 3, 5, 4}));
        assert(m.drop(5).eq({1}));
        assert(m.drop(6).is_null());

        // pad
        assert(m.pad(3).eq({1, 3, 5}));
        assert(m.pad(8, 2).eq({1, 3, 5, 4, 2, 6, 2, 2}));
        assert(m.pad(10).eq({1, 3, 5, 4, 2, 6, 0, 0, 0, 0}));

        // resize
        m.first() = 3;
        m.last() = 19;

        assert(m(1) == 3);
        assert(m(m.size()) == 19);
        assert(m.same(m));
        assert(m == m.to_matrix());


        std::cout << "Functional passed\n";

    };

    using namespace ejovo::factory;

    auto t_conditionals = [] () {

        auto m = tmat();

        assert(m.cond(eq(0.0)).size() == 1);
        assert(m.eq(4).size() == 3);
        assert(m.lt(5).size() == 9);
        assert(m.gt(100).size() == 0);
        assert(m.lt(-300).size() == 0);
        // assert((!m.lt(-300)).count() == m.size());
        assert(m.leq(5).size() == 11);
        assert(m.geq(8).size() == 1);

        std::cout << "Conditionals passed\n";

    };

    auto t_filter = [] () {

        auto m = tmat();

        auto TRUE = [&] (auto x) {
            return true;
        };

        auto filtered = m.filter(TRUE);

        // auto filtered1 = m.filter(ejovo::factory::even<double>());

        // filtered1.print();

        assert(m == m);
        assert(filtered == m);

        m(m < 5) = 20;

        assert(m.as_bool() == Matrix<bool>::ones(m.nrow(), m.ncol()));
        assert(m.as_bool().NOT() == Matrix<bool>::zeros(m.nrow(), m.ncol()));

        auto m2_explicit = m.map2<double, double>([&] (auto x, auto y) { return x + y; }, Matrix<double>::ones(12));
        auto m2_implicit = m.map2(factory::plus<double>(), Matrix<double>::ones(12));

        assert(m2_explicit == m2_implicit);

        std::cout << "Filter passed \n";

        m.print();

        m.lt(10).print();
        m.geq(20).print();
        m.pos().print();
        m.sqrd().print();

        m.where(factory::lt(10)).print();


    };


    t_bool();
    t_fill();
    t_stats();
    t_functional();
    t_filter();
    t_conditionals();














}