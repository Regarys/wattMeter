#include <stdio.h>
#include "nvml.h"

int main() {
    nvmlInit();

    nvmlDevice_t device;
    nvmlDeviceGetHandleByIndex(0, &device);

    unsigned int power;
    nvmlDeviceGetPowerUsage(device, &power);

    printf("GPU: %.2f W\n", power / 1000.0);

    nvmlShutdown();
    return 0;
}
