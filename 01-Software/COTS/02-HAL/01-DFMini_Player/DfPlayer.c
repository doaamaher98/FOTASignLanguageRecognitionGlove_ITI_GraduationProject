#include "UART.h"
#include "UART_Cfg.h"
#include "DfPlayer.h"
#include "DfPlayer_Prv.h"

#define DFP_IDX_StartCommand			0
#define DFP_IDX_VersionInformation		1
#define DFP_IDX_DataLength				2
#define DFP_IDX_Command		            3
#define DFP_IDX_FEEDBACK	            4
#define DFP_IDX_PARAM_MSB	            5
#define DFP_IDX_PARAM_LSB	            6
#define DFP_IDX_CHECK_MSB	            7
#define DFP_IDX_CHECK_LSB	            8
#define DFP_IDX_EndCommand		        9

static u8 Command_Array[10];


static u16 DFP_Checksum(void)
{
	u16 checksum = 0;
	checksum  = Command_Array[DFP_IDX_VersionInformation];
	checksum += Command_Array[DFP_IDX_DataLength];
	checksum += Command_Array[DFP_IDX_Command];
	checksum += Command_Array[DFP_IDX_FEEDBACK];
	checksum += Command_Array[DFP_IDX_PARAM_MSB];
	checksum += Command_Array[DFP_IDX_PARAM_LSB];

	checksum = 0xFFFF - checksum + 1;

	return checksum;
}

//void MUART_VidSendCharSync(u8 Copy_u8Char , UART_CHANNELS_t Channel_No)

void DFP_PlayTrackInFolder(u8 Copy_folder, u8 Copy_track , UART_CHANNELS_t Channel_No)
{
	u8 Local_u8Iterator;

	Command_Array[DFP_IDX_StartCommand] = DFP_StartCommand;
	Command_Array[DFP_IDX_VersionInformation] = DFP_VER;
	Command_Array[DFP_IDX_DataLength] = DFP_DataLength;
	Command_Array[DFP_IDX_Command] = DFP_Command_PlayTrackFolder;
	Command_Array[DFP_IDX_FEEDBACK] = DFP_NOFEEDBACK;
	Command_Array[DFP_IDX_PARAM_MSB] = Copy_folder;
	Command_Array[DFP_IDX_PARAM_LSB] = Copy_track;
	u16 checksum = DFP_Checksum();
	Command_Array[DFP_IDX_CHECK_MSB] = (checksum & 0xFF00) >> 8;
	Command_Array[DFP_IDX_CHECK_LSB] = checksum & 0x00FF;
	Command_Array[DFP_IDX_EndCommand] = DFP_EndCommand;

	for(Local_u8Iterator = 0; Local_u8Iterator < 10; Local_u8Iterator++)
	{
		MUART_VidSendCharSync(Command_Array[Local_u8Iterator] , Channel_No);
	}

}
