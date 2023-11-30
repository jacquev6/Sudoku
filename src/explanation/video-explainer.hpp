// Copyright 2023 Vincent Jacques

#ifndef EXPLANATION_VIDEO_EXPLAINER_HPP_
#define EXPLANATION_VIDEO_EXPLAINER_HPP_

#include "explanation.hpp"
#include "video/serializer.hpp"


template<unsigned size>
void explain_as_video(const Explanation<size>&, video::Serializer*, unsigned width, unsigned height);

#endif  // EXPLANATION_VIDEO_EXPLAINER_HPP_
