// License: BSD 3 clause

%{
#include "model_smoothed_hinge.h"
%}


class ModelSmoothedHinge : public virtual ModelGeneralizedLinear,
                    public ModelLipschitz {
 public:

  ModelSmoothedHinge(const SBaseArrayDouble2dPtr features,
              const SArrayDoublePtr labels,
              const bool fit_intercept,
              const int n_threads);
};