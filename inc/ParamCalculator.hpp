/** \file ParamCalculator.hpp
 *  \brief A class to calculate the parameterized alpha,n, and sigma for CBs
 *  \author S. V. Paulauskas
 *  \date 12 November 2013
 */
#ifndef __PARAMCALCULATOR_HPP_
#define __PARAMCALCULATOR_HPP_

#include <Variable.hpp>

///A class to calculate the parameterized alpha, n, and sigma for CBs
class ParamCalculator {
public:
    /*! Default constructor */
    ParamCalculator();
    /*! Default destructor */
    ~ParamCalculator(){};

    /*! \return the value for a_ (sigma)*/
    Variable GetA(void) const {return(a_);};
    /*! \return the value for b_ (sigma)*/
    Variable GetB(void) const {return(b_);};
    /*! \return the value for c_ (sigma)*/
    Variable GetC(void) const {return(c_);};
    /*! \return the value for d_ (sigma)*/
    Variable GetD(void) const {return(d_);};
    /*! \return the value for e_ (sigma)*/
    Variable GetE(void) const {return(e_);};
    /*! \return the value for f_ (alpha)*/
    Variable GetF(void) const {return(f_);};
    /*! \return the value for g_ (alpha)*/
    Variable GetG(void) const {return(g_);};
    /*! \return the value for h_ (alpha)*/
    Variable GetH(void) const {return(h_);};
    /*! \return the value for i_ (alpha)*/
    Variable GetI(void) const {return(i_);};
    /*! \return the value for j_ (n)*/
    Variable GetJ(void) const {return(j_);};
    /*! \return the value for k_ (n)*/
    Variable GetK(void) const {return(k_);};
    /*! \return the value for l_ (n)*/
    Variable GetL(void) const {return(l_);};

    /*! Sets the value for sigma parameter a
     * \param [in] a : the value to set */
    void SetA(const Variable &a) {a_ = a;};
    /*! Sets the value for sigma parameter b
     * \param [in] a : the value to set */
    void SetB(const Variable &a) {b_ = a;};
    /*! Sets the value for sigma parameter c
     * \param [in] a : the value to set */
    void SetC(const Variable &a) {c_ = a;};
    /*! Sets the value for sigma parameter d
     * \param [in] a : the value to set */
    void SetD(const Variable &a) {d_ = a;};
    /*! Sets the value for sigma parameter e
     * \param [in] a : the value to set */
    void SetE(const Variable &a) {e_ = a;};
    /*! Sets the value for alpha parameter f
     * \param [in] a : the value to set */
    void SetF(const Variable &a) {f_ = a;};
    /*! Sets the value for alpha parameter g
     * \param [in] a : the value to set */
    void SetG(const Variable &a) {g_ = a;};
    /*! Sets the value for alpha parameter h
     * \param [in] a : the value to set */
    void SetH(const Variable &a) {h_ = a;};
    /*! Sets the value for alpha parameter i
     * \param [in] a : the value to set */
    void SetI(const Variable &a) {i_ = a;};
    /*! Sets the value for n parameter j
     * \param [in] a : the value to set */
    void SetJ(const Variable &a) {j_ = a;};
    /*! Sets the value for n parameter k
     * \param [in] a : the value to set */
    void SetK(const Variable &a) {k_ = a;};
    /*! Sets the value for n parameter l
     * \param [in] a : the value to set */
    void SetL(const Variable &a) {l_ = a;};

    /*! Calculate the alpha parameter from the CB
    *   \param[in] tof the time of flight
    *   \return The break point for the Gaussian and Power parts of the CB */
    double CalcAlpha(const double &tof);
    /*! Calculate the n parameter for the CB
    *   \param[in] tof the time of flight
    *   \return The power parameter of the CB */
    double CalcN(const double &tof);
    /*! Calculate the sigma parameter for the CB
    *   \param[in] tof the time of flight
    *   \return The width of the Gaussian part of the CB */
    double CalcSigma(const double &tof);
private:
    Variable a_;//!< Coefficient for sigma parameter
    Variable b_;//!< Coefficient for sigma parameter
    Variable c_;//!< Coefficient for sigma parameter
    Variable d_;//!< Coefficient for sigma parameter
    Variable e_;//!< Coefficient for sigma parameter
    Variable f_;//!< Coefficient for alpha parameter
    Variable g_;//!< Coefficient for alpha parameter
    Variable h_;//!< Coefficient for alpha parameter
    Variable i_;//!< Coefficient for alpha parameter
    Variable j_;//!< Coefficient for n parameter
    Variable k_;//!< Coefficient for n parameter
    Variable l_;//!< Coefficient for n parameter
};

#endif //__PARAMCALCULATOR_HPP_
