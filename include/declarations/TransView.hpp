#pragma once

#include "AbsView.hpp"

namespace ejovo {

template <class T>
class Matrix<T>::TransView : public MatView {

    std::function<T(int i)> access;


public:

    // T& operator() (int i) const override;
    // T& operator() (int i) override;

    std::string to_string() const {
        return "TransView";
    }

    using Grid2D<T>::ncol;
    using Grid2D<T>::nrow;





};

















};