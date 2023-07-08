#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

osThreadId RedTaskHandle;
osThreadId GreemTaskHandle;
osThreadId BlueLedHandle;

void MainTask(void const *argument);
void SecondTask(void const *argument);
void ThirdTask(void const *argument);

void MX_FREERTOS_Init(void);

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
		StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize) {
	*ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
	*ppxIdleTaskStackBuffer = &xIdleStack[0];
	*pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;

}

void MX_FREERTOS_Init(void) {

	osThreadDef(RedTask, MainTask, osPriorityNormal, 0, 128);
	RedTaskHandle = osThreadCreate(osThread(RedTask), NULL);

	/* definition and creation of GreemTask */
	osThreadDef(GreemTask, SecondTask, osPriorityNormal, 0, 128);
	GreemTaskHandle = osThreadCreate(osThread(GreemTask), NULL);

	/* definition and creation of BlueLed */
	osThreadDef(BlueLed, ThirdTask, osPriorityNormal, 0, 128);
	BlueLedHandle = osThreadCreate(osThread(BlueLed), NULL);

}

void MainTask(void const *argument) {

	for (;;) {
		HAL_GPIO_TogglePin(RedLed_GPIO_Port, RedLed_Pin);
		vTaskDelay(1000/portTICK_PERIOD_MS);
	}

}

void SecondTask(void const *argument) {

	for (;;) {
		HAL_GPIO_TogglePin(BlueLed_GPIO_Port, BlueLed_Pin);
		vTaskDelay(200/portTICK_PERIOD_MS);
	}

}

void ThirdTask(void const *argument) {

	for (;;) {
		HAL_GPIO_TogglePin(GreenLed_GPIO_Port, GreenLed_Pin);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}

}

