#include "hal_data.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

/* Callback function */

bsp_io_port_pin_t LEDS[4] = {LED0, LED1, LED2, LED3};
int visited[4] = {0};

void kfc_callback(external_irq_callback_args_t *p_args)
{
    volatile int d = 0;
    d++;
}

int isPushed()
{
    bsp_io_level_t lev;
    R_IOPORT_PinRead(&g_ioport_ctrl, BTN, &lev);

    if (lev == 0) return 1;
    return 0;
}

void DFS(int lev){
    if (lev == 3) {
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        if (visited[i] == 1) {
            continue;
        }
        R_IOPORT_PinWrite(&g_ioport_ctrl, LEDS[i], 1);
        DFS(lev+1);
    }


}


void hal_entry(void)
{
    /* TODO: add your own code here */
    R_ICU_ExternalIrqEnable(&g_external_irq0_ctrl);
    /* BTN: P113(D7), LED0: P400(D15), LED1: P302(D9), LED2: P105(D5), LED3: P104(D4) */
    while(1) {


        R_BSP_SoftwareDelay(100, BSP_DELAY_UNITS_MILLISECONDS);
    }

}

void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_POST_C == event)
    {
        R_IOPORT_Open(&g_ioport_ctrl, g_ioport.p_cfg);
        // R_SCI_UART_Open(&g_uart0_ctrl, &g_uart0_cfg);
        R_ICU_ExternalIrqOpen(&g_external_irq0_ctrl, &g_external_irq0_cfg);
    }
}
