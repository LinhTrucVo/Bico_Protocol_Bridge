// ComService Implementation - Buffered Serial Communication with Ring-Buffers

#include <stddef.h>
#include <string.h>
#include "comService.h"
#include "serialDriver.h"

//============================================================================
// Internal Types
//============================================================================
typedef struct
{
    uint8_t  buffer[COMSERVICE_CFG_RX_BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
} ComService_RingBuffer_t;

typedef struct
{
    bool                    initialized;
    bool                    txBusy;
    ComService_RingBuffer_t rx;
    ComService_RingBuffer_t tx;
} ComService_Context_t;

//============================================================================
// Static Variables
//============================================================================
static ComService_Context_t context = {0};

//============================================================================
// Internal Helper Functions
//============================================================================
static bool RingBuffer_Write(ComService_RingBuffer_t *pRb, uint16_t bufSize, const uint8_t *pData, uint16_t length)
{
    if (pRb->count + length > bufSize)
    {
        return false;
    }
    for (uint16_t i = 0U; i < length; i++)
    {
        pRb->buffer[pRb->head] = pData[i];
        pRb->head = (pRb->head + 1U) % bufSize;
    }
    pRb->count += length;
    return true;
}

static uint16_t RingBuffer_Read(ComService_RingBuffer_t *pRb, uint16_t bufSize, uint8_t *pData, uint16_t maxLength)
{
    uint16_t toRead = (pRb->count < maxLength) ? pRb->count : maxLength;
    for (uint16_t i = 0U; i < toRead; i++)
    {
        pData[i] = pRb->buffer[pRb->tail];
        pRb->tail = (pRb->tail + 1U) % bufSize;
    }
    pRb->count -= toRead;
    return toRead;
}

//============================================================================
// Serial Driver Callbacks (called from ISR context)
//============================================================================
static void ComService_RxCallback(const uint8_t *pData, uint16_t length)
{
    if ((pData != NULL) && (length > 0U))
    {
        (void)RingBuffer_Write(&context.rx, COMSERVICE_CFG_RX_BUFFER_SIZE, pData, length);
    }
}

static void ComService_TxCallback(void)
{
    context.txBusy = false;
}

//============================================================================
// Public Functions
//============================================================================
ComService_Status_t ComServiceUnit_Init(void)
{
    context.rx.head  = 0U;
    context.rx.tail  = 0U;
    context.rx.count = 0U;
    context.tx.head  = 0U;
    context.tx.tail  = 0U;
    context.tx.count = 0U;
    context.txBusy   = false;

    /* Register callbacks with Serial Driver */
    (void)SerialDriverUnit_RegisterRxCallback(ComService_RxCallback);
    (void)SerialDriverUnit_RegisterTxCallback(ComService_TxCallback);

    context.initialized = true;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_DeInit(void)
{
    /* Deregister callbacks */
    (void)SerialDriverUnit_RegisterRxCallback(NULL);
    (void)SerialDriverUnit_RegisterTxCallback(NULL);

    context.initialized = false;
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_Run(void)
{
    if (!context.initialized)
    {
        return COMSERVICE_STATUS_NOT_INITIALIZED;
    }

    /* Tx: Flush Tx ring-buffer to Serial Driver when not busy */
    if ((!context.txBusy) && (context.tx.count > 0U))
    {
        uint8_t  txBuf[COMSERVICE_CFG_MAX_FRAME_SIZE];
        uint16_t toSend = (context.tx.count > COMSERVICE_CFG_MAX_FRAME_SIZE) ? COMSERVICE_CFG_MAX_FRAME_SIZE : context.tx.count;
        uint16_t sent = RingBuffer_Read(&context.tx, COMSERVICE_CFG_TX_BUFFER_SIZE, txBuf, toSend);

        if (sent > 0U)
        {
            if (SerialDriverUnit_Send(txBuf, sent) == SERIALDRIVERSTATUS_OK)
            {
                context.txBusy = true;
            }
            else
            {
                /* Send failed, put data back (best effort - write back to buffer) */
                (void)RingBuffer_Write(&context.tx, COMSERVICE_CFG_TX_BUFFER_SIZE, txBuf, sent);
            }
        }
    }

    return COMSERVICE_STATUS_OK;
}

bool ComServiceUnit_IsRxDataAvailable(void)
{
    if (!context.initialized)
    {
        return false;
    }
    return (context.rx.count > 0U);
}

ComService_Status_t ComServiceUnit_Read(uint8_t *pData, uint16_t maxLength, uint16_t *pReadLength)
{
    if (!context.initialized)
    {
        return COMSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || pReadLength == NULL)
    {
        return COMSERVICE_STATUS_INVALID_PARAM;
    }
    if (context.rx.count == 0U)
    {
        *pReadLength = 0U;
        return COMSERVICE_STATUS_BUFFER_EMPTY;
    }

    *pReadLength = RingBuffer_Read(&context.rx, COMSERVICE_CFG_RX_BUFFER_SIZE, pData, maxLength);
    return COMSERVICE_STATUS_OK;
}

ComService_Status_t ComServiceUnit_Write(const uint8_t *pData, uint16_t length)
{
    if (!context.initialized)
    {
        return COMSERVICE_STATUS_NOT_INITIALIZED;
    }
    if (pData == NULL || length == 0U)
    {
        return COMSERVICE_STATUS_INVALID_PARAM;
    }
    if (!RingBuffer_Write(&context.tx, COMSERVICE_CFG_TX_BUFFER_SIZE, pData, length))
    {
        return COMSERVICE_STATUS_BUFFER_FULL;
    }
    return COMSERVICE_STATUS_OK;
}
