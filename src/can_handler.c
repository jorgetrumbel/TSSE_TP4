/***************************************************************************//**
 @file     
 @brief	   
 @author   AV
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "can_handler.h"
#include <string.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define ID_9_BIT_POSITION	0x3FE

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static can_tx_sent_status_e tx_message_sent;							//Boolean indicator for sent CAN message

/*******************************************************************************
 *******************************************************************************
 GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void can_message_builder(struct can_message* message, bool error_bit, bool dir_bit, uint16_t message_9_bit_id, uint8_t * message_data, uint8_t data_length){
	message->id = (message_9_bit_id << 1) & ID_9_BIT_POSITION;
	message->id |= error_bit << 10;
	message->id |= dir_bit;
	message->fmt  = CAN_FMT_STDID;
	
	message->type = CAN_TYPE_DATA;
    memcpy(message->data, message_data, data_length);
	message->len  = data_length;
}

bool check_for_can_message_error(can_message_w_payload rx_msg){
	return (rx_msg.can_information.id & 0x400);
}

bool check_for_can_message_direction(can_message_w_payload rx_msg){
	return (rx_msg.can_information.id & 0x001);
}

uint16_t get_message_can_id(can_message_w_payload msg){
	return (msg.can_information.id & ID_9_BIT_POSITION) >> 1;
}

can_data_id_e get_can_message_data_id(uint8_t* data_to_check){
	return (can_data_id_e)*(data_to_check);
}

/*******************************************************************************
 *******************************************************************************
 LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/******************************************************************************/

