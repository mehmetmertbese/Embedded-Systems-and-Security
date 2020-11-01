
#include "KeyboardHID.h"
#include "german_keyboardCodes.h"

#define LED1 P1_1
#define LED2 P1_0

#define TICKS_PER_SECOND 10000
static volatile uint32_t ticks;
static uint32_t charTimes[84]; 

static uint8_t characterSent = 0,
			   indexToSend = 0;
static bool sendEnter = false;

static bool canSendNextChar = false;
static bool cracked = false;
static bool capsLockClosed = false;
static char CorrectKeyChars[20];
static uint8_t KeyIndex = 0;
static uint8_t foundCharNumber = 0;
static uint8_t charWriteCount = 0;
int a=0;
int b=0;

//finishCommandString[] = "echo 'MEHMET MERT BESE' > $HOME/03709689";
static int finishIndexes[] = {4, 2, 7, 14, 84, 85, 38, 30, 33, 38, 30, 45, 84, 38, 30, 43, 45, 84, 27, 30, 44, 30, 85, 84, 75, 84, 83, 33, 40, 38, 30, 80, 61, 54, 58, 61, 60, 57, 59, 60};
static uint8_t finishindexcounter = 0;

int charType(char ch);												  
void modifyReport(int indexToSend, USB_KeyboardReport_Data_t *report); 

void SysTick_Handler(void)
{
	ticks++;
}

XMC_SCU_CLOCK_CONFIG_t clock_config = {
	.syspll_config.p_div = 2,
	.syspll_config.n_div = 80,
	.syspll_config.k_div = 4,
	.syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL,
	.syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP,
	.enable_oschp = true,
	.calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY,
	.fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL,
	.fsys_clkdiv = 1,
	.fcpu_clkdiv = 1,
	.fccu_clkdiv = 1,
	.fperipheral_clkdiv = 1};

/* Forward declaration of HID callbacks as defined by LUFA */
bool CALLBACK_HID_Device_CreateHIDReport(
	USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo,
	uint8_t *const ReportID,
	const uint8_t ReportType,
	void *ReportData,
	uint16_t *const ReportSize);

void CALLBACK_HID_Device_ProcessHIDReport(
	USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo,
	const uint8_t ReportID,
	const uint8_t ReportType,
	const void *ReportData,
	const uint16_t ReportSize);

void SystemCoreClockSetup(void);

