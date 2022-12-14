module Telecom {
    @ Communication adapter interface implementing communication adapter interface via a Drv.ByteStreamDriverModel.
    passive component RFM23 {

        # ----------------------------------------------------------------------
        # Framer, deframer, and queue ports
        # ----------------------------------------------------------------------

        @ Data coming in from the framing component
        sync input port comDataIn: Drv.ByteStreamSend

        @ Status of the last radio transmission
        output port comStatus: Fw.SuccessCondition

        @ Com data passing back out
        output port comDataOut: Drv.ByteStreamRecv

        # ----------------------------------------------------------------------
        # Byte stream model
        # ----------------------------------------------------------------------

        @ deallocate output port 
        output port deallocate: Fw.BufferSend

        @ Schedule in port
        sync input port schedIn: Svc.Sched

        @ allocate output port 
        output port allocate: Fw.BufferGet 

    }
}