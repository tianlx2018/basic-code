#include "rwcp.h"
#include "stdbool.h"

//client to server
#define OP_CODE_DATA            0
#define OP_CODE_SYN              0x40
//server to client
#define OP_CODE_DATA_ACK           0
#define OP_CODE_SYN_ACK             0x40
#define OP_CODE_RST                     0x80
#define OP_CODE_RST_ACK             0x80
#define OP_CODE_GAP                    0xc0

bool flag_syn_ack = 0;
bool flag_data_ack = 0;
bool flag_rst_ack = 0;
bool flag_rst = 0;
bool flag_gap = 0;
bool flag_client_rst = 0;//if client reset section,then 1,else 0

int slide_window_tx = SLIDE_WINDOW_SIZE;
int curse = 0;
int length_remain = 0;
uint8_t sequence = 0;

static void send_bytes(uint8_t *data,int length)
{
    return;
}

static void send_one_byte(uint8_t data)
{
    return;
}

static void delay_ms(int  ms)
{
    RWCP_LOG("delay %d ms \r\n",ms);
    return;
}

//send data from buff
//uint8_t *pbuf:point to the original buffer header
//return data length remained
static int send_data(uint8_t *pbuf)
{
    do
    {
        sequence &= 0x3f;//OP_CODE_DATA
        send_bytes(&sequence,1);
        sequence++;

        if(length_remain > SEND_MTU-1)
        {
            send_bytes(pbuf+curse,SEND_MTU-1);
            length_remain -= SEND_MTU-1;
            curse += SEND_MTU-1;
        }
        else
        {
            send_bytes(pbuf+curse,length_remain);
            length_remain = 0;
        }

        slide_window_tx--;

    }while(slide_window_tx > 0 && length_remain > 0);

    return length_remain;
}

//int rwcp_send_handle(void)
int rwcp_send(uint8_t *pbuf,uint32_t length)
{
    //reset status
    flag_data_ack = 0;
    flag_gap = 0;
    flag_rst = 0;
    flag_rst_ack = 0;
    flag_syn_ack = 0;

    slide_window_tx = SLIDE_WINDOW_SIZE;
    curse = 0;
    length_remain = length;
    sequence = 0;

    //start section
    int retry_times = SEND_RETRY_TIMES;

    do
    {
        send_one_byte(OP_CODE_SYN);
        delay_ms(SEND_INTERVAL);
    }while(flag_syn_ack == 0 && retry_times-- > 0);

    if(retry_times == 0)
    return ERR_SERVER_NO_REPLY;

    //start sending
    retry_times = SEND_RETRY_TIMES;
    do
    {
        if(flag_data_ack)
        {
            retry_times = SEND_RETRY_TIMES;
            flag_data_ack = 0;
        }

        //do sending actions and output the length remained
        length_remain = send_data(pbuf);

        if(length_remain == 0)
            return ERR_NONE;

        delay_ms(SEND_INTERVAL);

    }while(retry_times-- > 0 && flag_rst == 0);

    if(flag_rst)
        return ERR_SERVER_RST;

    if(retry_times == 0)
        return ERR_SERVER_NO_REPLY;

    //success
    return ERR_NONE;
}

static void window_tx_move_forward(void)
{
    if(slide_window_tx<SLIDE_WINDOW_SIZE)
        slide_window_tx++;
}

int rwcp_server_on_receive(uint8_t *pbuf,uint32_t length)
{
    uint8_t type = *pbuf & 0xc0;
    uint8_t seq = *pbuf & 0x3f;

    switch(type)
    {
        case OP_CODE_DATA:
            send_one_byte(seq);//seq | OP_CODE_DATA = seq
            break;
        case OP_CODE_SYN:
            send_one_byte(OP_CODE_SYN_ACK);
            break;
        case OP_CODE_RST:
            send_one_byte(OP_CODE_RST_ACK);
            break;
    }

    return 0;
}

int rwcp_client_on_receive(uint8_t *pbuf,uint32_t length)
{
    uint8_t type = *pbuf & 0xc0;
    //uint8_t seq = *pbuf & 0x3f;

    switch(type)
    {
        case OP_CODE_DATA_ACK:
            {
                window_tx_move_forward();
                flag_data_ack = 1;
            }
            break;

        case OP_CODE_SYN_ACK:
            flag_syn_ack = 1;
            break;

        case OP_CODE_RST:
        //case OP_CODE_RST_ACK:
            if(flag_client_rst)
                flag_rst_ack = 1;
            else
            {
                flag_rst = 1;
                send_one_byte(OP_CODE_RST);
            }
            break;
    }

    return 0;
}

int rwcp_client_reset(void)
{
    flag_client_rst = 1;
    flag_rst = 1;
    send_one_byte(OP_CODE_RST);
    return 0;
}

int rwcp_sever_reset(void)
{
    send_one_byte(OP_CODE_RST);
    return 0;
}
