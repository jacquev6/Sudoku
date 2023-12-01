// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_TEXT_EXPLAINER_HPP_
#define EXPLANATION_TEXT_EXPLAINER_HPP_

#include <iostream>

#include "explanation.hpp"


template<unsigned size>
void explain_as_text(const Explanation<size>&, std::ostream&);

#endif  // EXPLANATION_TEXT_EXPLAINER_HPP_
