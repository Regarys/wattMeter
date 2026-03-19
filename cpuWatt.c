#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long long read_energy() {
    FILE *fp = fopen("/sys/class/powercap/intel-rapl:0/energy_uj", "r");
    if (!fp) {
        perror("fopen");
        exit(1);
    }

    long long energy;
    fscanf(fp, "%lld", &energy);
    fclose(fp);

    return energy;
}

int main() {
    long long e1, e2;
    double watt;

    e1 = read_energy();
    sleep(1);  // interval 1 detik
    e2 = read_energy();

    if (e2 < e1) {
        printf("Overflow detected\n");
        return 1;
    }

    watt = (double)(e2 - e1) / 1e6; // µJ → J → Watt

    printf("CPU Power: %.2f W\n", watt);

    return 0;
}
