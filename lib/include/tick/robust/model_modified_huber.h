#ifndef LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_
#define LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_

// License: BSD 3 clause

#include "tick/base_model/model_generalized_linear.h"
#include "tick/base_model/model_lipschitz.h"

template <class T>
class DLL_PUBLIC TModelModifiedHuber
    : public virtual TModelGeneralizedLinear<T>,
      public TModelLipschitz<T> {
 protected:
  using TModelGeneralizedLinear<T>::features_norm_sq;
  using TModelGeneralizedLinear<T>::compute_features_norm_sq;
  using TModelGeneralizedLinear<T>::n_samples;
  using TModelGeneralizedLinear<T>::n_features;
  using TModelGeneralizedLinear<T>::fit_intercept;
  using TModelGeneralizedLinear<T>::compute_grad_i;
  using TModelGeneralizedLinear<T>::n_threads;
  using TModelGeneralizedLinear<T>::get_inner_prod;
  using TModelLipschitz<T>::ready_lip_consts;
  using TModelLipschitz<T>::lip_consts;

 public:
  using TModelGeneralizedLinear<T>::get_label;
  using TModelGeneralizedLinear<T>::grad_i;
  using TModelGeneralizedLinear<T>::get_features;
  using TModelGeneralizedLinear<T>::grad_i_factor;
  using TModelGeneralizedLinear<T>::get_class_name;

 public:
  // This exists soley for cereal/swig
  TModelModifiedHuber() : TModelModifiedHuber(nullptr, nullptr, false) {}

  TModelModifiedHuber(const std::shared_ptr<BaseArray2d<T>> features,
                      const std::shared_ptr<SArray<T>> labels,
                      const bool fit_intercept, const int n_threads = 1)
      : TModelLabelsFeatures<T>(features, labels),
        TModelGeneralizedLinear<T>(features, labels, fit_intercept, n_threads) {
  }

  T loss_i(const ulong i, const Array<T> &coeffs) override;

  T grad_i_factor(const ulong i, const Array<T> &coeffs) override;

  void compute_lip_consts() override;

  template <class Archive>
  void serialize(Archive &ar) {
    ar(cereal::make_nvp("ModelGeneralizedLinear",
                        cereal::base_class<TModelGeneralizedLinear<T>>(this)));
    ar(cereal::make_nvp("ModelLipschitz",
                        cereal::base_class<TModelLipschitz<T>>(this)));
  }

  BoolStrReport compare(const TModelModifiedHuber<T> &that,
                        std::stringstream &ss) {
    ss << get_class_name() << std::endl;
    bool are_equal = TModelGeneralizedLinear<T>::compare(that, ss) &&
                     TModelLipschitz<T>::compare(that, ss);
    return BoolStrReport(are_equal, ss.str());
  }
  BoolStrReport compare(const TModelModifiedHuber<T> &that) {
    std::stringstream ss;
    return compare(that, ss);
  }
  BoolStrReport operator==(const TModelModifiedHuber<T> &that) {
    return TModelModifiedHuber<T>::compare(that);
  }
};

using ModelModifiedHuber = TModelModifiedHuber<double>;
using ModelModifiedHuberDouble = TModelModifiedHuber<double>;
using ModelModifiedHuberFloat = TModelModifiedHuber<float>;

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ModelModifiedHuberDouble,
                                   cereal::specialization::member_serialize)
CEREAL_REGISTER_TYPE(ModelModifiedHuberDouble)

CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(ModelModifiedHuberFloat,
                                   cereal::specialization::member_serialize)
CEREAL_REGISTER_TYPE(ModelModifiedHuberFloat)

#endif  // LIB_INCLUDE_TICK_ROBUST_MODEL_MODIFIED_HUBER_H_