/**
 * Main program entry point. This routine configures the hardware required by
 * the application, then enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	// Init LED pins for debugging and NUM/CAPS visual report
	XMC_GPIO_SetMode(LED1, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	XMC_GPIO_SetMode(LED2, XMC_GPIO_MODE_OUTPUT_PUSH_PULL);
	USB_Init();

	// Wait until host has enumerated HID device
	int waitTime = 800000;
	for (int i = 0; i < waitTime; ++i)
		;
	SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);
	XMC_GPIO_SetOutputHigh(LED2);
	while (1)
	{
		HID_Device_USBTask(&Keyboard_HID_Interface);
	}
}

void modifyReport(int indexToSend, USB_KeyboardReport_Data_t *report)
{
	switch (indexToSend)
	{
	case 0:
		report->Modifier = 0;
		report->KeyCode[0] = 0x04;
		break;
	case 1:
		report->Modifier = 0;
		report->KeyCode[0] = 0x05;
		break;
	case 2:
		report->Modifier = 0;
		report->KeyCode[0] = 0x06;
		break;
	case 3:
		report->Modifier = 0;
		report->KeyCode[0] = 0x07;
		break;
	case 4:
		report->Modifier = 0;
		report->KeyCode[0] = 0x08;
		break;
	case 5:
		report->Modifier = 0;
		report->KeyCode[0] = 0x09;
		break;
	case 6:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0A;
		break;
	case 7:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0B;
		break;
	case 8:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0C;
		break;
	case 9:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0D;
		break;
	case 10:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0E;
		break;
	case 11:
		report->Modifier = 0;
		report->KeyCode[0] = 0x0F;
		break;
	case 12:
		report->Modifier = 0;
		report->KeyCode[0] = 0x10;
		break;
	case 13:
		report->Modifier = 0;
		report->KeyCode[0] = 0x11;
		break;
	case 14:
		report->Modifier = 0;
		report->KeyCode[0] = 0x12;
		break;
	case 15:
		report->Modifier = 0;
		report->KeyCode[0] = 0x13;
		break;
	case 16:
		report->Modifier = 0;
		report->KeyCode[0] = 0x14;
		break;
	case 17:
		report->Modifier = 0;
		report->KeyCode[0] = 0x15;
		break;
	case 18:
		report->Modifier = 0;
		report->KeyCode[0] = 0x16;
		break;
	case 19:
		report->Modifier = 0;
		report->KeyCode[0] = 0x17;
		break;
	case 20:
		report->Modifier = 0;
		report->KeyCode[0] = 0x18;
		break;
	case 21:
		report->Modifier = 0;
		report->KeyCode[0] = 0x19;
		break;
	case 22:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1A;
		break;
	case 23:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1B;
		break;
	case 24:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1D;
		break;
	case 25:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1C;
		break;

	case 26:
		report->Modifier = 2;
		report->KeyCode[0] = 0x04;
		break;
	case 27:
		report->Modifier = 2;
		report->KeyCode[0] = 0x05;
		break;
	case 28:
		report->Modifier = 2;
		report->KeyCode[0] = 0x06;
		break;
	case 29:
		report->Modifier = 2;
		report->KeyCode[0] = 0x07;
		break;
	case 30:
		report->Modifier = 2;
		report->KeyCode[0] = 0x08;
		break;
	case 31:
		report->Modifier = 2;
		report->KeyCode[0] = 0x09;
		break;
	case 32:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0A;
		break;
	case 33:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0B;
		break;
	case 34:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0C;
		break;
	case 35:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0D;
		break;
	case 36:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0E;
		break;
	case 37:
		report->Modifier = 2;
		report->KeyCode[0] = 0x0F;
		break;
	case 38:
		report->Modifier = 2;
		report->KeyCode[0] = 0x10;
		break;
	case 39:
		report->Modifier = 2;
		report->KeyCode[0] = 0x11;
		break;
	case 40:
		report->Modifier = 2;
		report->KeyCode[0] = 0x12;
		break;
	case 41:
		report->Modifier = 2;
		report->KeyCode[0] = 0x13;
		break;
	case 42:
		report->Modifier = 2;
		report->KeyCode[0] = 0x14;
		break;
	case 43:
		report->Modifier = 2;
		report->KeyCode[0] = 0x15;
		break;
	case 44:
		report->Modifier = 2;
		report->KeyCode[0] = 0x16;
		break;
	case 45:
		report->Modifier = 2;
		report->KeyCode[0] = 0x17;
		break;
	case 46:
		report->Modifier = 2;
		report->KeyCode[0] = 0x18;
		break;
	case 47:
		report->Modifier = 2;
		report->KeyCode[0] = 0x19;
		break;
	case 48:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1A;
		break;
	case 49:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1B;
		break;
	case 50:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1D;
		break;
	case 51:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1C;
		break;

	//
	case 52:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1E;
		break;
	case 53:
		report->Modifier = 0;
		report->KeyCode[0] = 0x1F;
		break;
	case 54:
		report->Modifier = 0;
		report->KeyCode[0] = 0x20;
		break;
	case 55:
		report->Modifier = 0;
		report->KeyCode[0] = 0x21;
		break;
	case 56:
		report->Modifier = 0;
		report->KeyCode[0] = 0x22;
		break;
	case 57:
		report->Modifier = 0;
		report->KeyCode[0] = 0x23;
		break;
	case 58:
		report->Modifier = 0;
		report->KeyCode[0] = 0x24;
		break;
	case 59:
		report->Modifier = 0;
		report->KeyCode[0] = 0x25;
		break;
	case 60:
		report->Modifier = 0;
		report->KeyCode[0] = 0x26;
		break;
	case 61:
		report->Modifier = 0;
		report->KeyCode[0] = 0x27;
		break;

	case 62:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1E;
		break;
	case 63:
		report->Modifier = 2;
		report->KeyCode[0] = 0x25;
		break;
	case 64:
		report->Modifier = 2;
		report->KeyCode[0] = 0x26;
		break;
	case 65:
		report->Modifier = 0;
		report->KeyCode[0] = 0x38;
		break;
	case 66:
		report->Modifier = 2;
		report->KeyCode[0] = 0x38;
		break;
	case 67:
		report->Modifier = 0;
		report->KeyCode[0] = 0x30;
		break;
	case 68:
		report->Modifier = 2;
		report->KeyCode[0] = 0x27;
		break;
	case 69:
		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
		report->KeyCode[0] = 0x30;
		break;
	case 70:
		report->Modifier = 2;
		report->KeyCode[0] = 0x36;
		break;
	case 71:
		report->Modifier = 2;
		report->KeyCode[0] = 0x37;
		break;
	case 72:
		report->Modifier = 0;
		report->KeyCode[0] = 0x36;
		break;
	case 73:
		report->Modifier = 0;
		report->KeyCode[0] = 0x37;
		break;
	case 74:
		report->Modifier = 0;
		report->KeyCode[0] = 0x64;
		break;
	case 75:
		report->Modifier = 2;
		report->KeyCode[0] = 0x64;
		break;
	case 76:
		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
		report->KeyCode[0] = 0x25;
		break;
	case 77:
		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
		report->KeyCode[0] = 0x26;
		break;
	case 78:
		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
		report->KeyCode[0] = 0x24;
		break;
	case 79:
		report->Modifier = HID_KEYBOARD_MODIFIER_RIGHTALT;
		report->KeyCode[0] = 0x27;
		break;
	case 80:
		report->Modifier = 2;
		report->KeyCode[0] = 0x24;
		break;
	case 81:
		report->Modifier = 2;
		report->KeyCode[0] = 0x2D;
		break;
	case 82:
		report->Modifier = 2;
		report->KeyCode[0] = 0x23;
		break;
	case 83:
		report->Modifier = 2;
		report->KeyCode[0] = 0x21;
		break;
	case 84:
		report->Modifier = 0;
		report->KeyCode[0] = 0x2C;
		break;
	case 85:
		report->Modifier = 2;
		report->KeyCode[0] = 0x1F;
		break;
	};
}

void findLetterOfKey(USB_KeyboardReport_Data_t *report)
{
	if (indexToSend < 83 && canSendNextChar)
	{
		if (characterSent)
		{

			report->Modifier = 0;
			report->Reserved = 0;
			report->KeyCode[0] = 0;
			characterSent = 0;
			if (!sendEnter)
			{
				canSendNextChar = false;
				++indexToSend;
			}
		}
		else if (sendEnter)
		{
			report->Modifier = 0;
			report->Reserved = 0;
			report->KeyCode[0] = GERMAN_KEYBOARD_SC_ENTER;
			sendEnter = false;
			charTimes[indexToSend] = ticks;
			ticks = 0;
			characterSent = 1;
		}
		else
		{
			report->Modifier = 0;
			if (foundCharNumber == charWriteCount)
			{
				modifyReport(indexToSend, report);
				charWriteCount = 0;
				sendEnter = true;
			}
			else
			{
				modifyReport(CorrectKeyChars[charWriteCount], report);
				charWriteCount++;
			}
		}
	}
	else
	{
		report->Modifier = 0;
		report->Reserved = 0;
		report->KeyCode[0] = 0;
		characterSent = 0;
	}
}

bool CALLBACK_HID_Device_CreateHIDReport(
	USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo,
	uint8_t *const ReportID,
	const uint8_t ReportType,
	void *ReportData,
	uint16_t *const ReportSize)
{
	USB_KeyboardReport_Data_t *report = (USB_KeyboardReport_Data_t *)ReportData;
	*ReportSize = sizeof(USB_KeyboardReport_Data_t);

	static bool capsLockTapped = false;
	static bool shouldSendData;
	if (!cracked)
	{
		findLetterOfKey(report);
	}
	else if (!capsLockClosed)
	{
		if (capsLockTapped)
		{
			report->Modifier = 0;
			report->Reserved = 0;
			report->KeyCode[0] = 0;
			characterSent = 0;
			capsLockClosed = true;
		}
		else if (!capsLockClosed)
		{
			report->Modifier = 0;
			report->Reserved = 0;
			report->KeyCode[0] = HID_KEYBOARD_SC_CAPS_LOCK;
			capsLockTapped = true;
			for (int i = 0; i < 10e5; ++i)
				;
		}
	}
	else if (capsLockClosed)
	{
		if (finishindexcounter < 40)
		{
			report->Modifier = 0;
			modifyReport(finishIndexes[finishindexcounter], report);
			finishindexcounter++;
		}
		else if (finishindexcounter == 40)
		{
			report->Modifier = 0;
			report->Reserved = 0;
			report->KeyCode[0] = GERMAN_KEYBOARD_SC_ENTER;
			finishindexcounter++;
		}
	}
	return true;
}

uint8_t findHighestTime()
{
	uint32_t max_time = 0;
	uint8_t location = 0;
	a=a+1;
	b=b+1;
	for (int i = 0; i < 83; i++)
	{
		if (charTimes[i] > max_time)
		{
			max_time = charTimes[i];
			location = i;
		}
	}
	return location - 1;
}

// Called on report input. For keyboard HID devices, that's the state of the LEDs
void CALLBACK_HID_Device_ProcessHIDReport(
	USB_ClassInfo_HID_Device_t *const HIDInterfaceInfo,
	const uint8_t ReportID,
	const uint8_t ReportType,
	const void *ReportData,
	const uint16_t ReportSize)
{
	uint8_t *report = (uint8_t *)ReportData;

	if (*report & HID_KEYBOARD_LED_NUMLOCK)
	{
		XMC_GPIO_SetOutputHigh(LED1);
		if (indexToSend == 83)
		{
			KeyIndex = findHighestTime();
			CorrectKeyChars[foundCharNumber] = KeyIndex;
			foundCharNumber++;
			indexToSend = 0;
		}
		canSendNextChar = true;
	}
	else
	{
		XMC_GPIO_SetOutputLow(LED1);
		canSendNextChar = false;
	}

	if (*report & HID_KEYBOARD_LED_CAPSLOCK)
	{
		XMC_GPIO_SetOutputHigh(LED2);
		cracked = true;
	}
	else
	{
		XMC_GPIO_SetOutputLow(LED2);
	}
}

void SystemCoreClockSetup(void)
{
	/* Setup settings for USB clock */
	XMC_SCU_CLOCK_Init(&clock_config);

	XMC_SCU_CLOCK_EnableUsbPll();
	XMC_SCU_CLOCK_StartUsbPll(2, 64);
	XMC_SCU_CLOCK_SetUsbClockDivider(4);
	XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
	XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

	SystemCoreClockUpdate();
}
