// ======================================================================
// \title  RFM23.cpp
// \author mstarch
// \brief  cpp file for RFM23 component implementation class
// ======================================================================

#include <Telecom/RFM23/RFM23.hpp>
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/BasicTypes.hpp"
#include "RH_RF22.h"
#include "RHHardwareSPI1.h" 

namespace Telecom {

const int CS_PIN     = 38;    //38
const int INT_PIN    = 8;     //8    

const int SPI_MISO   = 39;    //39
const int SPI_MOSI   = 26;    //26
const int SPI_SCK    = 27;    //27

const int RX_ON      = 30;    //30 low when receiving, high when sending 
const int TX_ON      = 31;    //31 low when sending, high when receiving 

// ----------------------------------------------------------------------
// Construction, initialization, and destruction
// ----------------------------------------------------------------------

//construct the fprime component and radio object 
RFM23::RFM23(const char* const compName) : RFM23ComponentBase(compName), m_reinitialize(true), rf23( CS_PIN, INT_PIN, hardware_spi1 ) ; 
 {}

//init for the fprime compontent
void RFM23::init(const NATIVE_INT_TYPE instance) {
    RFM23ComponentBase::init(instance);
}

RFM23::~RFM23() {}

void RFM23::radioInit (){
  
  SPI1.setMISO(SPI_MISO);
  SPI1.setMOSI(SPI_MOSI);
  SPI1.setSCK(SPI_SCK);
  pinMode(RX_ON, OUTPUT);   //could be source of error 
  pinMode(TX_ON, OUTPUT);

int x = 0; 
  while( x < 10 ){
    if ( !rf23.init() ){  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
     
      Fw::Logger::logMsg("driver init failed: ");
      Fw::Logger::logMsg( x ); 
      digitalWrite(led, LOW);
      delay(5000);

      SPI1.end(); 
      delay(500);
       
      x += 1;
    }
    else
    {
      Fw::Logger::logMsg("init successful");
      return true; 
     }
  }
  if (x > 8){
    Fw::Logger::logMsg( "initialization failed, exiting" ); 
    return false; 
  }

    f23.setFrequency( 433 );  //433 according to the link budget 
    rf23.setTxPower( RH_RF22_RF23BP_TXPOW_30DBM );         
                                                  //RH_RF22_RF23B_TXPOW_13DBM    low power          
                                                  //RH_RF22_TXPOW_20DBM          mid power (.1W )
                                                  //RH_RF22_RF23BP_TXPOW_30DBM   highest power (for flight) (1W) 
  //must put to sleep before switching modulation scheme
    if( !rf23.sleep() ){
        Fw::Logger::logMsg( "failed to sleep" ); 
    }
    
    
    if ( !rf23.setModemConfig(RH_RF22::GFSK_Rb2Fd5)){    
                                                            // <FSK_Rb125Fd125>   highest FSK data rate (125kbs)
                                                            // <FSK_Rb2Fd5>       lowe FSK data rate (2kbs)
                                                            // <GFSK_Rb125Fd125>  highest GFSK rate GFSK (125kbs) TEST FOR FLIGHT
                                                            // <GFSK_Rb2Fd5>      lowest GFSK data rate (2kbs) 
                                                            // <FSK_Rb_512Fd2_5>  original FSK test modulation (0.512kbs)
                                                            
        Fw::Logger::logMsg( "modulation setting unsuccessful ");
    }

  //make it sleep again just in case
  if( !rf23.sleep() ){
    Fw::Logger::logMsg( "failed to sleep" ); 
  }
  else {
    Fw::Logger::logMsg( "init & setup successful"); 
  }
  
  this->comStatus_out(0, Drv::SendStatus::SEND_OK );
} //end radioInit

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

Drv::SendStatus RFM23::comDataIn_handler(const NATIVE_INT_TYPE portNum, Fw::Buffer& sendBuffer) {
    U8 *packetData = sendBuffer.getData();   //getData is a member function of Fw class 
    
    PLATFORM_INT_TYPE packetSize = sendBuffer.getSize();

    rf23.send(packetData, packetSize);          //send the packet 
    rf23.waitPacketSent();

    if (this->isConnected_comStatus_OutputPort(0)) {
        this->comStatus_out(0, Drv::SendStatus::SEND_OK );
    }

    this->deallocate_out(0,sendBuffer);         //deallocate the sendBuffer
        
    
    return Drv::SendStatus::SEND_OK;  // Always send ok to deframer as it does not handle this anyway
}

void RFM23 ::
    schedIn_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    if (rf23.waitAvailableTimeout( 100 )){

        Fw::Buffer receiveBuffer = this->allocate_out(0,RH_RF22_MAX_MESSAGE_LEN); 
        if( receiveBuffer.getSize() == RH_RF22_MAX_MESSAGE_LEN ){
            U8 receiveSize = RH_RF22_MAX_MESSAGE_LEN; 

            if (rf23.recv(receiveBuffer.getData(), &receiveSize)) {
                receiveBuffer.setSize(receiveSize); 
                comDataOut_out(0,receiveBuffer, Drv::SendStatus::SEND_OK); 
            }
        
        }
    }
  }

}  // end namespace 
