// ======================================================================
// \title  RFM23.hpp
// \author mstarch
// \brief  hpp file for RFM23 component implementation class
// ======================================================================

#ifndef Telecom_RFM23_HPP
#define Telecom_RFM23_HPP

#include "Telecom/RFM23/RFM23ComponentAc.hpp"

namespace Telecom {

class RFM23 : public RFM23ComponentBase {
  public:
    const NATIVE_UINT_TYPE RETRY_LIMIT = 10;
    // ----------------------------------------------------------------------
    // Construction, initialization, and destruction
    // ----------------------------------------------------------------------

    //! Construct object RFM23
    //!
    RFM23(const char* const compName /*!< The component name*/
    );

    //! Initialize object RFM23
    //!
    void init(const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
    );

    //! Destroy object RFM23
    //!
    ~RFM23() override;

    //my code 
    void radioInit(); 

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for comDataIn
    //!
    Drv::SendStatus comDataIn_handler(const NATIVE_INT_TYPE portNum, /*!< The port number*/
                                      Fw::Buffer& sendBuffer) override;

     //! Handler implementation for schedIn
      //!
      void schedIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< 
      The call order
      */
      );
    

    RH_RF22 rf23 ;   //private instance of radio object 

};

}  // end namespace Svc

#endif
