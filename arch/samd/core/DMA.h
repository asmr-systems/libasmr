#ifndef _DMA_H_
#define _DMA_H_

// TODO add DMA related types (see AdafruitDMA)

enum class DMAStatus {
    OK,
    NOT_FOUND,
    BUSY,
    ERR_NOT_INITIALIZED,
};

enum class DMATriggerAction {
    BEAT,
    BLOCK,
    TRANSACTION,
};

enum class DMACallback {
    TRANSFER_DONE,
    TRANSFER_ERR,
    CHANNEL_SUSPEND,
};

enum DMAPriority {
    DMA_PRIORITY_0,
    DMA_PRIORITY_1,
    DMA_PRIORITY_2,
    DMA_PRIORITY_3,
};

class DMAChannel {
public:
    DMAChannel();

    /**  @brief allocates a DMA channel.

         @return DMA::Status::OK
                 DMA::Status::NOT_FOUND
     */
    DMAStatus allocate();

    /**  @brief de-allocates a DMA channel.

         @return DMA::Status::OK
                 DMA::Status::BUSY
                 DMA::Status::ERR_NOT_INITIALIZED
    */
    DMAStatus free();

    /**  @brief trigger a DMA channel via software
     */
    void trigger();

    /**  @brief set DMA peripheral trigger.

         @param a trigger ID.
     */
    void setTrigger(uint8_t trigger);

    /**  @brief set DMA trigger action.

         @param action DMATriggerAction
     */
    void setAction(DMATriggerAction action);

    void setCallback(
        void (*callback)(DMAChannel *) = NULL,
        DMACallback type = DMACallback::TRANSFER_DONE);


    void setPriority(DMAPriority pri);

    uint8_t getChannel();

    bool isInProgress();

    // TODO
    DMacDescriptor* addDescriptor();
};

#endif // _DMA_H_
