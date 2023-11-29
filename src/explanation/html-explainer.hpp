// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_HTML_EXPLAINER_HPP_
#define EXPLANATION_HTML_EXPLAINER_HPP_

#include <filesystem>

#include "explanation.hpp"


template<unsigned size>
void explain_as_html(const Explanation<size>&, const std::filesystem::path&, unsigned width, unsigned height);

#endif  // EXPLANATION_HTML_EXPLAINER_HPP_
