#ifdef SIM_STATIC_LIBRARY
# include<../include/linear_tetmesh_neohookean_dq.h>
#endif

template<typename DerivedRet, typename DerivedV, typename DerivedQ, typename DefoType, typename DerivedVol, typename DerivedParam>
void sim::linear_tetmesh_neohookean_dq(Eigen::VectorXx<DerivedRet> &g, const Eigen::DenseBase<DerivedV> &V,  Eigen::Ref<const Eigen::MatrixXi> E,
                                        const Eigen::MatrixBase<DerivedQ> &q, 
                                        const Eigen::MatrixBase<DefoType> &dXinv, const Eigen::MatrixBase<DerivedVol>  &volume, 
                                        const Eigen::MatrixBase<DerivedParam> &params) {

    auto assemble_func = [&q](auto &g,  const auto &e, 
                            const auto &dXinv,
                            const auto &volume,
                            const auto &params) 
                           { 
                             linear_tet_neohookean_dq(g, q, e, sim::unflatten<4,3>(dXinv), params, volume(0));
                           };
    

    Eigen::Vector12x<DerivedRet> g_tmp;
    sim::assemble(g, 3*V.rows(), E, E, assemble_func, g_tmp, dXinv, volume, params);
}

#include <iostream>

