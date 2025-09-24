#define DelayFactor 100  // Para Nexys

#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define GPIO2_BTNs  0x80001800
#define GPIO2_INOUT 0x80001808

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

int main(void)
{
    int i, count = 1, btns_value, delay;

    // Configura LEDs como salida
    WRITE_GPIO(GPIO_INOUT, 0xFFFF);

    // Configura botones como entrada
    WRITE_GPIO(GPIO2_INOUT, 0x00);

    while (1) {
        btns_value = READ_GPIO(GPIO2_BTNs) & 0x1F; // Lee los 5 botones

        // BTNC (bit 0) cambia la velocidad
        if (btns_value & 0x01)
            delay = 10000 * DelayFactor;
        else
            delay = 30000 * DelayFactor;

        // BTNU (bit 1) reinicia el contador
        if (btns_value & 0x02)
            count = 1;

        WRITE_GPIO(GPIO_LEDs, count);
        count++;

        for (i = 0; i < delay; i++);
    }

    return 0;
}